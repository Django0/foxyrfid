#include "stdafx.h"
#include "NDEFRecord.h"
#include "URI.h"
#include "NTAG_I2C_Glossary.h"

		// Gets a bluetooth pairing NDEF message and returns the Bluetooth information parsed
		LONG NDEFRecord::parseBTPairRecord(char* input, char* output, int* payloadSize)
		{
			// Initialize pointers to go accross the array, and other variables
			char* p_end = input + input[0];
			char *deviceName = NULL, *deviceClass = NULL;
			int length, deviceNameLength = 0, deviceClassLength = 0;
			char *p_in, *p_out;
			int i;

			// The string I return is: MAC address length + MAC address + Name length + Name + Class length + Class + '\0'

			// MAC address (input[2..7] to output[1..12])
			output[0] = 12;
			for (i = 6, p_in = input + 7, p_out = output + 1; i > 0; i--, p_in--, p_out++)
			{
				*p_out = ((*p_in >> 4) & 0x0F) + '0';
				p_out++;
				*p_out = ((*p_in) & 0x0F) + '0';
			}
			p_in = input + 8;
			do
			{
				// Name or Class, depending on the second byte
				length = *p_in - 1;
				*p_out = length;
				p_in++;
				switch (*p_in)
				{
				case 0x09:
					// Name
					deviceNameLength = length;
					deviceName = (char*)malloc(deviceNameLength*sizeof(char));
					p_in++;
					memcpy(deviceName, p_in, deviceNameLength);
					p_in += deviceNameLength;
					break;
				case 0x0D:
					//Class
					deviceClassLength = 2 * length;
					deviceClass = (char*)malloc(deviceClassLength*sizeof(char));
					p_in += length;
					p_out = deviceClass;
					for (i = length; i > 0; i--, p_in--, p_out++)
					{
						*p_out = ((*p_in >> 4) & 0x0F) + '0';
						p_out++;
						*p_out = ((*p_in) & 0x0F) + '0';
					}
					p_in += length + 1;
					break;
				}
			} while (p_in < p_end);

			// Name
			p_out = output + 13;
			*p_out = deviceNameLength;
			p_out++;
			memcpy(p_out, deviceName, deviceNameLength);
			free(deviceName);

			// Class
			p_out += deviceNameLength;
			*p_out = deviceClassLength;
			p_out++;
			memcpy(p_out, deviceClass, deviceClassLength);
			p_out += deviceClassLength;
			*p_out = '\0';
			free(deviceClass);

			*payloadSize = 12 + deviceNameLength + deviceClassLength + 2;

			return SCARD_S_SUCCESS;
		}

		// Creates a text-type NDEF message
		LONG NDEFRecord::createTextRecord(BYTE* payload, int payloadSize, BYTE* message, int* length)
		{
			int ndefHeaderSize;
			
			if (payloadSize + 7 > 255)
			{			
				BYTE ndef_header[] = { NDEF_NFCF_TYPE2, 0xFF, (BYTE)(floor((payloadSize + 10) / 256)), (BYTE)((payloadSize + 10) % 256), NDEF_TNF_LONG, 0x01, 0x00, 0x00, (BYTE)(floor((payloadSize + 3) / 256)), (BYTE)((payloadSize + 3) % 256), NDEF_TEXT_TYPE, 0x02, NDEF_TEXT_LANG_P1, NDEF_TEXT_LANG_P2 };
				ndefHeaderSize = ARRAY_SIZE(ndef_header);
				memcpy(message, ndef_header, ndefHeaderSize);
				memcpy(message + ndefHeaderSize, payload, payloadSize);
				message[ndefHeaderSize + payloadSize] = 0xFE;
				*length = ndefHeaderSize + payloadSize + 1;
			}
			else
			{
				BYTE ndef_header[] = { NDEF_NFCF_TYPE2, payloadSize + 7, NDEF_TNF_SHORT, 0x01, payloadSize + 3, NDEF_TEXT_TYPE, 0x02, NDEF_TEXT_LANG_P1, NDEF_TEXT_LANG_P2 };
				ndefHeaderSize = ARRAY_SIZE(ndef_header);
				memcpy(message, ndef_header, ndefHeaderSize);
				memcpy(message + ndefHeaderSize, payload, payloadSize);
				message[ndefHeaderSize + payloadSize] = 0xFE;
				*length = ndefHeaderSize + payloadSize + 1;
			}
			
			return SCARD_S_SUCCESS;
		}

		// Creates a URI-type NDEF message
		LONG NDEFRecord::createUriRecord(BYTE* payload, int payloadSize, BYTE* message, int* length)
		{
			LONG lReturn;
			BYTE uriType = 0;
			BYTE uriLength = 0;

			
			lReturn = URI::getUriIdentifier((char*)payload, &uriType, &uriLength);
			if (lReturn == SCARD_S_SUCCESS)
			{
				// Recalculate the new size
				payloadSize = payloadSize - uriLength;

				// NDEF header
				BYTE ndef_header[] = { NDEF_NFCF_TYPE2, payloadSize + 5, NDEF_TNF_SHORT, 0x01, payloadSize + 1, NDEF_URI_TYPE };
				int ndefHeaderSize = ARRAY_SIZE(ndef_header);

				// NDEF message
				memcpy(message, ndef_header, ndefHeaderSize);
				message[ndefHeaderSize] = uriType;
				memcpy(message + ndefHeaderSize + 1, payload + uriLength, payloadSize);
				message[ndefHeaderSize + 1 + payloadSize] = 0xFE;
				*length = ndefHeaderSize + 1 + payloadSize + 1;
			}

			return lReturn;
		}

		// Creates a Bluetooth handover type NDEF message
		LONG NDEFRecord::createBTPairRecord(BYTE* payload, int payloadSize, BYTE* message, int* length)
		{
			// Get pairing values
			BYTE *deviceMAC, *deviceName, *deviceClass;
			BYTE deviceMACLength = 0, deviceNameLength = 0, deviceClassLength = 0;

			// The string I receive is: MAC address + Name length + Name + Class length + Class + '\0'
			// Get the MAC address
			deviceMACLength = 6;
			deviceMAC = (BYTE*)malloc(deviceMACLength * sizeof(BYTE));
			for (int i = 0, j = deviceMACLength - 1; j >= 0; i += 2, j--)
				deviceMAC[j] = (BYTE)(((payload[i] - '0') << 4) + (payload[i + 1] - '0'));
			// Get the name
			deviceNameLength = payload[deviceMACLength * 2];
			deviceName = (BYTE*)malloc(deviceNameLength * sizeof(BYTE));
			memcpy(deviceName, payload + deviceMACLength * 2 + 1, deviceNameLength);
			// Get the class
			deviceClassLength = payload[deviceMACLength * 2 + 1 + deviceNameLength] / 2;
			deviceClass = (BYTE*)malloc(deviceClassLength * sizeof(BYTE));
			for (int i = deviceMACLength * 2 + 1 + deviceNameLength + 1, j = deviceClassLength - 1; j >= 0; i += 2, j--)
				deviceClass[j] = (BYTE)(((payload[i] - '0') << 4) + (payload[i + 1] - '0'));

			// Build the payload of the Bluetooth handover message
			BYTE payloadBtLength = deviceMACLength + deviceNameLength + deviceClassLength + 2 + 4;
			BYTE* payloadBt = (BYTE*)malloc(payloadBtLength*sizeof(BYTE));
			// Payload Size
			payloadBt[0] = payloadBtLength;
			payloadBt[1] = 0x00;
			// MAC address
			memcpy(payloadBt + 2, deviceMAC, deviceMACLength);
			free(deviceMAC);
			// Name
			payloadBt[8] = deviceNameLength + 1;
			payloadBt[9] = 0x09; // Device Name identifier
			memcpy(payloadBt + 10, deviceName, deviceNameLength);
			free(deviceName);
			// Class
			payloadBt[10 + deviceNameLength] = deviceClassLength + 1;
			payloadBt[10 + deviceNameLength + 1] = 0x0D; // Service Name identifier
			memcpy(payloadBt + 8 + deviceNameLength + 4, deviceClass, deviceClassLength);
			free(deviceClass);

			// Build the NDEF message
			// NDEF header
			BYTE headerBt[] = { 0x12, strlen(MIME_BTPAIR), payloadBtLength };
			int headerBtLength = ARRAY_SIZE(headerBt);
			BYTE recordHs[] = { NDEF_NFCF_TYPE2, 15 + headerBtLength + strlen(MIME_BTPAIR) + payloadBtLength, 0x91, 0x02, 0x0A, 0x48, 0x73, 0x12, 0xD1, 0x02, 0x04, 0x61, 0x63, 0x01, 0x01, 0x30, 0x00 };
			BYTE recordHsLength = ARRAY_SIZE(recordHs);
			// NDEF message
			*length = recordHsLength + headerBtLength + strlen(MIME_BTPAIR) + payloadBtLength;
			memcpy(message, recordHs, recordHsLength);
			memcpy(message + recordHsLength, headerBt, headerBtLength);
			memcpy(message + recordHsLength + headerBtLength, MIME_BTPAIR, strlen(MIME_BTPAIR));
			memcpy(message + recordHsLength + headerBtLength + strlen(MIME_BTPAIR), payloadBt, payloadBtLength);
			message[recordHsLength + headerBtLength + strlen(MIME_BTPAIR) + payloadBtLength] = 0xFE;
			*length = recordHsLength + headerBtLength + strlen(MIME_BTPAIR) + payloadBtLength + 1;
			free(payloadBt);

			return SCARD_S_SUCCESS;
		}

		// Creates a SP-type NDEF message
		LONG NDEFRecord::createSPRecord(BYTE* payload, int payloadSize, BYTE* message, int* length)
		{
			LONG lReturn;
			BYTE uriType = 0;
			BYTE uriLength = 0;

			// Get strings
			BYTE titleLength = payload[0];
			BYTE *title = payload + 1;
			BYTE linkLength = payload[titleLength + 1];
			BYTE *link = payload + titleLength + 2;

			URI^ uri = gcnew URI();
			lReturn = URI::getUriIdentifier((char*)link, &uriType, &uriLength);
			
			if (lReturn == SCARD_S_SUCCESS)
			{
				// Recalculate the new size
				linkLength = linkLength - uriLength;

				// NDEF headers
				BYTE ndef_header[] = { NDEF_NFCF_TYPE2, titleLength + linkLength + 17, NDEF_TNF_SHORT, 0x02, titleLength + linkLength + 12, NDEF_SMARTPOSTER_TYPE, 0x70 };
				int ndefHeaderSize = ARRAY_SIZE(ndef_header);
				BYTE title_header[] = { 0x91, 0x01, titleLength + 3, 0x54, 0x02, 0x65, 0x6E };
				int titleHeaderSize = ARRAY_SIZE(title_header);
				BYTE link_header[] = { 0x51, 0x01, linkLength + 1, 0x55 };
				int linkHeaderSize = ARRAY_SIZE(link_header);

				// NDEF message
				memcpy(message, ndef_header, ndefHeaderSize);
				memcpy(message + ndefHeaderSize, title_header, titleHeaderSize);
				memcpy(message + ndefHeaderSize + titleHeaderSize, title, titleLength);
				memcpy(message + ndefHeaderSize + titleHeaderSize + titleLength, link_header, linkHeaderSize);
				message[ndefHeaderSize + titleHeaderSize + titleLength + linkHeaderSize] = uriType;
				memcpy(message + ndefHeaderSize + titleHeaderSize + titleLength + linkHeaderSize + 1, link + uriLength, linkLength);
				message[ndefHeaderSize + titleHeaderSize + titleLength + linkHeaderSize + 1 + linkLength] = 0xFE;
				*length = ndefHeaderSize + titleHeaderSize + titleLength + linkHeaderSize + 1 + linkLength + 1;
			}

			return lReturn;
		}

