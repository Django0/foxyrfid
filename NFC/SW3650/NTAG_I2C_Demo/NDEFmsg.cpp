#include "stdafx.h"
#include "NDEFmsg.h"
#include "NDEFRecord.h"
#include "URI.h"

using namespace NTAG_I2C_Demo;

using namespace System;

		NDEFmsg::NDEFmsg(RF_Commands *rf_in)
		{
			rf_cmd = rf_in;
		}

		LONG NDEFmsg::setAuthentication(std::string pass)
		{
			LONG lReturn;
			BYTE password_bytes[4];

			if (pass == "SUN")
			{
				password_bytes[0] = 0xFF;
				password_bytes[1] = 0xFF;
				password_bytes[2] = 0xFF;
				password_bytes[3] = 0xFF;
			}
			else if (pass == "STAR")
			{
				password_bytes[0] = 0x55;
				password_bytes[1] = 0x55;
				password_bytes[2] = 0x55;
				password_bytes[3] = 0x55;
			}
			else if (pass == "MOON")
			{
				password_bytes[0] = 0xAA;
				password_bytes[1] = 0xAA;
				password_bytes[2] = 0xAA;
				password_bytes[3] = 0xAA;
			}

			lReturn = rf_cmd->PWD_AUTH(password_bytes);

			return lReturn;
		}

		LONG NDEFmsg::ReadNdef(int* NdefType, BYTE* payload, int* payloadSize, BOOL *AARPresent, BYTE* AAR, int*AARSize, DWORD* readBytes, float* readTime)
		{
			LONG lReturn;
			BYTE data[MAX_MEM_SIZE];
			int length;
			*payloadSize = 0;
			
				*readTime = (float)clock();
				// Get the NDEF message
				lReturn = ReadNdefMessage(data, &length);
				
				*readBytes = (int)ceil((float)(length + 6) / 16) * 16;	// Bytes are read 16 by 16
				DWORD temp = *readBytes;
				if (isReturnSuccess(lReturn))
				{
					// The TNF is defined in the last three bits of the first byte of the NDEF Message
					BYTE TNF = data[0] & 0x07;
					BYTE typeLength = data[1];
					int payloadLength = data[2];
					int offset = 0;
					if (data[0] == 0xC1)
					{
						payloadLength = data[4];
						payloadLength = payloadLength * 256;
						payloadLength = payloadLength + data[5];
						offset = 3;
					}
					
					// From byte 3, the NDEF type is defined as an string of length typeLength
					BYTE* Type = (BYTE*)malloc((typeLength + 1)*sizeof(BYTE));
					memcpy(Type, data + 3 + offset, typeLength);
					Type[typeLength] = '\0';

					// Get the message and message type
					if (TNF == TNF_WELL_KNOWN)
					{
						// Check if it is a text-type NDEF message
						int comp = strcmp((char*)Type, RTD_TEXT);
						if (comp == 0)
						{
							*NdefType = TYPE_NDEF_TEXT;

							// We ignore the language information bytes in the payload (3bytes)
							*payloadSize = payloadLength - 3;
							int header_length = 3 + typeLength + 3 + offset;
							memcpy(payload, data + header_length, *payloadSize);
						}
						else
						{
							// Check if it is an URI-type NDEF message
							comp = strcmp((char*)Type, RTD_URI);
							if (comp == 0)
							{
								*NdefType = TYPE_NDEF_URI;

								// The first byte in the URI payload indicates the type of URI stored
								char uriType[30];
								BYTE uriLength;

								lReturn = URI::getUriType(data[3 + typeLength + offset], uriType, &uriLength);

								if (isReturnSuccess(lReturn))
								{
									*payloadSize = uriLength + payloadLength - 1;
									memcpy(payload, uriType, uriLength);
									memcpy(payload + uriLength, data + 3 + typeLength + 1 + offset, payloadLength - 1);
								}
							}
							else
							{
								// Check if it is a Bluetooth handover-type NDEF message
								comp = strcmp((char*)Type, RTD_HS);
								if (comp == 0)
								{
									*NdefType = TYPE_NDEF_BTPAIR;

									// Skip the HS Record header
									char* btRecord = (char*)data + 5 + data[2];
									payload[0] = btRecord[1];
									btRecord += 3;
									memcpy(payload + 1, btRecord, payload[0]);
									if (strncmp(btRecord, MIME_BTPAIR, strlen(MIME_BTPAIR)) == 0)
									{
										// It is a Bluetooth pairing record
										NDEFRecord::parseBTPairRecord(btRecord + strlen(MIME_BTPAIR), (char*)payload + 1 + strlen(MIME_BTPAIR), payloadSize);	// It always returns SCARD_S_SUCCESS
										*payloadSize += 1 + strlen(MIME_BTPAIR);
									}
									else
									{
										payload[1 + strlen(MIME_BTPAIR)] = 0;
										*payloadSize = 1 + strlen(MIME_BTPAIR);
									}
								}
								else
								{
									// Check if it is a Smart Poster-type NDEF message
									comp = strcmp((char*)Type, RTD_SP);
									if (comp == 0)
									{
										*NdefType = TYPE_NDEF_SP;

										// The first element in the Smart Poster should be Text-type
										if (data[3 + typeLength] == 0x91 && data[3 + typeLength + 1] == 0x01 && data[3 + typeLength + 3] == 'T')
										{
											// We ignore the language information bytes in the payload (3bytes)
											payload[0] = data[3 + typeLength + 2] - 3;
											*payloadSize = payload[0] + 1;
											memcpy(payload + 1, data + 3 + typeLength + 4 + 3, payload[0]);

											// The second element in the Smart Poster should be URI type
											if (data[3 + typeLength + 4 + 3 + payload[0]] == 0x51 && data[3 + typeLength + 4 + 3 + payload[0] + 1] == 0x01 && data[3 + typeLength + 4 + 3 + payload[0] + 3] == 'U')
											{
												// The first byte in the URI payload indicates the type of URI stored
												char uriType[30];
												BYTE uriLength;

												lReturn = URI::getUriType(data[3 + typeLength + 4 + 3 + payload[0] + 4], uriType, &uriLength);

												if (isReturnSuccess(lReturn))
												{
													payload[*payloadSize] = uriLength + data[3 + typeLength + 4 + 3 + payload[0] + 2] - 1;
													memcpy(payload + *payloadSize + 1, uriType, uriLength);
													memcpy(payload + *payloadSize + 1 + uriLength, data + 3 + typeLength + 4 + 3 + payload[0] + 5, data[3 + typeLength + 4 + 3 + payload[0] + 2] - 1);
													*payloadSize += uriLength + data[3 + typeLength + 4 + 3 + payload[0] + 2] - 1 + 1;
												}
											}
											else
												lReturn = SCARD_E_INVALID_TARGET;
										}
										else
											lReturn = SCARD_E_INVALID_TARGET;
									}
									else
										lReturn = SCARD_E_INVALID_TARGET;
								}
							}
						}
					}
					// This way it can also be a Bluetooth handover type NDEF message
					else if (TNF == TNF_MIME_TYPE)
					{
						*NdefType = TYPE_NDEF_BTPAIR;

						// Skip the HS Record header
						char* btRecord = (char*)data + 5 + data[2];
						payload[0] = btRecord[1];
						btRecord += 3;
						memcpy(payload + 1, btRecord, payload[0]);
						if (strncmp(btRecord, MIME_BTPAIR, strlen(MIME_BTPAIR)) == 0)
						{
							// It is a Bluetooth pairing record
							NDEFRecord::parseBTPairRecord(btRecord + strlen(MIME_BTPAIR), (char*)payload + 1 + strlen(MIME_BTPAIR), payloadSize);	// It always returns SCARD_S_SUCCESS
							*payloadSize += 1 + strlen(MIME_BTPAIR);
						}
						else
						{
							payload[1 + strlen(MIME_BTPAIR)] = 0;
							*payloadSize = 1 + strlen(MIME_BTPAIR);
						}
					}
					else
						lReturn = SCARD_E_INVALID_TARGET;

					//Check if the NDEF message contains an AAR at the end
					// For text, URI and Smart Poster type NDEFs, if we store them without an AAR, data[0] is 0xD1 (one record), while if we store them with an AAR, data[0] is 0x91 (two records)
					// For BT Pairing type NDEFs, data[0] is 0x91 in both cases (two records without AAR and three records with AAR)
					if (data[0] == 0x91 && isReturnSuccess(lReturn))
					{
						char* aarRecord = NULL;
						if (*NdefType == TYPE_NDEF_BTPAIR)
						{
							if (length > 3 + typeLength + payloadLength + 3 + data[3 + typeLength + payloadLength + 1] + data[3 + typeLength + payloadLength + 2])
								aarRecord = strstr((char*)(data + 3 + typeLength + payloadLength + 3 + data[3 + typeLength + payloadLength + 1] + data[3 + typeLength + payloadLength + 2] + 3), "android.com:pkg");
						}
						else
							aarRecord = strstr((char*)(data + 3 + typeLength + payloadLength + 3), "android.com:pkg");
						if (aarRecord != NULL)
						{
							*AARPresent = TRUE;
							*AARSize = data - (BYTE*)aarRecord + length - strlen("android.com:pkg");
							memcpy(AAR, aarRecord + strlen("android.com:pkg"), *AARSize);
						}
					}
					*readTime = (float)clock() - *readTime;

					free(Type);
				}
			
			return lReturn;
		}

		// Writes the NDEF type indicated with the content indicated
		LONG NDEFmsg::WriteNdef(int NdefType, BYTE* payload, int payloadSize, BOOL addAAR, DWORD* writeBytes, float* writeTime)
		{
			LONG lReturn;
			SRAM *sram = new SRAM(rf_cmd);
			BYTE message[MAX_MEM_SIZE];
			int length;
			
				*writeTime = (float)clock();
				// Create the NDEF message
				switch (NdefType)
				{
				case TYPE_NDEF_TEXT:
					lReturn = NDEFRecord::createTextRecord(payload, payloadSize, message, &length);
					break;
				case TYPE_NDEF_URI:
					lReturn = NDEFRecord::createUriRecord(payload, payloadSize, message, &length);
					break;
				case TYPE_NDEF_BTPAIR:
					lReturn = NDEFRecord::createBTPairRecord(payload, payloadSize, message, &length);
					break;
				case TYPE_NDEF_SP:
					lReturn = NDEFRecord::createSPRecord(payload, payloadSize, message, &length);
					break;
				}
				if (isReturnSuccess(lReturn))
				{
					// If required, append the AAR to the NDEF message
					if (addAAR)
						lReturn = AppendAAR(message, &length);
					if (isReturnSuccess(lReturn))
					{
						// Write the NDEF message to the tag
						lReturn = WriteNdefMessage(message, length);
						*writeTime = (float)clock() - *writeTime;
						*writeBytes = (int)ceil((float)(length) / 4) * 4; // Bytes are writen 4 by 4
						if (isReturnSuccess(lReturn))
						{
							// Inform the BoardDemo about the new NDEF message that has been stored
							BYTE wData[NTAG_MEM_SIZE_SRAM] = { 0 };
							wData[60] = 'N';
							sram->WriteSram(wData);
						}
					}
				}
				
			return lReturn;
		}

		// Reads an NDEF message from the tag
		LONG NDEFmsg::ReadNdefMessage(BYTE* data, int* length)
		{
			LONG lReturn;
			BYTE cc[16];
			int aux,i;
			BYTE* pos;

			if (this->auth)
			{
				setAuthentication(this->pass_ndef);
			}
			// Check that in page 3 there is the NDEF Magic Number, that in page 4 the tag field is an NDEF message, and the length of the NDEF message
			lReturn = rf_cmd->READ(3, cc);
			if (isReturnSuccess(lReturn) && cc[0] == 0xE1 && cc[4] == 0x03)
			{
				if (cc[5] == 0xFF)
				{
					aux = cc[6];
					*length = aux * 256 + (int)cc[7];
					// Copy into data the bytes of the NDEF message that I already have
					memcpy(data, cc + 8, 8);
					// Send read commands until I have read the whole NDEF
					
					i = (int)ceil(((float)(*length - 8 + 1)) / 16);
					pos = data + 8;
				}
				else{
					*length = cc[5];

					// Copy into data the bytes of the NDEF message that I already have
					memcpy(data, cc + 6, 10);
					// Send read commands until I have read the whole NDEF
					i = (int)ceil(((float)(*length - 10 + 1)) / 16);
					pos = data + 10;
				}
				
				BYTE page = 7;
				while (i > 0 && isReturnSuccess(lReturn))
				{
					lReturn = rf_cmd->READ(page, pos);
					i--;
					pos += 16;
					page += 4;
				}
				
			}
			else if (isReturnSuccess(lReturn))	// If the tag is not NDEF formatted
				lReturn = SCARD_E_INVALID_TARGET;

			return lReturn;
		}

		// Writes an NDEF message into the tag
		LONG NDEFmsg::WriteNdefMessage(BYTE* data, int length)
		{
			LONG lReturn;
			BYTE cc[16];

			if (this->auth)
			{
				setAuthentication(this->pass_ndef);
			}
			// Check that in page 3 there is the NDEF Magic Number
			lReturn = rf_cmd->READ(3, cc);
			if (isReturnSuccess(lReturn) && cc[0] == 0xE1)
			{
				// Send write commands until I have written the whole NDEF
				int i = (int)ceil(((float)(length)) / 4);
				BYTE* pos = data;
				BYTE page = 4;
				data[length] = 0x00;
				data[length + 1] = 0x00;
				data[length + 2] = 0x00;
				while (i > 0 && isReturnSuccess(lReturn))
				{
					if (this->auth)
					{
						setAuthentication(this->pass_ndef);
					}
					lReturn = rf_cmd->WRITE(page, pos);
					i--;
					pos += 4;
					page++;
				}
			}
			else if (isReturnSuccess(lReturn))	// If the tag is not NDEF formatted
				lReturn = SCARD_E_INVALID_TARGET;

			return lReturn;
		}

		BYTE* NDEFmsg::CreateDefaultNDEFmessage(){
			BYTE payload[MAX_MEM_SIZE];
			payload[0] = strlen("NTAG I2C EXPLORER");
			memcpy(payload + 1, "NTAG I2C EXPLORER", strlen("NTAG I2C EXPLORER"));
			payload[1 + strlen("NTAG I2C EXPLORER")] = strlen("http://www.nxp.com/demoboard/OM5569");
			memcpy(payload + 1 + strlen("NTAG I2C EXPLORER") + 1, "http://www.nxp.com/demoboard/OM5569", strlen("http://www.nxp.com/demoboard/OM5569"));
			payload[1 + strlen("NTAG I2C EXPLORER") + 1 + strlen("http://www.nxp.com/demoboard/OM5569")] = '\0'; // Title Length + Title + Link Length + Link
			return payload;
		}

		// Appends an AAR to an NDEF message
		LONG NDEFmsg::AppendAAR(BYTE* message, int* length)
		{
			// AAR header
			BYTE AARheader[] = { 0x54, 0x0F, 0x13 };
			int AARheaderSize = ARRAY_SIZE(AARheader);

			// AAR text
			BYTE AARtext[] = "android.com:pkgcom.nxp.ntagi2cdemo";
			int AARtextSize = ARRAY_SIZE(AARtext) - 1;	// We don't count here the '\0' at the end

			// NDEF message
			memcpy(message + *length - 1, AARheader, AARheaderSize);
			memcpy(message + *length - 1 + AARheaderSize, AARtext, AARtextSize);
			message[*length - 1 + AARheaderSize + AARtextSize] = 0xFE;
			*length += AARheaderSize + AARtextSize;
			message[1] += AARheaderSize + AARtextSize;
			message[2] = 0x91;

			return SCARD_S_SUCCESS;
		};

		// Creates a SP-type NDEF message
		LONG NDEFmsg::createSPRecord(BYTE payload[], int payloadSize, BYTE* message, int* length)
		{
			LONG lReturn;
			BYTE uriType = 0;
			BYTE uriLength = 0;

			// Get strings
			BYTE titleLength = payload[0];
			BYTE *title = payload + 1;
			BYTE linkLength = payload[titleLength + 1];
			BYTE *link = payload + titleLength + 2;

			// We have to filter the URI type and get the appropriate URI Identifier
			lReturn = URI::getUriIdentifier((char*)link, &uriType, &uriLength);
			if (isReturnSuccess(lReturn))
			{
				// Recalculate the new size
				linkLength = linkLength - uriLength;

				// NDEF headers
				BYTE ndef_header[] = { 0x03, titleLength + linkLength + 17, 0xD1, 0x02, titleLength + linkLength + 12, 0x53, 0x70 };
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
	
		bool NDEFmsg::isReturnSuccess(LONG response){
			return (response == SCARD_S_SUCCESS);
		}

		int NDEFmsg::numberBytes2Write(int payloadNDEFSize){
			int result;
			if (payloadNDEFSize + 7 > 255){
				result = 14 + payloadNDEFSize;
			}
			else{
				result = 9 + payloadNDEFSize;
			}
			
			if (result % 4 != 0){
				result = result + 4 - (result % 4);
			}
			return result;
		}