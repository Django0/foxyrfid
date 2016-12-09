#include "stdafx.h"
#include "RF_Commands.h"
#include "Reader.h"

using namespace NTAG_I2C_Demo;

//                ->APDU header <-          ->payload lenght<-                    ->payload<-
//BYTE cmd[] = { 0xFF, 0xEF, 0x00, 0x00,         0x06,             CMD_WRITE, 0x00, 0x00, 0x00, 0x00, 0x00 };

		RF_Commands::RF_Commands(){
			sCardReader = new Reader();
			selectedSector = 0;
		}

		RF_Commands::RF_Commands(LPCTSTR readerIdentifierString){
			sCardReader = new Reader(readerIdentifierString);
			selectedSector = 0;
		}

		// Gets the version of the NTAG I2C IC
		LONG RF_Commands::GET_VERSION(BYTE* version)
		{
			LONG lReturn;
			BYTE cmdGetVersion[] = { 0xFF, 0xEF, 0x00, 0x00, 0x01, CMD_GET_VERSION };
			DWORD cmdLength = sizeof(cmdGetVersion);
			DWORD respLength = CMD_GET_VERSION_RESP_LENGTH;
			BYTE respGetVersion[CMD_GET_VERSION_RESP_LENGTH];

			lReturn = sCardReader->cardTransmit(cmdGetVersion, cmdLength, NULL, respGetVersion, &respLength);

			if (isReturnSuccess(lReturn)){
				if (isResponseLengthAsExpected(respLength, CMD_GET_VERSION_RESP_LENGTH))
					lReturn = getVersion(respGetVersion[6], respGetVersion[5], respGetVersion[4], version);
				else
					lReturn = SCARD_E_COMM_DATA_LOST;
			}

			return lReturn;
		};

		/* Disables the polling and selects the sector passed as parameter
		Note that it is necessary to execute the END_SECTOR_SELECT function later, to enable the polling again and to go back to sector 0 */
		LONG RF_Commands::SECTOR_SELECT(BYTE nb_sector)
		{
			if (nb_sector == selectedSector) //If the tag is already in sector 0, there is no need to perform SECTOR_SELECT(1)
				return 0;
			LONG lReturn;

			BYTE cmdDisablePolling[] = { CMD_DISABLE_POLLING };
			DWORD cmdDisableLength = sizeof(cmdDisablePolling);
			BYTE respDisablePolling[CMD_DISABLE_POLLING_RESP_LENGTH];
			DWORD respDisableLength = CMD_DISABLE_POLLING_RESP_LENGTH;

			BYTE cmdSectorSelect0[] = { 0xFF, 0xEF, 0x00, 0x00, 0x02, CMD_SECTOR_SELECT, 0xFF };
			DWORD cmdSS0Length = sizeof(cmdSectorSelect0);
			BYTE respSectorSelect0[CMD0_SECTOR_SELECT_RESP_LENGTH];
			DWORD respSS0Length = CMD0_SECTOR_SELECT_RESP_LENGTH;

			BYTE cmdSectorSelect1[] = { CMD1_SECTOR_SELECT };
			DWORD cmdSS1Length = sizeof(cmdSectorSelect1);
			BYTE respSectorSelect1[CMD1_SECTOR_SELECT_RESP_LENGTH];
			DWORD respSS1Length = CMD1_SECTOR_SELECT_RESP_LENGTH;

			lReturn = sCardReader->cardTransmit(cmdDisablePolling, cmdDisableLength, NULL, respDisablePolling, &respDisableLength);

			if (isReturnSuccess(lReturn) && respDisableLength == 2 && respDisablePolling[0] == 0x90 && respDisablePolling[1] == 0x00)
			{
				// Send the first command of Sector Select
				lReturn = sCardReader->cardTransmit(cmdSectorSelect0, cmdSS0Length, NULL, respSectorSelect0, &respSS0Length);

				if (isReturnSuccess(lReturn) && respSS0Length == 1 && respSectorSelect0[0] == 0x0A)
				{
					// Send the second command of the sector select, indicating the sector
					cmdSectorSelect1[5] = nb_sector;
					lReturn = sCardReader->cardTransmit(cmdSectorSelect1, cmdSS1Length, NULL, respSectorSelect1, &respSS1Length);

					// Check if an error has occurred even though lReturn indicates success
					if (isReturnSuccess(lReturn) && respSS1Length != 0)
						lReturn = SCARD_E_COMM_DATA_LOST;
				}
				else if (isReturnSuccess(lReturn))
					lReturn = SCARD_E_COMM_DATA_LOST;
			}
			else if (isReturnSuccess(lReturn))
				lReturn = SCARD_E_COMM_DATA_LOST;

			return lReturn;
		}

		LONG RF_Commands::END_SECTOR_SELECT()	// Enables the polling and goes back to sector 0
		{
			LONG lReturn;

			BYTE cmdEnablePolling[] = { CMD_ENABLE_POLLING };
			DWORD cmdEnableLength = sizeof(cmdEnablePolling);
			BYTE respEnablePolling[CMD_ENABLE_POLLING_RESP_LENGTH];
			DWORD respEnablePollingLength = CMD_ENABLE_POLLING_RESP_LENGTH;

			BYTE cmdError[] = { CMD_ERROR };
			DWORD cmdErrorLength = sizeof(cmdError);
			BYTE respError[CMD_ERROR_RESP_LENGTH];
			DWORD respErrorLength = CMD_ERROR_RESP_LENGTH;

			// Enable polling
			lReturn = sCardReader->cardTransmit(cmdEnablePolling, cmdEnableLength, NULL, respEnablePolling, &respEnablePollingLength);

			// Check if an error has occurred even though lReturn indicates success
			if (isReturnSuccess(lReturn) && (respEnablePollingLength != CMD_ERROR_RESP_LENGTH || checkStatusWordSuccess(respEnablePolling, 0))){ 
				lReturn = SCARD_E_COMM_DATA_LOST;
			}

			lReturn = sCardReader->cardTransmit(cmdError, cmdErrorLength, NULL, respError, &respErrorLength);

			return lReturn;
		}

		// Sends a Password authentication command and stores the result in the variable data
		LONG RF_Commands::PWD_AUTH(BYTE* password)
		{
			int CMD_PWD_AUTH_DATA_OFFSET = 6;
			int PWD_AUTH_LENGTH = 4 * sizeof(BYTE);

			LONG lReturn;
			BYTE cmdPWD[] = { 0xFF, 0xEF, 0x00, 0x00, 0x05, CMD_PWD_AUTH, 0x00, 0x00, 0x00, 0x00};
			DWORD cmdPWDLength = sizeof(cmdPWD);
			BYTE respcmdPWD[CMD_PWD_AUTH_RESP_LENGTH];
			DWORD respcmdPWDLength = CMD_PWD_AUTH_RESP_LENGTH;

			memcpy(cmdPWD + CMD_PWD_AUTH_DATA_OFFSET, password, PWD_AUTH_LENGTH);

			// Send PWD_AUTH command
			lReturn = sCardReader->cardTransmit(cmdPWD, cmdPWDLength, NULL, respcmdPWD, &respcmdPWDLength);

			// Check if an error has occurred even though lReturn indicates success
			if (isReturnSuccess(lReturn) && (respcmdPWDLength != CMD_PWD_AUTH_RESP_LENGTH || respcmdPWD[0] != 0x00 || respcmdPWD[1] != 0x00)){
				lReturn = SCARD_E_COMM_DATA_LOST;
			}

			return lReturn;
		}

		// Sends a Read command and stores the result in the variable data
		LONG RF_Commands::READ(BYTE page, BYTE* data)
		{
			LONG lReturn;
			BYTE cmdRead[] = { 0xFF, 0xEF, 0x00, 0x00, 0x02, CMD_READ, 0x00 };
			DWORD cmdReadLength = sizeof(cmdRead);
			BYTE respRead[CMD_READ_RESP_LENGTH];
			DWORD respReadLength = CMD_READ_RESP_LENGTH;

			// Send Read command
			cmdRead[6] = page;
			lReturn = sCardReader->cardTransmit(cmdRead, cmdReadLength, NULL, respRead, &respReadLength);

			if (isReturnSuccess(lReturn)){
				if (isResponseLengthAsExpected(respReadLength, CMD_READ_RESP_LENGTH)){
					memcpy(data, respRead, respReadLength - NTAG_CRC_SIZE);
				}
				else{
					lReturn = SCARD_E_COMM_DATA_LOST;
				}
			}

			return lReturn;
		}

		// Sends a Fast Read command and stores the result in the variable data
		LONG RF_Commands::FAST_READ(BYTE startPage, BYTE endPage, BYTE* data)
		{
			LONG lReturn;
			BYTE cmdFastRead[] = { 0xFF, 0xEF, 0x00, 0x00, 0x03, CMD_FAST_READ, 0x00, 0x00 };
			DWORD cmdFastReadLength = sizeof(cmdFastRead);
			BYTE respFastRead[CMD_FAST_READ_RESP_LENGTH];
			DWORD respFastReadLength = CMD_FAST_READ_RESP_LENGTH;
			
			// Send Fast Read command
			cmdFastRead[6] = startPage;
			cmdFastRead[7] = endPage;
			lReturn = sCardReader->cardTransmit(cmdFastRead, cmdFastReadLength, NULL, respFastRead, &respFastReadLength);

			if (isReturnSuccess(lReturn)){
				if (respFastReadLength == (endPage - startPage + 1) * NTAG_PAGE_SIZE + NTAG_CRC_SIZE){
					memcpy(data, respFastRead, respFastReadLength - NTAG_CRC_SIZE);
				}
				else{
					lReturn = SCARD_E_COMM_DATA_LOST;
				}
			}

			return lReturn;
		}

		// Sends a Write command with the content of the variable data
		LONG RF_Commands::WRITE(BYTE page, BYTE* data)
		{
			int CMD_WRITE_PAGE_OFFSET = 6;
			int CMD_WRITE_DATA_OFFSET = 7;
			int DATA_DATA_OFFSET = 0;
			int DATA_LENGTH = 4 * sizeof(BYTE);

			LONG lReturn;
			BYTE cmdWrite[] = { 0xFF, 0xEF, 0x00, 0x00, 0x06, CMD_WRITE, 0x00, 0x00, 0x00, 0x00, 0x00 };
			DWORD cmdWriteLength = sizeof(cmdWrite);
			BYTE respWrite[CMD_WRITE_RESP_LENGTH];
			DWORD respWriteLength = CMD_WRITE_RESP_LENGTH;

			// Send Write command [init:end] or memcpy
			cmdWrite[CMD_WRITE_PAGE_OFFSET] = page;
			memcpy(cmdWrite + CMD_WRITE_DATA_OFFSET, data + DATA_DATA_OFFSET, DATA_LENGTH);
			
			lReturn = sCardReader->cardTransmit(cmdWrite, cmdWriteLength, NULL, respWrite, &respWriteLength);

			// Check if an error has occurred even though lReturn indicates success
			if (isReturnSuccess(lReturn) && (respWriteLength != CMD_WRITE_RESP_LENGTH || respWrite[0] != 0x0A)){
				lReturn = SCARD_E_COMM_DATA_LOST;
			}

			return lReturn;
		}
		
		// Sends a Fast Write command and stores the result in the variable data
		LONG RF_Commands::FAST_WRITE(BYTE* data)
		{
			LONG lReturn;
			BYTE cmdFastWrite[] = { 0xFF, 0xEF, 0x00, 0x00, 0x43, CMD_FAST_WRITE, CMD_FAST_WRITE_START, CMD_FAST_WRITE_END, DATA_64_BYTES};
			DWORD cmdFastWriteLength = sizeof(cmdFastWrite);
			BYTE respFastWrite[CMD_FAST_WRITE_RESP_LENGTH];
			DWORD respFastWriteLength = CMD_FAST_WRITE_RESP_LENGTH;
			int DATA_LENGTH = 64 * sizeof(BYTE);

			memcpy(cmdFastWrite + 8, data + 0, DATA_LENGTH);

			// Send Fast WRITE command
			lReturn = sCardReader->cardTransmit(cmdFastWrite, cmdFastWriteLength, NULL, respFastWrite, &respFastWriteLength);

			// Check if an error has occurred even though lReturn indicates success
			if (isReturnSuccess(lReturn) && (respFastWriteLength != CMD_FAST_WRITE_RESP_LENGTH || respFastWrite[0] != 0x0A)){
				lReturn = SCARD_E_COMM_DATA_LOST;
			}

			return lReturn;
		}

		//Private methods:

		bool RF_Commands::isReturnSuccess(LONG response){
			return (response == SCARD_S_SUCCESS);
		}

		bool RF_Commands::isResponseLengthAsExpected(DWORD resp_length, DWORD expected_length){
			return (resp_length == expected_length);
		}

		LONG RF_Commands::getVersion(BYTE GVByte_Storage, BYTE GVByte_Minor, BYTE GVByte_Major, BYTE* vrsn){	//GV is for GetVersion
			LONG GVReturn = SCARD_S_SUCCESS;
		//	if (GVByte_Storage == NTAG_V1K_CODE)
		//	{
				if (GVByte_Major != 2) return SCARD_E_UNKNOWN_CARD;
				if ((GVByte_Minor == 2) && (GVByte_Storage == 0x13)) // NTAG I²C plus 1K
				{
					*vrsn = NTAG_VERSION_1K_PLUS;
				}
				if ((GVByte_Minor == 2) && (GVByte_Storage == 0x15)) // NTAG I²C plus 2K
				{
					*vrsn = NTAG_VERSION_2K_PLUS;
				}
				if ((GVByte_Minor == 1) && (GVByte_Storage == 0x13))// NTAG I²C 1K
				{
					*vrsn = NTAG_VERSION_1K;
				}
				if ((GVByte_Minor == 1) && (GVByte_Storage == 0x15))// NTAG I²C 2K
				{
					*vrsn = NTAG_VERSION_2K;
				}
		//	}				
		//	else
		//		GVReturn = SCARD_E_UNKNOWN_CARD;	// The version is unknown by this function
			return GVReturn;
		}

		long RF_Commands::establishConnection(int mode, DWORD* pAP){	//mode: 1=DIRECT; 2=SHARED; 3=EXCLUSIVE
			long lReturn;

			switch (mode) 
			{
				case 2:            // Note the colon, not a semicolon
					lReturn = sCardReader->cardConnect_SHARED_Mode(pAP);
					break;
				case 3:            // Note the colon, not a semicolon
					lReturn = sCardReader->cardConnect_DIRECT_Mode(pAP);
					break;
				default:            // Note the colon, not a semicolon
					lReturn = sCardReader->cardConnect_EXCLUSIVE_Mode(pAP);
					break;
			}

			if (lReturn == SCARD_S_SUCCESS)
			{
				sCardReader->sendPciConfig(*pAP);
			}
			return lReturn;
		}

		void RF_Commands::releaseConnection(long connectionStatus){
			if (connectionStatus == SCARD_S_SUCCESS)
			{
				free(sCardReader->ppioSendPci);
				sCardReader->cardDisconnect();
			}
			free(sCardReader->phCardHandle);
		}

		bool RF_Commands::readerInit(){
			LPTSTR pmszReaders = NULL;
			LPTSTR pReader;
			DWORD cch = SCARD_AUTOALLOCATE;
			WCHAR endOfValue = '\0';
			bool res = false;

			if (sCardReader->setContext() == SCARD_S_SUCCESS)
			{
				if (sCardReader->getConnectedReaders(&pmszReaders, &cch) == SCARD_S_SUCCESS)
				{
					pReader = pmszReaders;

					while (endOfValue != *pReader)
					{
						if (!wcscmp(pReader, sCardReader->szReader)) //compareReaderIdentifier
						{
							sCardReader->isReader = res = true;
						}
						pReader = pReader + wcslen(pReader) + 1;	// get next Reader Identifier
					}
				}
			}
			return res;
		}

		long RF_Commands::releaseContext()
		{
			long ret;
			ret = sCardReader->releaseContext();
			return ret;
		}

		bool RF_Commands::isReaderConnected(){
			return sCardReader->isReaderConnected();
		}

		bool RF_Commands::checkStatusWordSuccess(BYTE * response, int swOffset){
			return(response[swOffset + 0] != 0x90 || response[swOffset + 1] != 0x00);
		}

		/*bool RF_Commands::checkIfTag(){
			return sCardReader->checkIfTag();
		}*/

		long RF_Commands::readIdentivFWversion(char* IdentivReaderFWversion){
			return sCardReader->readIdentivFWversion(IdentivReaderFWversion);
		}

