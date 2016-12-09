#include "stdafx.h"
#include "EEPROM.h"
#include "URI.h"

using namespace NTAG_I2C_Demo; 

	int getMemSize(BYTE NtagVersion);
	void speedTest(int* nWrittenBytes, float* writeTime, int* nReadBytes, float* readTime, long lReturn, int ndefMessageSize, int memSize, BYTE* text, int chMultiplier);
	void resetMem(LONG lReturn, BYTE* rPage, BYTE* wPage, BYTE NtagVersion, float* resetTime, BYTE message, int length, int memSize);
	int checkMemSize(BYTE NtagVersion, DWORD* resetBytes);
	void fwFlash(int newFWLength, BYTE* newFW, BYTE* sectorFW, BYTE* cmd, BYTE* resp, long lReturn, SRAM* sram);

	RF_Commands* rf_cmd;

	EEPROM::EEPROM(RF_Commands* rf_in)
	{
		rf_cmd = rf_in;
	}

	LONG setAuth(std::string pass)
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

	long EEPROM::Read(BYTE* data, DWORD* readBytes, float* readTime)
	{
		LONG lReturn;
		
		int fetch_start = 0;

			// Initialize variables
			*readBytes = 0;

			// Check memory size
			BYTE NtagVersion;
			int memSize = 0;

			lReturn = rf_cmd->GET_VERSION(&NtagVersion);
			if (lReturn == SCARD_S_SUCCESS)
			{
				memSize = getMemSize(NtagVersion);

				*readTime = (float)clock();

				readMem(fetch_start, lReturn, memSize, data, readBytes);

				*readTime = (float)clock() - *readTime;

				// Check if we have gone to sector 1
				if ((fetch_start & 0xFF00) != 0)
					rf_cmd->END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
			}

		return lReturn;
	}

	long EEPROM::ResetMemory(DWORD* resetBytes, float* resetTime)
	{
		LONG lReturn;
		BYTE wPage[4] = { 0 };
		BYTE rPage[16];
		BYTE message[MAX_MEM_SIZE];
		int length;

			// Check memory size
			BYTE NtagVersion;
			lReturn = rf_cmd->GET_VERSION(&NtagVersion);
			if (lReturn == SCARD_S_SUCCESS)
			{

				int memSize = (checkMemSize(NtagVersion, resetBytes) + 16) / 4;

				*resetTime = (float)clock();

				resetMem(lReturn, rPage, wPage, NtagVersion, resetTime, message, length, memSize);
			}

		return lReturn;
	}

	long EEPROM::EEPROMSpeedTest(int chMultiplier, BYTE* text, int* nWrittenBytes, float* writeTime, int* nReadBytes, float* readTime)
	{
		LONG lReturn;
		BYTE NtagVersion;
		int memSize = 0;
		int ndefMessageSize;

			// Check memory size depending on the version
			lReturn = rf_cmd->GET_VERSION(&NtagVersion);
			if (lReturn == SCARD_S_SUCCESS)
			{
				memSize = getMemSize(NtagVersion);

				speedTest(nWrittenBytes, writeTime, nReadBytes, readTime, lReturn, ndefMessageSize, memSize, text, chMultiplier);
			}
			else
				lReturn = SCARD_E_INVALID_VALUE;
		
		return lReturn;
	};


	int EEPROM::getMemSize(BYTE NtagVersion)
	{
		int memSize;

		if (NtagVersion == NTAG_VERSION_1K)
			memSize = (NTAG_I2C_1k_MemSize + 16) / 4;
		else if (NtagVersion == NTAG_VERSION_2K)
			memSize = (NTAG_I2C_2k_MemSize + 16) / 4;
		else if (NtagVersion == NTAG_VERSION_1K_PLUS)
			memSize = (NTAG_I2C_PLUS_1k_MemSize + 16) / 4;
		else if (NtagVersion == NTAG_VERSION_2K_PLUS)
			memSize = (NTAG_I2C_PLUS_2k_MemSize + 16) / 4;

		return memSize;
	}

	void EEPROM::speedTest(int* nWrittenBytes, float* writeTime, int* nReadBytes, float* readTime, long lReturn, int ndefMessageSize, int memSize, BYTE* text, int chMultiplier)
	{
		
		// Build the NDEF message
		// NDEF payload
		int textSize = strlen((char*)text);
		int ndefPayloadSize = textSize*chMultiplier;
		int ndeftlvHeaderSize;
		BYTE* messageText = (BYTE*)malloc(ndefPayloadSize*sizeof(BYTE));
		BYTE* pnt;
		BYTE message[MAX_MEM_SIZE];

		for (pnt = messageText; pnt < messageText + ndefPayloadSize; pnt += textSize)
		{
			memcpy(pnt, text, textSize);
		}
		
		if (ndefPayloadSize + 7 > 255)
		{
			BYTE ndeftlv_header[] = { NDEF_NFCF_TYPE2, 0xFF, (BYTE)(floor((ndefPayloadSize + 10) / 256)), (BYTE)((ndefPayloadSize + 10) % 256), NDEF_TNF_LONG, 0x01, 0x00, 0x00, (BYTE)(floor((ndefPayloadSize + 3) / 256)), (BYTE)((ndefPayloadSize + 3) % 256), NDEF_TEXT_TYPE, 0x02, NDEF_TEXT_LANG_P1, NDEF_TEXT_LANG_P2 };
			ndeftlvHeaderSize = ARRAY_SIZE(ndeftlv_header);
			
			ndefMessageSize = ndeftlvHeaderSize + ndefPayloadSize;

			if (ndefMessageSize % 4 != 0)
				ndefMessageSize = ndefMessageSize + 4 - (ndefMessageSize % 4);
			
			memcpy(message, ndeftlv_header, ndeftlvHeaderSize);
			memcpy(message + ndeftlvHeaderSize, messageText, ndefPayloadSize);
			message[ndefMessageSize] = 0xFE;
		}
		else
		{
			BYTE ndeftlv_header[] = { NDEF_NFCF_TYPE2, ndefPayloadSize + 7, NDEF_TNF_SHORT, 0x01, ndefPayloadSize + 3, NDEF_TEXT_TYPE, 0x02, NDEF_TEXT_LANG_P1, NDEF_TEXT_LANG_P2 };
			ndeftlvHeaderSize = ARRAY_SIZE(ndeftlv_header);
		
			ndefMessageSize = ndeftlvHeaderSize + ndefPayloadSize;

			if (ndefMessageSize % 4 != 0)
				ndefMessageSize = ndefMessageSize + 4 - (ndefMessageSize % 4);

			memcpy(message, ndeftlv_header, ndeftlvHeaderSize);
			memcpy(message + ndeftlvHeaderSize, messageText, ndefPayloadSize);
			message[ndefMessageSize] = 0xFE;
		}

		// Check if the message fits in the NTAG memory
		if (ndefMessageSize + 32 < memSize * 4)	// The NDEF message starts at page 4
		{
			BYTE wPage[4];
			BYTE *p_ndef = message, *p_endndef = message + ndefMessageSize;

			// Execute write test
			*writeTime = (float)clock();

			// Write the bytes in the first sector
			int i = User_memory_Begin;
			while (i < 0x100 && p_ndef < p_endndef && lReturn == SCARD_S_SUCCESS)
			{
				memcpy(wPage, p_ndef, 4);
				if (this->auth) setAuth(this->pass_eeprom);
				lReturn = rf_cmd->WRITE(i, wPage);
				i++;
				p_ndef += 4;
			}
			// Check if there are more sectors
			if (p_ndef < p_endndef && lReturn == SCARD_S_SUCCESS)
			{
				lReturn = rf_cmd->SECTOR_SELECT(1);
				if (lReturn == SCARD_S_SUCCESS)
				{
					i = 0;
					while (p_ndef < p_endndef && lReturn == SCARD_S_SUCCESS)
					{
						memcpy(wPage, p_ndef, 4);
						if (this->auth) setAuth(this->pass_eeprom);
						lReturn = rf_cmd->WRITE(i, wPage);
						i++;
						p_ndef += 4;
					}
				}
				rf_cmd->END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
			}

			*writeTime = (float)clock() - *writeTime;
			if (lReturn == SCARD_S_SUCCESS)
			{
				int max_fast_read = (MAX_TRANSCEIVE_LENGTH - 2) / 4;
				int fetch_start = 4;
				int fetch_end;

				// Execute read test
				*readTime = (float)clock();

				// There is a limitation when trying to read more than 256 bytes
				// I split the fast reading in as many reads as I need
				while (fetch_start < (ndefMessageSize / 4) + 4 && lReturn == SCARD_S_SUCCESS)
				{
					fetch_end = fetch_start + max_fast_read - 1;

					// check for last read, fetch only rest
					if (fetch_end >= (ndefMessageSize / 4) + 3)
						fetch_end = (ndefMessageSize / 4) + 3;

					// check for sector change in between and reduce fast_read to stay within sector
					if ((fetch_start & 0xFF00) != (fetch_end & 0xFF00))
						fetch_end = (fetch_start & 0xFF00) + 0xFF;

					// fetch data
					if (this->auth) setAuth(this->pass_eeprom);
					lReturn = rf_cmd->FAST_READ(fetch_start & 0x00FF, fetch_end & 0x00FF, message);  // I don't care what I am reading, so I use the message variable because I won't use it anymore
					if (lReturn == SCARD_S_SUCCESS)
					{
						// calculate next fetch_start
						fetch_start = fetch_end + 1;

						// check for sector select needed
						if ((fetch_start & 0xFF00) != (fetch_end & 0xFF00))
							lReturn = rf_cmd->SECTOR_SELECT(1);
					}
				}

				*readTime = (float)clock() - *readTime;

				// Check if we have gone to sector 1
				if ((fetch_start & 0xFF00) != 0)
					rf_cmd->END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
				if (lReturn == SCARD_S_SUCCESS)
				{
					*nWrittenBytes = ndefMessageSize;
					*nReadBytes = ndefMessageSize;
				}
			}
		}
	}

	void EEPROM::readMem(int fetch_start, long lReturn, int memSize, BYTE* data, DWORD* readBytes)
	{
		int fetch_end = 0;
		int max_fast_read = (MAX_TRANSCEIVE_LENGTH - 2) / 4;

		// There is a limitation when trying to read more than 256 bytes 
		// I split the fast reading in as many reads as I need
		do
		{
			fetch_end = fetch_start + max_fast_read - 1;

			// check for last read, fetch only rest
			if (fetch_end >= memSize)
				fetch_end = memSize;

			// check for sector change in between and reduce fast_read to stay within sector
			if ((fetch_start & 0xFF00) != (fetch_end & 0xFF00))
				fetch_end = (fetch_start & 0xFF00) + 0xFF;

			// fetch data
			lReturn = rf_cmd->FAST_READ(fetch_start & 0x00FF, fetch_end & 0x00FF, data + *readBytes);
			if (lReturn == SCARD_S_SUCCESS)
			{
				*readBytes += (fetch_end - fetch_start + 1) * 4;

				// calculate next fetch_start
				fetch_start = fetch_end + 1;

				// check for sector select needed
				if ((fetch_start & 0xFF00) != (fetch_end & 0xFF00))
					lReturn = rf_cmd->SECTOR_SELECT(1);
			}
		} while (fetch_start <= memSize && lReturn == SCARD_S_SUCCESS);

		//END_SECTOR_SELECT in case we are in the 2K memory
		rf_cmd->END_SECTOR_SELECT();
	}

	// Reads the full memory of the NTAG (the first four pages, the user memory and the dynamic lock bytes)

	int EEPROM::checkMemSize(BYTE NtagVersion, DWORD* resetBytes)
	{
		if (NtagVersion == NTAG_VERSION_1K)
		{
			*resetBytes = NTAG_I2C_1k_MemSize;
			return NTAG_I2C_1k_MemSize;
		}
		else if (NtagVersion == NTAG_VERSION_2K)
		{
			*resetBytes = NTAG_I2C_2k_MemSize;
			return NTAG_I2C_2k_MemSize;
		}
		else if (NtagVersion == NTAG_VERSION_1K_PLUS)
		{
			*resetBytes = NTAG_I2C_PLUS_1k_MemSize;
			return NTAG_I2C_PLUS_1k_MemSize;
		}
		else if (NtagVersion == NTAG_VERSION_2K_PLUS)
		{
			*resetBytes = NTAG_I2C_PLUS_2k_MemSize;
			return NTAG_I2C_PLUS_2k_MemSize;
		}
	}

	BYTE EEPROM::Write(LONG lReturn, BYTE* rPage, BYTE* wPage, float* resetTime, BYTE* message, int length, int memSize, BYTE NtagVersion)
	{
		BYTE res;

		NDEFmsg* ndefmsg = new NDEFmsg(rf_cmd);

		Registers* reg = new Registers(rf_cmd);

		BYTE tmp[4];

		int payloadSize;

		if (this->auth) setAuth(this->pass_eeprom);
		lReturn = rf_cmd->WRITE(3, wPage);
		if (lReturn == SCARD_S_SUCCESS)
		{
			// Check if it has been written succesfully
			if (this->auth) setAuth(this->pass_eeprom);
			lReturn = rf_cmd->READ(3, rPage);
			if (lReturn == SCARD_S_SUCCESS)
			{
				if (rPage[0] == wPage[0] && rPage[1] == wPage[1] && rPage[2] == wPage[2] && rPage[3] == wPage[3])
				{
					// Write the whole first sector
					int i = User_memory_Begin;
					wPage[0] = 0;
					wPage[1] = 0;
					wPage[2] = 0;
					wPage[3] = 0;
					do
					{
						if ((NtagVersion == NTAG_VERSION_1K_PLUS) || (NtagVersion == NTAG_VERSION_2K_PLUS))
						{
							switch (i)
							{
							case AUTH0_PAGE: //Clean AUTH0
								tmp[0] = 0x00;
								tmp[1] = 0x00;
								tmp[2] = 0x00;
								tmp[3] = CLEAN_AUTH0;
								if (this->auth) setAuth(this->pass_eeprom);
								if (rf_cmd->WRITE(AUTH0_PAGE, tmp) == SCARD_S_SUCCESS)
								{
									lReturn = SCARD_S_SUCCESS;
								}
								break;
							case PWD_PAGE: //Clean password
								tmp[0] = 0xFF;
								tmp[1] = 0xFF;
								tmp[2] = 0xFF;
								tmp[3] = 0xFF;
								if (this->auth) setAuth(this->pass_eeprom);
								if (lReturn = rf_cmd->WRITE(PWD_PAGE, tmp) == SCARD_S_SUCCESS)
								{
									lReturn = SCARD_S_SUCCESS;
								}
								break;
							case ACCESS_PAGE: //Clean ACCESS
								tmp[0] = CLEAN_ACCESS;
								tmp[1] = 0x00;
								tmp[2] = 0x00;
								tmp[3] = 0x00;
								if (this->auth) setAuth(this->pass_eeprom);
								if (rf_cmd->WRITE(ACCESS_PAGE, tmp) == SCARD_S_SUCCESS)
								{
									lReturn = SCARD_S_SUCCESS;
								}
								break;
							case PT_I2C_PAGE: //Clean PT_I2C
								tmp[0] = CLEAN_PT_I2C;
								tmp[1] = 0x00;
								tmp[2] = 0x00;
								tmp[3] = 0x00;
								if (this->auth) setAuth(this->pass_eeprom);
								if (rf_cmd->WRITE(PT_I2C_PAGE, tmp) == SCARD_S_SUCCESS)
								{
									lReturn = SCARD_S_SUCCESS;
								}
								break;
							case PACK_PAGE: //Clean PACK
								tmp[0] = 0x00;
								tmp[1] = 0x00;
								tmp[2] = 0x00;
								tmp[3] = 0x00;
								if (this->auth) setAuth(this->pass_eeprom);
								if (rf_cmd->WRITE(PACK_PAGE, tmp) == SCARD_S_SUCCESS)
								{
									lReturn = SCARD_S_SUCCESS;
								}
								break;
							default:
								if (this->auth) setAuth(this->pass_eeprom);
								lReturn = rf_cmd->WRITE(i, wPage); 
								break;
							}
						}
						else
						{
							if (this->auth) setAuth(this->pass_eeprom);
							lReturn = rf_cmd->WRITE(i, wPage);
						}
						i++;
						if (((NtagVersion == NTAG_VERSION_1K_PLUS) || (NtagVersion == NTAG_VERSION_2K_PLUS)) && i == 232) break; //Stop right before the config registers
					} while (i < 0x100 && i < memSize && lReturn == SCARD_S_SUCCESS);

					// Check if there are more sectors
					if (memSize > 0x100 && lReturn == SCARD_S_SUCCESS)
					{
						lReturn = rf_cmd->SECTOR_SELECT(1);
						i = 0;
						while ((i < memSize - 0x100) && lReturn == SCARD_S_SUCCESS)
						{
							if (this->auth) setAuth(this->pass_eeprom);
							lReturn = rf_cmd->WRITE(i, wPage);
							i++;
						}
						rf_cmd->END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
					}
					
					if (lReturn == SCARD_S_SUCCESS)
					{
						// Create the default NDEF message to be written into the tag memory

						BYTE payload[MAX_MEM_SIZE];

						payload[0] = strlen("NTAG I2C EXPLORER");
						memcpy(payload + 1, "NTAG I2C EXPLORER", strlen("NTAG I2C EXPLORER"));
						payload[1 + strlen("NTAG I2C EXPLORER")] = strlen("http://www.nxp.com/demoboard/OM5569");
						memcpy(payload + 1 + strlen("NTAG I2C EXPLORER") + 1, "http://www.nxp.com/demoboard/OM5569", strlen("http://www.nxp.com/demoboard/OM5569"));
						payload[1 + strlen("NTAG I2C EXPLORER") + 1 + strlen("http://www.nxp.com/demoboard/OM5569")] = '\0'; // Title Length + Title + Link Length + Link
						payloadSize = 1 + strlen("NTAG I2C EXPLORER") + 1 + strlen("http://www.nxp.com/demoboard/OM5569");
						
						//LONG lReturn;
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
							length = ndefHeaderSize + titleHeaderSize + titleLength + linkHeaderSize + 1 + linkLength + 1;
						}
						
						if (lReturn == SCARD_S_SUCCESS)
						{
							// Append the AAR to the NDEF message

							// AAR header
							BYTE AARheader[] = { 0x54, 0x0F, 0x13 };
							int AARheaderSize = ARRAY_SIZE(AARheader);

							// AAR text
							BYTE AARtext[] = "android.com:pkgcom.nxp.ntagi2cdemo";
							int AARtextSize = ARRAY_SIZE(AARtext) - 1;	// We don't count here the '\0' at the end

							// NDEF message
							memcpy(message + length - 1, AARheader, AARheaderSize);
							memcpy(message + length - 1 + AARheaderSize, AARtext, AARtextSize);
							message[length - 1 + AARheaderSize + AARtextSize] = 0xFE;
							length += AARheaderSize + AARtextSize;
							message[1] += AARheaderSize + AARtextSize;
							message[2] = 0x91;

							if (lReturn == SCARD_S_SUCCESS)
							{
								// Write the NDEF message to the tag
								if (this->auth) setAuth(this->pass_eeprom);
								lReturn = ndefmsg->WriteNdefMessage(message, length);
								if (lReturn == SCARD_S_SUCCESS)
								{
									// Check configuration lock bit via RF
									Ntag_I2C_Registers_t configReg;
									lReturn = reg->GetConfigRegisters(&configReg);
									if (lReturn == SCARD_S_SUCCESS)
									{
										lReturn = SCARD_P_CONFIG_LOCKED;
										if (configReg.REG_EEPROM_WR_BUSY == FALSE)	// It is the same bit in the session registers
										{
											// Change the config registers to their default value
											configReg.REG_I2C_RST_ON_OFF = FALSE;
											memcpy(configReg.REG_FD_OFF, "00b", 3);
											memcpy(configReg.REG_FD_ON, "00b", 3);
											configReg.REG_PTHRU_DIR = TRUE;
											configReg.REG_LAST_NDEF_PAGE = 0;
											configReg.REG_SM_Reg = 0xF8;
											configReg.REG_WD_LS_Reg = 0x48;
											configReg.REG_WD_MS_Reg = 0x08;
											configReg.REG_I2C_CLOCK_STR = TRUE;
											configReg.REG_I2C_LOCKED = FALSE;
											configReg.REG_RF_LOCKED = FALSE;
											if (this->auth) setAuth(this->pass_eeprom);
											lReturn = reg->SetConfigRegisters(configReg);

											res = SCARD_S_SUCCESS;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		return res;
	}

	void EEPROM::writeCapabilityContainer(BYTE* wPage, BYTE NtagVersion, LONG lReturn, BYTE* rPage, float* resetTime, BYTE* message, int length, int memSize)
	{
		// Try writing the Capability Container
		if (NtagVersion == NTAG_VERSION_2K || NtagVersion == NTAG_VERSION_2K_PLUS)
		{
			// CC for NTAG 2k or plus 2k
			wPage[0] = 0xE1;
			wPage[1] = 0x10;
			wPage[2] = 0xEA;
			wPage[3] = 0x00;
		}
		else
		{
			// CC for NTAG 1k or plus 1k
			wPage[0] = 0xE1;
			wPage[1] = 0x10;
			wPage[2] = 0x6D;
			wPage[3] = 0x00;
		}

		if (Write(lReturn, rPage, wPage, resetTime, message, length, memSize, NtagVersion) == SCARD_S_SUCCESS)
		{
			*resetTime = (float)clock() - *resetTime;
		}

	}

	void EEPROM::checkDynLockBytes(LONG lReturn, BYTE* rPage, BYTE* wPage, BYTE NtagVersion, float* resetTime, BYTE* message, int length, int memSize)
	{
		// Check dynamic lock bytes
		if (NtagVersion == NTAG_VERSION_2K)
		{
			lReturn = rf_cmd->SECTOR_SELECT(1);
			if (lReturn == SCARD_S_SUCCESS)
				lReturn = rf_cmd->READ(0xE0, rPage);
			rf_cmd->END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
		}
		else{
			lReturn = rf_cmd->READ(0xE2, rPage);
		}

		if (lReturn == SCARD_S_SUCCESS)
		{
			lReturn = SCARD_P_DYNAMIC_LOCKED;
			if (rPage[0] == 0 && rPage[1] == 0 && rPage[2] == 0)
			{
				writeCapabilityContainer(wPage, NtagVersion, lReturn, rPage, resetTime, message, length, memSize);
			}
		}
	}

	void EEPROM::checkStaticLockBytes(LONG lReturn, BYTE* rPage, BYTE* wPage, BYTE NtagVersion, float* resetTime, BYTE* message, int length, int memSize)
	{
		lReturn = SCARD_P_STATIC_LOCKED;
		if (rPage[2] == 0 && rPage[3] == 0)
		{
			checkDynLockBytes(lReturn, rPage, wPage, NtagVersion, resetTime, message, length, memSize);
		}
	}

	void EEPROM::resetMem(LONG lReturn, BYTE* rPage, BYTE* wPage, BYTE NtagVersion, float* resetTime, BYTE* message, int length, int memSize)
	{
		// Check static lock bytes
		lReturn = rf_cmd->READ(2, rPage);
		if (lReturn == SCARD_S_SUCCESS)
		{
			checkStaticLockBytes(lReturn, rPage, wPage, NtagVersion, resetTime, message, length, memSize);
		}
	}

	bool EEPROM::isReturnSuccess(LONG response){
		return (response == SCARD_S_SUCCESS);
	}