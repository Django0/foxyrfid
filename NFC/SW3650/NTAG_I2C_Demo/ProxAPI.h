/*// NFC Forum NDEF Parsing values
#define TNF_WELL_KNOWN 1
#define TNF_MIME_TYPE 3

// NFC Forum Well-Known type identifiers
#define RTD_TEXT "T"
#define RTD_URI "U"
#define RTD_HS "Hs"
#define RTD_SP "Sp"

// NFC Forum MIME type identifiers
#define MIME_BTPAIR "application/vnd.bluetooth.ep.oob"

// LPC11U24 parameters
#define SECTOR_SIZE	4096

// My proprietary reader errors
#define SCARD_P_STATIC_LOCKED	0xFF000001
#define SCARD_P_DYNAMIC_LOCKED	0xFF000002
#define SCARD_P_CC_WRONG		0xFF000003
#define SCARD_P_CONFIG_LOCKED	0xFF000004

// My LED color identifiers
#define RED		1
#define BLUE	2
#define GREEN	3
#define OFF     0

//refactored NDEF
// My NDEF type identifiers
#define TYPE_NDEF_TEXT 0
#define TYPE_NDEF_URI 1
#define TYPE_NDEF_BTPAIR 2
#define TYPE_NDEF_SP 3

// Obtains the size of an static array
#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

//REFACTORED
//Identiv reader FW structure
#define IOCTL_CCID_ESCAPE SCARD_CTL_CODE (0xDAC)
typedef struct
{
BYTE byMajorVersion;
BYTE byMinorVersion;
BYTE bySupportedModes;
WORD wSupportedProtocols;
WORD winputDevice;
BYTE byPersonality;
BYTE byMaxSlots;
BYTE bySerialNoLength;
BYTE abySerialNumber[28];
} ReaderInfoExtended;

//Refactored to Registers
// Structure with the session/config registers parsed
typedef struct Ntag_I2C_Registers
{
	char	REG_Manufacture[20];
	int		REG_Mem_size;
	BOOL	REG_I2C_RST_ON_OFF;
	char	REG_FD_OFF[3];
	char	REG_FD_ON[3];
	int		REG_LAST_NDEF_PAGE;
	BOOL	REG_NDEF_DATA_READ;
	BOOL	REG_RF_FIELD_PRESENT;
	BOOL	REG_PTHRU_ON_OFF;
	BOOL	REG_I2C_LOCKED;
	BOOL	REG_RF_LOCKED;
	BOOL	REG_SRAM_I2C_READY;
	BOOL	REG_SRAM_RF_READY;
	BOOL	REG_EEPROM_WR_BUSY;
	BOOL	REG_PTHRU_DIR;
	int		REG_SM_Reg;
	int		REG_WD_LS_Reg;
	int		REG_WD_MS_Reg;
	//	String	REG_NDEF_Message;
	BOOL	REG_SRAM_MIRROR_ON_OFF;
	BOOL	REG_I2C_CLOCK_STR;
} Ntag_I2C_Registers_t;

//REFACTORED TO BoardDemo (TO RE-REFACTOR)
// Structure with the version of the board and the firmware
typedef struct Versions
{
	char	Board_Version[18];
	char	Board_FW_Version[18];
}Versions_t;

#include <string>
#include <iostream>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;
using namespace System::Runtime::InteropServices;

#pragma once

namespace NTAG_I2C_Demo {

	using namespace System;

	public ref class TagWaiter
	{
	private:
		//REFACTORED
		// PC/SC variables
		SCARDCONTEXT* phContext;	// I declare it as a pointer to avoid issues with C++/CLI: it creates it as an interior_ptr
		//LPCTSTR szReader = L"SCM Microsystems Inc. SCL010 Contactless Reader 0";
		//LPCTSTR szReader = L"SCM Microsystems Inc. SCL011 Contactless Reader 0";
		LPCTSTR szReader = L"Identiv CLOUD 3700 F Contactless Reader 0";
		SCARDHANDLE* phCardHandle;	// I declare it as a pointer to avoid issues with C++/CLI: it creates it as an interior_ptr
		SCARD_IO_REQUEST* ppioSendPci; // I declare it as a pointer to avoid issues with C++/CLI

		//REFACTORED
		// variables for the LED Demo
		BYTE* prevTempC;	
		BYTE* prevTempF;
		BYTE* prevVolt;

	public:
		event System::EventHandler^ TagEvent;
		event System::EventHandler^ TagRemovedEvent;
		bool isLedDemo = false;
		bool isReader = false;
		bool endWait;
		bool killThread = false;

		// Constructor
		TagWaiter()
		{
			//REFACTORED
			// Initialize context
			Reader::phContext = (SCARDCONTEXT*)malloc(sizeof(SCARDCONTEXT));
			if (SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, Reader::phContext) == SCARD_S_SUCCESS)
			{
				// Check if the reader is connected
				LPTSTR pmszReaders = NULL;
				DWORD cch = SCARD_AUTOALLOCATE;
				if (SCardListReaders(*Reader::phContext, NULL, (LPTSTR)&pmszReaders, &cch) == SCARD_S_SUCCESS)
				{
					LPTSTR pReader;
					// Check if the reader is inside the list
					pReader = pmszReaders;
					while ('\0' != *pReader)	// A double-null terminates the list of values
					{
						if (!wcscmp(pReader, Reader::szReader))
							this->isReader = true;
						pReader = pReader + wcslen(pReader) + 1;	// Advance to the next string
					}

					// Initialize variables for the Led Demo
					prevTempC = (BYTE*)malloc(4*sizeof(BYTE));
					memset(prevTempC, 0, 4*sizeof(BYTE));
					prevTempF = (BYTE*)malloc(5*sizeof(BYTE));
					memset(prevTempF, 0, 5 * sizeof(BYTE));
					prevVolt = (BYTE*)malloc(2*sizeof(BYTE));
					memset(prevVolt, 0, 2 * sizeof(BYTE));
				}
			}
		}

		//REFACTORED
		// Destructor
		~TagWaiter()
		{
			//Free variables for the Led Demo
			free(prevTempC);
			free(prevTempF);
			free(prevVolt);

			SCardReleaseContext(*phContext);
			free(Reader::phContext);
		}

		//REFACTORED
		// Secondary thread
		void FireOnTag()
		{
			// PC/SC variables
			SCARD_READERSTATE sReaderState;
			memset(&sReaderState, 0, sizeof(SCARD_READERSTATE));
			sReaderState.szReader = Reader::szReader;

			while (this->killThread == false)
			{
				this->endWait = false;

				// Wait until a tag is detected
				do
				{
					System::Threading::Thread::Sleep(100);
					SCardGetStatusChange(*Reader::phContext, INFINITE, &sReaderState, 1);
				} while ((sReaderState.dwEventState & SCARD_STATE_PRESENT) != SCARD_STATE_PRESENT && this->killThread == false);
				if (this->killThread == false)
				{
					bool isTag = true;
					TagEvent(this, gcnew EventArgs());

					// Wait until the tag is lost
					do
					{
						System::Threading::Thread::Sleep(100);
						isTag = CheckIfTag();
						if (!this->killThread && this->isLedDemo)	// If we are in the Demo tab, we need to keep on reading the tag
						{
							TagEvent(this, gcnew EventArgs());
							
						}
					} while (isTag && !this->endWait && !this->killThread);
					if (!isTag)
						TagRemovedEvent(this, gcnew EventArgs());
				}
			}
		}

		//REFACTORED
		// Turns on one of the LEDs (by writting the appropriate content into the SRAM) and reads what buttons are pressed and the temperature at the board
		LONG BoardDemo(char ledColor, BOOL enTemp, BOOL enLCD, BOOL dispNDEF, BOOL* redButton, BOOL* greenButton, BOOL* blueButton, float* tempC, float* tempF, float* voltage, float* version)
		{
			LONG lReturn;
			BYTE cmd[NTAG_MEM_SIZE_SRAM];
			BYTE resp[NTAG_MEM_SIZE_SRAM];

			// Connect to card (we do it in exclusive mode to avoid interferences from other Windows services, e.g., when trying to access to sectors other than 0)
			Reader::phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
			DWORD dwAP; //Active protocol
			int i = 0;
			do
			{
				lReturn = SCardConnect(*Reader::phContext, Reader::szReader, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, Reader::phCardHandle, &dwAP);
				Sleep(50);
				i++;
			} while (lReturn == SCARD_E_SHARING_VIOLATION && i < 10);
			if (lReturn == SCARD_S_SUCCESS)
			{
				Reader::ppioSendPci = (SCARD_IO_REQUEST*)malloc(sizeof(SCARD_IO_REQUEST));
				Reader::ppioSendPci->dwProtocol = dwAP;
				Reader::ppioSendPci->cbPciLength = 8;

				// Send SRAM command with the LED information and get information about the temperature, voltage and buttons
				memset(&cmd, 0, NTAG_MEM_SIZE_SRAM);
				cmd[40] = prevTempC[0];
				cmd[41] = prevTempC[1];
				cmd[42] = prevTempC[2];
				cmd[43] = prevTempC[3];
				cmd[45] = prevTempF[0];
				cmd[46] = prevTempF[1];
				cmd[47] = prevTempF[2];
				cmd[48] = prevTempF[3];
				cmd[49] = prevTempF[4];
				cmd[56] = prevVolt[0];
				cmd[57] = prevVolt[1];
				if (dispNDEF == TRUE)
					cmd[53] = 'E';
				if (enLCD == TRUE)
					cmd[54] = 'E';
				if (enTemp == TRUE)
					cmd[55] = 'E';
				cmd[60] = 'L';
				cmd[61] = '0' + ledColor;
				lReturn = PerformSramCom(cmd, resp);
				if (lReturn == SCARD_S_SUCCESS)
				{
					// Parse the information from the SRAM
					// Obtain the temperature
					int Temp = 0;
					// Adding first Byte
					Temp = ((resp[59] >> 5) & 0x00000007);
					// Adding second Byte
					Temp |= ((resp[58] << 3) & 0x000007F8);
					// If the 11 Bit is 1 it is negative
					if ((Temp & (1 << 11)) == (1 << 11)) {
						// Mask out the 11 Bit
						Temp &= ~(1 << 11);
					}
					// Obtain the actual value
					*tempC = Temp * 0.125f;
					*tempF = 32 + (1.8f * *tempC);

					// Obtain the voltage
					int Voltage = (int)resp[57] * 0x100 + resp[56];

					// Obtain the actual value
					*voltage = 0;
					if (Voltage != 0)
						*voltage = 0x3FF * 2.048f / Voltage;

					// Obtain the temperature and voltage values to send the next time to the board
					char fString[10];
					if (enTemp == TRUE)
					{
						sprintf_s(fString, 10, "%06.2f", *tempF);
						prevTempF[0] = fString[0];
						prevTempF[1] = fString[1];
						prevTempF[2] = fString[2];
						prevTempF[3] = fString[4];
						prevTempF[4] = fString[5];
						sprintf_s(fString, 10, "%05.2f", *tempC);
						prevTempC[0] = fString[0];
						prevTempC[1] = fString[1];
						prevTempC[2] = fString[3];
						prevTempC[3] = fString[4];
					}
					sprintf_s(fString, 10, "%03.1f", *voltage);
					prevVolt[0] = fString[0];
					prevVolt[1] = fString[2];

					// Obtain the buttons
					*redButton = FALSE;
					*greenButton = FALSE;
					*blueButton = FALSE;
					if ((resp[62] & 0x01) == 0x01)
						*redButton = TRUE;
					if ((resp[62] & 0x02) == 0x02)
						*greenButton = TRUE;
					if ((resp[62] & 0x04) == 0x04)
						*blueButton = TRUE;

					// Obtain the firmware version
					*version = 1;
					if (resp[63] != 0)
						*version = ((resp[63] >> 4) & 0x0F) + ((resp[63] & 0x0F) * 0.1f);
				}
				free(Reader::ppioSendPci);
				SCardDisconnect(*Reader::phCardHandle, SCARD_LEAVE_CARD);
			}
			free(Reader::phCardHandle);

			return lReturn;
		}

		//REFACTORED
		//Returns the identiv FW version
		LONG readIdentivFWversion(char* IdentivReaderFWversion)
		{
			SCARDCONTEXT ContextHandle;
			SCARDHANDLE CardHandle;
			ReaderInfoExtended strReaderInfo;
			BYTE InByte, i;
			DWORD BytesRead, ActiveProtocol;
			ULONG ret;
			//char *s;
			//char *ReaderName[] = { "Identive CLOUD 3700 F Contactless Reader 0",NULL };
			BYTE byMajorVersion;
			BYTE byMinorVersion;
			LPCTSTR szReader = L"Identiv CLOUD 3700 F Contactless Reader 0";

			ret = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &ContextHandle);
			if (ret == SCARD_S_SUCCESS)
			{
				ret = SCardConnect(ContextHandle, szReader, SCARD_SHARE_DIRECT, SCARD_PROTOCOL_UNDEFINED, &CardHandle, &ActiveProtocol);

				if (ret == SCARD_S_SUCCESS)
				{
					InByte = 0x1E;
					ret = SCardControl(CardHandle, IOCTL_CCID_ESCAPE, &InByte, 1, &strReaderInfo, sizeof(strReaderInfo), &BytesRead);
					if (SCARD_S_SUCCESS == ret)
					{
						IdentivReaderFWversion[0] = '0' + strReaderInfo.byMajorVersion;
						IdentivReaderFWversion[1] = '.';
						IdentivReaderFWversion[2] = '0' + strReaderInfo.byMinorVersion;
					}
				}
			}
			SCardDisconnect(CardHandle, SCARD_LEAVE_CARD);
			return ret;
		}

		//REFACTOR TO BoardDemo
		// Returns the board and firmware versions
		LONG ReadVersions(Versions_t* versions)
		{
			LONG lReturn;
			BYTE cmd[NTAG_MEM_SIZE_SRAM];
			BYTE resp[NTAG_MEM_SIZE_SRAM];

			// Connect to card (we do it in exclusive mode to avoid interferences from other Windows services, e.g., when trying to access to sectors other than 0)
			Reader::phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
			DWORD dwAP; //Active protocol
			int i = 0;
			do
			{
				lReturn = SCardConnect(*Reader::phContext, Reader::szReader, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, Reader::phCardHandle, &dwAP);
				Sleep(50);
				i++;
			} while (lReturn == SCARD_E_SHARING_VIOLATION && i < 10);
			if (lReturn == SCARD_S_SUCCESS)
			{
				Reader::ppioSendPci = (SCARD_IO_REQUEST*)malloc(sizeof(SCARD_IO_REQUEST));
				Reader::ppioSendPci->dwProtocol = dwAP;
				Reader::ppioSendPci->cbPciLength = 8;

				// Send SRAM command asking for version information
				memset(&cmd, 0, NTAG_MEM_SIZE_SRAM);
				cmd[60] = 'V';
				lReturn = PerformSramCom(cmd, resp);
				if (lReturn == SCARD_S_SUCCESS)
				{
					// Parse the information from the SRAM
					// Check if data was sent, otherwise it is a ExplorerBoard FW
					if (resp[12] == 0)
					{
						versions->Board_Version[0] = ((resp[63] >> 4) & (BYTE)0x0F) + 0x30;
						versions->Board_Version[1] = '.';  
						versions->Board_Version[2] = (resp[63] & (BYTE)0x0F) + 0x30;
						versions->Board_Version[3] = '\0';
						strcpy_s(versions->Board_FW_Version, 4, versions->Board_Version);
					}
					else
					{
						resp[15] = '\0';
						strcpy_s(versions->Board_Version, 4, (char*)resp + 12);
						resp[31] = '\0';
						strcpy_s(versions->Board_FW_Version, 4, (char*)resp + 28);
					}
				}
				free(Reader::ppioSendPci);
				SCardDisconnect(*Reader::phCardHandle, SCARD_LEAVE_CARD);
			}
			free(Reader::phCardHandle);

			return lReturn;
		}

		//REFACTORED TO SRAM
		// Flashes the memory of the board with the firmware in the BYTE array
		LONG FlashMemory(BYTE* newFW, int newFWLength, DWORD* flashBytes, float* flashTime, System::Windows::Forms::ProgressBar^ progressBar1)
		{
			LONG lReturn;
			BYTE sectorFW[SECTOR_SIZE];
			BYTE cmd[NTAG_MEM_SIZE_SRAM];
			BYTE resp[NTAG_MEM_SIZE_SRAM];

			// Connect to card (we do it in exclusive mode to avoid interferences from other Windows services, e.g., when trying to access to sectors other than 0)
			Reader::phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
			DWORD dwAP; //Active protocol
			int i = 0;
			do
			{
				lReturn = SCardConnect(*Reader::phContext, Reader::szReader, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, Reader::phCardHandle, &dwAP);
				Sleep(50);
				i++;
			} while (lReturn == SCARD_E_SHARING_VIOLATION && i < 10);
			if (lReturn == SCARD_S_SUCCESS)
			{
				*flashBytes = (int)ceil((float)(newFWLength + 2) / 4) * 4;
				*flashTime = (float)clock();
				Reader::ppioSendPci = (SCARD_IO_REQUEST*)malloc(sizeof(SCARD_IO_REQUEST));
				Reader::ppioSendPci->dwProtocol = dwAP;
				Reader::ppioSendPci->cbPciLength = 8;

				// We divide the firmware in bunches of 4096 bytes, that will be written in one of the sectors of the microcontroller
				int nFlashSectors = newFWLength / SECTOR_SIZE + ((newFWLength % SECTOR_SIZE) == 0 ? 0 : 1);
				int h = 0;
				int j = 0;
				do
				{
					// Write a whole sector onto the SRAM
					// Check if it is the last sector
					if (newFWLength - (h + 1) * SECTOR_SIZE < 0)
					{
						// If it is the last sector, we copy the remaining bytes of the firmware to the sectorFW array, and we fill the rest of the array with 0s
						memset(sectorFW, 0, SECTOR_SIZE);
						memcpy(sectorFW, newFW + h*SECTOR_SIZE, newFWLength % SECTOR_SIZE);
					}
					else
					{	// If it is not the last sector, we copy the corresponding sector of the firmware to the sectorFW arraw
						memcpy(sectorFW, newFW + h*SECTOR_SIZE, SECTOR_SIZE);
					}
					// Send SRAM command indicating that a whole new sector will be written
					int flashAddr = 0x4000 + h * SECTOR_SIZE;	// We begin to write on sector 4
					memset(cmd, 0, NTAG_MEM_SIZE_SRAM);
					cmd[52] = flashAddr >> 24 & 0xFF;
					cmd[53] = flashAddr >> 16 & 0xFF;
					cmd[54] = flashAddr >> 8 & 0xFF;
					cmd[55] = flashAddr & 0xFF;
					cmd[56] = SECTOR_SIZE >> 24 & 0xFF;
					cmd[57] = SECTOR_SIZE >> 16 & 0xFF;
					cmd[58] = SECTOR_SIZE >> 8 & 0xFF;
					cmd[59] = SECTOR_SIZE & 0xFF;
					cmd[60] = 'F';
					cmd[61] = 'P';
					lReturn = WriteSram(cmd);
					// Send several SRAM commands with the firmware of the sector indicated previously
					BYTE* pSectorFW = sectorFW;
					
					while (pSectorFW < sectorFW + SECTOR_SIZE && lReturn == SCARD_S_SUCCESS)
					{
						lReturn = WaitForI2CRead();
						if (lReturn == SCARD_S_SUCCESS)
						{
							lReturn = WriteSram(pSectorFW);
							progressBar1->PerformStep();
						}
						pSectorFW += NTAG_MEM_SIZE_SRAM;
					}
					if (lReturn == SCARD_S_SUCCESS)
					{
						// Wait for the microcontroller to process the information and to write the response into the SRAM
						Sleep(2000);
						lReturn = WaitForI2CWrite();
						if (lReturn == SCARD_S_SUCCESS)
						{
							lReturn = ReadSram(resp);
							// Check if an error has occurred even though lReturn indicates success
							if (lReturn == SCARD_S_SUCCESS && (resp[60] != 'A' || resp[61] != 'C' || resp[62] != 'K'))
								lReturn = SCARD_E_COMM_DATA_LOST;
						}
					}

					h++;
				} while (h < nFlashSectors && lReturn == SCARD_S_SUCCESS);
				if (lReturn == SCARD_S_SUCCESS)
				{
					// If the writting has been ccompleted successfully, we indicate it to the board
					memset(cmd, 0, NTAG_MEM_SIZE_SRAM);
					cmd[60] = 'F';
					cmd[61] = 'S';
					lReturn = WriteSram(cmd);
					if (lReturn == SCARD_S_SUCCESS)
						lReturn = WaitForI2CRead();
				}
				else
				{
					// If the writting has not been completed successfully, we indicate it to the board (we don't update lReturn)
					memset(cmd, 0, NTAG_MEM_SIZE_SRAM);
					cmd[60] = 'F';
					cmd[61] = 'F';
					WriteSram(cmd);
					WaitForI2CRead();
				}
				*flashTime = (float)clock() - *flashTime;

				free(Reader::ppioSendPci);
				SCardDisconnect(*Reader::phCardHandle, SCARD_LEAVE_CARD);
			}
			free(Reader::phCardHandle);

			return lReturn;
		}

		// Returns the NDEF message and message type
		LONG ReadNdef(int* NdefType, BYTE* payload, int* payloadSize, BOOL *AARPresent, BYTE* AAR, int*AARSize, DWORD* readBytes, float* readTime)
		{
			LONG lReturn;
			BYTE data[MAX_MEM_SIZE];
			int length;
			*payloadSize = 0;

			// Connect to card (no need for exclusive access, as everything is done in sector 0)
			Reader::phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
			DWORD dwAP; //Active protocol
			lReturn = SCardConnect(*Reader::phContext, Reader::szReader, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, Reader::phCardHandle, &dwAP);
			if (lReturn == SCARD_S_SUCCESS)
			{
				Reader::ppioSendPci = (SCARD_IO_REQUEST*)malloc(sizeof(SCARD_IO_REQUEST));
				Reader::ppioSendPci->dwProtocol = dwAP;
				Reader::ppioSendPci->cbPciLength = 8;

				*readTime = (float)clock();
				// Get the NDEF message
				lReturn = ReadNdefMessage(data, &length);
				*readBytes = (int)ceil((float)(length + 6) / 16) * 16;	// Bytes are read 16 by 16
				if (lReturn == SCARD_S_SUCCESS)
				{
					// The TNF is defined in the last three bits of the first byte of the NDEF Message
					BYTE TNF = data[0] & 0x07;
					BYTE typeLength = data[1];
					BYTE payloadLength = data[2];
					// From byte 3, the NDEF type is defined as an string of length typeLength
					BYTE* Type = (BYTE*)malloc((typeLength + 1)*sizeof(BYTE));
					memcpy(Type, data + 3, typeLength);
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
							memcpy(payload, data + 3 + typeLength + 3, *payloadSize);
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
								lReturn = getUriType(data[3 + typeLength], uriType, &uriLength);
								if (lReturn == SCARD_S_SUCCESS)
								{
									*payloadSize = uriLength + payloadLength - 1;
									memcpy(payload, uriType, uriLength);
									memcpy(payload + uriLength, data + 3 + typeLength + 1, payloadLength - 1);
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
										parseBTPairRecord(btRecord + strlen(MIME_BTPAIR), (char*)payload + 1 + strlen(MIME_BTPAIR), payloadSize);	// It always returns SCARD_S_SUCCESS
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
												lReturn = getUriType(data[3 + typeLength + 4 + 3 + payload[0] + 4], uriType, &uriLength);
												if (lReturn == SCARD_S_SUCCESS)
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
							parseBTPairRecord(btRecord + strlen(MIME_BTPAIR), (char*)payload + 1 + strlen(MIME_BTPAIR), payloadSize);	// It always returns SCARD_S_SUCCESS
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
					if (data[0] == 0x91 && lReturn == SCARD_S_SUCCESS)
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
				free(Reader::ppioSendPci);
				SCardDisconnect(*Reader::phCardHandle, SCARD_LEAVE_CARD);
			}
			free(Reader::phCardHandle);

			return lReturn;
		}

		//REFACTORED TO NDEF
		// Writes the NDEF type indicated with the content indicated
		LONG WriteNdef(int NdefType, BYTE* payload, int payloadSize, BOOL addAAR, DWORD* writeBytes, float* writeTime)
		{
			LONG lReturn;
			BYTE message[MAX_MEM_SIZE];
			int length;

			// Connect to card (no need for exclusive access, as everything is done in sector 0)
			Reader::phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
			DWORD dwAP; //Active protocol
			lReturn = SCardConnect(*Reader::phContext, Reader::szReader, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, Reader::phCardHandle, &dwAP);
			if (lReturn == SCARD_S_SUCCESS)
			{
				Reader::ppioSendPci = (SCARD_IO_REQUEST*)malloc(sizeof(SCARD_IO_REQUEST));
				Reader::ppioSendPci->dwProtocol = dwAP;
				Reader::ppioSendPci->cbPciLength = 8;

				*writeTime = (float)clock();
				// Create the NDEF message
				switch (NdefType)
				{
				case TYPE_NDEF_TEXT:
					lReturn = createTextRecord(payload, payloadSize, message, &length);
					break;
				case TYPE_NDEF_URI:
					lReturn = createUriRecord(payload, payloadSize, message, &length);
					break;
				case TYPE_NDEF_BTPAIR:
					lReturn = createBTPairRecord(payload, payloadSize, message, &length);
					break;
				case TYPE_NDEF_SP:
					lReturn = createSPRecord(payload, payloadSize, message, &length);
					break;
				}
				if (lReturn == SCARD_S_SUCCESS)
				{
					// If required, append the AAR to the NDEF message
					if (addAAR)
						lReturn = AppendAAR(message, &length);
					if (lReturn == SCARD_S_SUCCESS)
					{
						// Write the NDEF message to the tag
						lReturn = WriteNdefMessage(message, length);
						*writeTime = (float)clock() - *writeTime;
						*writeBytes = (int)ceil((float)(length + 2) / 4) * 4; // Bytes are writen 4 by 4
						if (lReturn == SCARD_S_SUCCESS)
						{
							// Inform the BoardDemo about the new NDEF message that has been stored
							BYTE wData[NTAG_MEM_SIZE_SRAM] = { 0 };
							wData[60] = 'N';
							WriteSram(wData);
						}
					}
				}
				free(Reader::ppioSendPci);
				SCardDisconnect(*Reader::phCardHandle, SCARD_LEAVE_CARD);
			}
			free(Reader::phCardHandle);

			return lReturn;
		}

		//refactored to sram
		// Performs a test on the speed for writing and reading from the SRAM
		LONG SRAMSpeedTest(int chMultiplier, BOOL polling, BOOL* integritySent, BOOL* integrityRecv, float* writeTime, float* readTime)
		{
			LONG lReturn;
			BYTE dataBlock[NTAG_MEM_SIZE_SRAM] = { 0 };

			// Connect to card (we do it in exclusive mode to avoid interferences from other Windows services, e.g., when trying to access to sectors other than 0)
			Reader::phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
			DWORD dwAP; //Active protocol
			int i = 0;
			do
			{
				lReturn = SCardConnect(*Reader::phContext, Reader::szReader, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, Reader::phCardHandle, &dwAP);
				Sleep(50);
				i++;
			} while (lReturn == SCARD_E_SHARING_VIOLATION && i < 10);
			if (lReturn == SCARD_S_SUCCESS)
			{
				Reader::ppioSendPci = (SCARD_IO_REQUEST*)malloc(sizeof(SCARD_IO_REQUEST));
				Reader::ppioSendPci->dwProtocol = dwAP;
				Reader::ppioSendPci->cbPciLength = 8;

				// During the SRAM test we write 64 bytes in the memory space dedicated for it
				// S: reference for the SpeedTest
				dataBlock[60] = 'S';
				lReturn = WriteSram(dataBlock);
				if (lReturn == SCARD_S_SUCCESS)
				{
					// if the Passthrough mode was not activated, wait for it to be activated
					lReturn = WaitForPassthroughActive();
					if (lReturn == SCARD_S_SUCCESS)
					{
						dataBlock[60] = 0;	// == memset(dataBlock, 0, NTAG_MEM_SIZE_SRAM);
						// Initialize the seed for the CRC32 calculation
						uint32_t seed = 0xFFFFFFFF;
						uint32_t crcTx = 0;

						// Execute write test
						*writeTime = (float)clock();
						int i = chMultiplier;
						while (i > 0 && lReturn == SCARD_S_SUCCESS)
						{
							// The last block contains the "finish_S_" string to notify the LPC board about the message transmission completion
							if (i == 1)
							{
								memcpy(dataBlock, "finish_S_", 9);
								// Update content for the CRC32 calculation (last 4 bytes are the CRC32)
								crcTx = crc32(seed, dataBlock, NTAG_MEM_SIZE_SRAM - 4);
								// Append the CRC32 to the block as this is the last block to be transmitted
								dataBlock[60] = (crcTx >> 0) & 0xFF;
								dataBlock[61] = (crcTx >> 8) & 0xFF;
								dataBlock[62] = (crcTx >> 16) & 0xFF;
								dataBlock[63] = (crcTx >> 24) & 0xFF;
							}
							else
							{
								// Update content for the CRC32 calculation
								crcTx = crc32(seed, dataBlock, NTAG_MEM_SIZE_SRAM);
								seed = crcTx;
							}

							// Write Data to SRAM
							lReturn = WriteSram(dataBlock);

							if (lReturn == SCARD_S_SUCCESS)
							{
								// Check if polling is required
								if (polling == TRUE)
									lReturn = WaitForI2CRead();
								else
									Sleep(30);
							}

							i--;
						}
						*writeTime = (float)clock() - *writeTime;

						Sleep(10);

						// Reset the seed to its initial value for the CRC32 calculation
						seed = 0xFFFFFFFF;
						uint32_t crcRx = 0;

						// Execute read test
						*readTime = (float)clock();
						i = chMultiplier;
						while (i > 0 && lReturn == SCARD_S_SUCCESS)
						{
							// Check if polling is required
							if (polling == TRUE)
								lReturn = WaitForI2CWrite();
							else
								Sleep(30);
							if (lReturn == SCARD_S_SUCCESS)
							{
								// data is ready, read from SRAM
								lReturn = ReadSram(dataBlock);
								if (i > 1)
								{
									crcRx = crc32(seed, dataBlock, NTAG_MEM_SIZE_SRAM);
									seed = crcRx;
								}
								else
									crcRx = crc32(seed, dataBlock, NTAG_MEM_SIZE_SRAM - 4);
							}
							i--;
						}
						*readTime = (float)clock() - *readTime;
						if (lReturn == SCARD_S_SUCCESS)
						{
							// Get the CRC values in reception
							uint32_t crcReceived = dataBlock[NTAG_MEM_SIZE_SRAM - 1] << 24 | dataBlock[NTAG_MEM_SIZE_SRAM - 2] << 16 |
								dataBlock[NTAG_MEM_SIZE_SRAM - 3] << 8 | dataBlock[NTAG_MEM_SIZE_SRAM - 4];
							*integrityRecv = (crcReceived == crcRx);

							// Check if the microcontroller detected an error in the CRC
							*integritySent = dataBlock[59] == 0x01 ? FALSE : TRUE;
						}
					}
				}
				free(Reader::ppioSendPci);
				SCardDisconnect(*Reader::phCardHandle, SCARD_LEAVE_CARD);
			}
			free(Reader::phCardHandle);

			return lReturn;
		}

		//refactored to EEPROM
		// Performs a test on the speed for writing and reading from the EEPROM
		LONG EEPROMSpeedTest(int chMultiplier, BYTE* text, int* nWrittenBytes, float* writeTime, int* nReadBytes, float* readTime)
		{
			LONG lReturn;
			BYTE message[MAX_MEM_SIZE];

			// Connect to card (we do it in exclusive mode to avoid interferences from other Windows services, e.g., when trying to access to sectors other than 0)
			Reader::phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
			DWORD dwAP; //Active protocol
			int i = 0;
			do
			{
				lReturn = SCardConnect(*Reader::phContext, Reader::szReader, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, Reader::phCardHandle, &dwAP);
				Sleep(50);
				i++;
			} while (lReturn == SCARD_E_SHARING_VIOLATION && i < 10);
			if (lReturn == SCARD_S_SUCCESS)
			{
				Reader::ppioSendPci = (SCARD_IO_REQUEST*)malloc(sizeof(SCARD_IO_REQUEST));
				Reader::ppioSendPci->dwProtocol = dwAP;
				Reader::ppioSendPci->cbPciLength = 8;

				// Check memory size
				BYTE NtagVersion;
				int memSize = 0;
				lReturn = GET_VERSION(&NtagVersion);
				if (lReturn == SCARD_S_SUCCESS)
				{
					if (NtagVersion == NTAG_VERSION_1K)
						memSize = (NTAG_I2C_1k_MemSize + 16) / 4;
					else if (NtagVersion == NTAG_VERSION_2K)
						memSize = (NTAG_I2C_2k_MemSize + 16) / 4;
					
					// Build the NDEF message
					// NDEF payload
					int textSize = strlen((char*)text);
					int ndefPayloadSize = textSize*chMultiplier;
					BYTE* messageText = (BYTE*)malloc(ndefPayloadSize*sizeof(BYTE));
					BYTE* pnt;
					for (pnt = messageText; pnt < messageText + ndefPayloadSize; pnt += textSize)
						memcpy(pnt, text, textSize);
					// NDEF header (long NDEF)
					BYTE ndeftlv_header[] = { 0x03, 0xFF, ((ndefPayloadSize + 10) >> 8) & 0xFF, (ndefPayloadSize + 10) & 0xFF, 0xC1, 0x01, 0x00, 0x00, ((ndefPayloadSize + 3) >> 8) & 0xFF,
						(ndefPayloadSize + 3) & 0xFF, 0x54, 0x02, 0x65, 0x6E };
					int ndeftlvHeaderSize = ARRAY_SIZE(ndeftlv_header) - 2; // We rest -2 because the type text includes de language "en"
					// NDEF message
					int ndefMessageSize = ndeftlvHeaderSize + ndefPayloadSize;
					if (ndefMessageSize % 4 == 1)
						ndefMessageSize = ndefMessageSize + 3;
					if (ndefMessageSize % 4 == 2)
						ndefMessageSize = ndefMessageSize + 2;
					if (ndefMessageSize % 4 == 3)
						ndefMessageSize = ndefMessageSize + 1;
					memcpy(message, ndeftlv_header, ndeftlvHeaderSize);
					memcpy(message + ndeftlvHeaderSize, messageText, ndefPayloadSize);
					message[ndefMessageSize] = 0xFE;
					message[ndefMessageSize] = 0x00;
					message[ndefMessageSize] = 0x00;
					message[ndefMessageSize] = 0x00;
				//	ndefMessageSize += 4 - ndefMessageSize % 4;

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
							lReturn = WRITE(i, wPage);
							i++;
							p_ndef += 4;
						}
						// Check if there are more sectors
						if (p_ndef < p_endndef && lReturn == SCARD_S_SUCCESS)
						{
							lReturn = SECTOR_SELECT(1);
							if (lReturn == SCARD_S_SUCCESS)
							{
								i = 0;
								while (p_ndef < p_endndef && lReturn == SCARD_S_SUCCESS)
								{
									memcpy(wPage, p_ndef, 4);
									lReturn = WRITE(i, wPage);
									i++;
									p_ndef += 4;
								}
							}
							END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
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
								lReturn = FAST_READ(fetch_start & 0x00FF, fetch_end & 0x00FF, message);	// I don't care what I am reading, so I use the message variable because I won't use it anymore
								if (lReturn == SCARD_S_SUCCESS)
								{
									// calculate next fetch_start
									fetch_start = fetch_end + 1;
									// check for sector select needed
									if ((fetch_start & 0xFF00) != (fetch_end & 0xFF00))
										lReturn = SECTOR_SELECT(1);
								}
							}
							*readTime = (float)clock() - *readTime;
							// Check if we have gone to sector 1
							if ((fetch_start & 0xFF00) !=  0)
								END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
							if (lReturn == SCARD_S_SUCCESS)
							{
								*nWrittenBytes = ndefMessageSize;
								*nReadBytes = ndefMessageSize;
							}
						}
					}
					else
						lReturn = SCARD_E_INVALID_VALUE;
				}
				free(Reader::ppioSendPci);
				SCardDisconnect(*Reader::phCardHandle, SCARD_LEAVE_CARD);
			}
			free(Reader::phCardHandle);

			return lReturn;
		}
		
		//REFACTORED TO EEPROM
		// Reads the full memory of the NTAG (the first four pages, the user memory and the dynamic lock bytes)
		LONG ReadMemory(BYTE* data, DWORD* readBytes, float* readTime)
		{
			LONG lReturn;

			// Connect to card (we do it in exclusive mode to avoid interferences from other Windows services, e.g., when trying to access to sectors other than 0)
			Reader::phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
			DWORD dwAP; //Active protocol
			int i = 0;
			do
			{
				lReturn = SCardConnect(*Reader::phContext, Reader::szReader, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, Reader::phCardHandle, &dwAP);
				Sleep(50);
				i++;
			} while (lReturn == SCARD_E_SHARING_VIOLATION && i < 10);
			if (lReturn == SCARD_S_SUCCESS)
			{
				Reader::ppioSendPci = (SCARD_IO_REQUEST*)malloc(sizeof(SCARD_IO_REQUEST));
				Reader::ppioSendPci->dwProtocol = dwAP;
				Reader::ppioSendPci->cbPciLength = 8;

				// Initialize variables
				*readBytes = 0;
				int max_fast_read = (MAX_TRANSCEIVE_LENGTH - 2) / 4;
				int fetch_start = 0;
				int fetch_end = 0;
				// Check memory size
				BYTE NtagVersion;
				int memSize = 0;
				lReturn = GET_VERSION(&NtagVersion);
				if (lReturn == SCARD_S_SUCCESS)
				{
					if (NtagVersion == NTAG_VERSION_1K)
						memSize = (NTAG_I2C_1k_MemSize + 16) / 4;
					else if (NtagVersion == NTAG_VERSION_2K)
						memSize = (NTAG_I2C_2k_MemSize + 16) / 4;

					*readTime = (float)clock();
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
						lReturn = FAST_READ(fetch_start & 0x00FF, fetch_end & 0x00FF, data + *readBytes);
						if (lReturn == SCARD_S_SUCCESS)
						{
							*readBytes += (fetch_end - fetch_start + 1)*4;
							// calculate next fetch_start
							fetch_start = fetch_end + 1;
							// check for sector select needed
							if ((fetch_start & 0xFF00) != (fetch_end & 0xFF00))
								lReturn = SECTOR_SELECT(1);
						}
					} while (fetch_start <= memSize && lReturn == SCARD_S_SUCCESS);
					*readTime = (float)clock() - *readTime;
					// Check if we have gone to sector 1
					if ((fetch_start & 0xFF00) != 0)
						END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
				}
				free(Reader::ppioSendPci);
				SCardDisconnect(*Reader::phCardHandle, SCARD_LEAVE_CARD);
			}
			free(Reader::phCardHandle);

			return lReturn;
		}

		// Resets the full user memory of the NTAG
		LONG ResetMemory(DWORD* resetBytes, float* resetTime)
		{
			LONG lReturn;
			BYTE wPage[4] = { 0 };
			BYTE rPage[16];
			BYTE message[MAX_MEM_SIZE];
			int length;
			BYTE payload[MAX_MEM_SIZE];
			int payloadSize;

			// Connect to card (we do it in exclusive mode to avoid interferences from other Windows services, e.g., when trying to access to sectors other than 0)
			Reader::phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
			DWORD dwAP; //Active protocol
			int i = 0;
			do
			{
				lReturn = SCardConnect(*Reader::phContext, Reader::szReader, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, Reader::phCardHandle, &dwAP);
				Sleep(50);
				i++;
			} while (lReturn == SCARD_E_SHARING_VIOLATION && i < 10);
			if (lReturn == SCARD_S_SUCCESS)
			{
				Reader::ppioSendPci = (SCARD_IO_REQUEST*)malloc(sizeof(SCARD_IO_REQUEST));
				Reader::ppioSendPci->dwProtocol = dwAP;
				Reader::ppioSendPci->cbPciLength = 8;

				// Check memory size
				BYTE NtagVersion;
				lReturn = GET_VERSION(&NtagVersion);
				if (lReturn == SCARD_S_SUCCESS)
				{
					if (NtagVersion == NTAG_VERSION_1K)
						*resetBytes = NTAG_I2C_1k_MemSize;
					else if (NtagVersion == NTAG_VERSION_2K)
						*resetBytes = NTAG_I2C_2k_MemSize;
					int memSize = (*resetBytes + 16) / 4;
					
					*resetTime = (float)clock();
					// Check static lock bytes
					lReturn = READ(2, rPage);
					if (lReturn == SCARD_S_SUCCESS)
					{
						lReturn = SCARD_P_STATIC_LOCKED;
						if (rPage[2] == 0 && rPage[3] == 0)
						{
							// Check dynamic lock bytes
							if (NtagVersion == NTAG_VERSION_1K)
								lReturn = READ(0xE2, rPage);
							else
							{
								lReturn = SECTOR_SELECT(1);
								if (lReturn == SCARD_S_SUCCESS)
									lReturn = READ(0xE0, rPage);
								END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
							}
							if (lReturn == SCARD_S_SUCCESS)
							{
								lReturn = SCARD_P_DYNAMIC_LOCKED;
								if (rPage[0] == 0 && rPage[1] == 0 && rPage[2] == 0)
								{
									// Try writing the Capability Container
									if (NtagVersion == NTAG_VERSION_1K)
									{
										// CC for NTAG 1k
										wPage[0] = 0xE1;
										wPage[1] = 0x10;
										wPage[2] = 0x6D;
										wPage[3] = 0x00;
									}
									else
									{
										// CC for NTAG 2k
										wPage[0] = 0xE1;
										wPage[1] = 0x10;
										wPage[2] = 0xEA;
										wPage[3] = 0x00;
									}
									lReturn = WRITE(3, wPage);
									if (lReturn == SCARD_S_SUCCESS)
									{
										// Check if it has been written succesfully
										lReturn = READ(3, rPage);
										if (lReturn == SCARD_S_SUCCESS)
										{
											lReturn = SCARD_P_CC_WRONG;
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
													lReturn = WRITE(i, wPage);
													i++;
												} while (i < 0x100 && i < memSize && lReturn == SCARD_S_SUCCESS);
												// Check if there are more sectors
												if (memSize > 0x100 && lReturn == SCARD_S_SUCCESS)
												{
													lReturn = SECTOR_SELECT(1);
													i = 0;
													while (i < memSize - 0x100 && lReturn == SCARD_S_SUCCESS)
													{
														lReturn = WRITE(i, wPage);
														i++;
													}
													END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
												}
												if (lReturn == SCARD_S_SUCCESS)
												{
													// Create the default NDEF message to be written into the tag memory
													payload[0] = strlen("NTAG I2C EXPLORER");
													memcpy(payload + 1, "NTAG I2C EXPLORER", strlen("NTAG I2C EXPLORER"));
													payload[1 + strlen("NTAG I2C EXPLORER")] = strlen("http://www.nxp.com/demoboard/OM5569");
													memcpy(payload + 1 + strlen("NTAG I2C EXPLORER") + 1, "http://www.nxp.com/demoboard/OM5569", strlen("http://www.nxp.com/demoboard/OM5569"));
													payload[1 + strlen("NTAG I2C EXPLORER") + 1 + strlen("http://www.nxp.com/demoboard/OM5569")] = '\0'; // Title Length + Title + Link Length + Link
													payloadSize = 1 + strlen("NTAG I2C EXPLORER") + 1 + strlen("http://www.nxp.com/demoboard/OM5569");
													lReturn = createSPRecord(payload, payloadSize, message, &length);
													if (lReturn == SCARD_S_SUCCESS)
													{
														// Append the AAR to the NDEF message
														lReturn = AppendAAR(message, &length);
														if (lReturn == SCARD_S_SUCCESS)
														{
															// Write the NDEF message to the tag
															lReturn = WriteNdefMessage(message, length);
															if (lReturn == SCARD_S_SUCCESS)
															{
																// Check configuration lock bit via RF
																Ntag_I2C_Registers_t configReg;
																lReturn = GetConfigRegisters(&configReg);
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
																		lReturn = SetConfigRegisters(configReg);

																		*resetTime = (float)clock() - *resetTime;
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
				//free(Reader::ppioSendPci);
				SCardDisconnect(*Reader::phCardHandle, SCARD_LEAVE_CARD);
			}
			//free(Reader::phCardHandle);

			return lReturn;
		}

		// Gets the session registers of the NTAG
		LONG ReadSessionRegisters(Ntag_I2C_Registers_t* sessionReg)
		{
			LONG lReturn;
			BYTE data[16];

			// Connect to card (we do it in exclusive mode to avoid interferences from other Windows services, e.g., when trying to access to sectors other than 0)
			Reader::phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
			DWORD dwAP; //Active protocol
			int i = 0;
			do
			{
				lReturn = SCardConnect(*Reader::phContext, Reader::szReader, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, Reader::phCardHandle, &dwAP);
				Sleep(50);
				i++;
			} while (lReturn == SCARD_E_SHARING_VIOLATION && i < 10);
			if (lReturn == SCARD_S_SUCCESS)
			{
				Reader::ppioSendPci = (SCARD_IO_REQUEST*)malloc(sizeof(SCARD_IO_REQUEST));
				Reader::ppioSendPci->dwProtocol = dwAP;
				Reader::ppioSendPci->cbPciLength = 8;

				// Get all the session registers. The Session Registers are located in Sector 3
				lReturn = SECTOR_SELECT(3);
				if (lReturn == SCARD_S_SUCCESS)
				{
					// Read session registers
					lReturn = READ(SessionPage, data);
					if (lReturn == SCARD_S_SUCCESS)
						parseRegisters(sessionReg, data);
				}
				END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
				free(Reader::ppioSendPci);
				SCardDisconnect(*Reader::phCardHandle, SCARD_LEAVE_CARD);
			}
			free(Reader::phCardHandle);

			return lReturn;
		}

		// Gets the config registers of the NTAG
		LONG ReadConfigRegisters(Ntag_I2C_Registers_t* configReg)
		{
			LONG lReturn;

			// Connect to card (we do it in exclusive mode to avoid interferences from other Windows services, e.g., when trying to access to sectors other than 0)
			Reader::phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
			DWORD dwAP; //Active protocol
			int i = 0;
			do
			{
				lReturn = SCardConnect(*Reader::phContext, Reader::szReader, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, Reader::phCardHandle, &dwAP);
				Sleep(50);
				i++;
			} while (lReturn == SCARD_E_SHARING_VIOLATION && i < 10);
			if (lReturn == SCARD_S_SUCCESS)
			{
				Reader::ppioSendPci = (SCARD_IO_REQUEST*)malloc(sizeof(SCARD_IO_REQUEST));
				Reader::ppioSendPci->dwProtocol = dwAP;
				Reader::ppioSendPci->cbPciLength = 8;

				// Get all the config registers
				lReturn = GetConfigRegisters(configReg);

				free(Reader::ppioSendPci);
				SCardDisconnect(*Reader::phCardHandle, SCARD_LEAVE_CARD);
			}
			free(Reader::phCardHandle);

			return lReturn;
		}

		// Writes the config registers with the specified content
		LONG WriteConfigRegisters(Ntag_I2C_Registers_t configReg)
		{
			LONG lReturn;

			// Connect to card (we do it in exclusive mode to avoid interferences from other Windows services, e.g., when trying to access to sectors other than 0)
			Reader::phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
			DWORD dwAP; //Active protocol
			int i = 0;
			do
			{
				lReturn = SCardConnect(*Reader::phContext, Reader::szReader, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, Reader::phCardHandle, &dwAP);
				Sleep(50);
				i++;
			} while (lReturn == SCARD_E_SHARING_VIOLATION && i < 10);
			if (lReturn == SCARD_S_SUCCESS)
			{
				Reader::ppioSendPci = (SCARD_IO_REQUEST*)malloc(sizeof(SCARD_IO_REQUEST));
				Reader::ppioSendPci->dwProtocol = dwAP;
				Reader::ppioSendPci->cbPciLength = 8;

				// Set all the config registers
				lReturn = SetConfigRegisters(configReg);

				free(Reader::ppioSendPci);
				SCardDisconnect(*Reader::phCardHandle, SCARD_LEAVE_CARD);
			}
			free(Reader::phCardHandle);

			return lReturn;
		}

		////////////////////////////////////////////////////////////////////////////////
		/////////////////////// TAGWAITER INTERNAL FUNCTIONS ///////////////////////////
		////////////////////////////////////////////////////////////////////////////////
	private:

		// Checks if there is a tag present
		bool CheckIfTag()
		{
			LONG lReturn;
			bool isTag = false;

			// Connect to card
			Reader::phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
			DWORD dwAP; //Active protocol
			lReturn = SCardConnect(*Reader::phContext, Reader::szReader, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, Reader::phCardHandle, &dwAP);
			if (lReturn == SCARD_S_SUCCESS)
			{
				isTag = true;
				SCardDisconnect(*Reader::phCardHandle, SCARD_LEAVE_CARD);
			}

			return isTag;
		}


		// Performs a cycle of writing into the SRAM, waiting for mthe microcontroller to read it and to respond, and reading the response
		LONG PerformSramCom(BYTE*cmd, BYTE* resp)
		{
			LONG lReturn;

			// Send SRAM command
			lReturn = WriteSram(cmd);
			if (lReturn == SCARD_S_SUCCESS)
			{
				// Wait for I2C Read
				lReturn = WaitForI2CRead();
				if (lReturn == SCARD_S_SUCCESS)
				{
					// Wait for I2C Write
					lReturn = WaitForI2CWrite();
					if (lReturn == SCARD_S_SUCCESS)
					{
						// Read SRAM response
						lReturn = ReadSram(resp);
					}
				}
			}

			return lReturn;
		}
		
		// Reads the SRAM and stores the result in the variable data
		LONG ReadSram(BYTE* data)
		{
			LONG lReturn;

			// In Pass-through mode, the SRAM may be mirrored to sector 0 or sector 1
			BYTE NtagVersion;
			lReturn = GET_VERSION(&NtagVersion);
			if (lReturn == SCARD_S_SUCCESS)
			{
				if (NtagVersion == NTAG_VERSION_2K)
					lReturn = SECTOR_SELECT(1);
				if (lReturn == SCARD_S_SUCCESS)
					lReturn = FAST_READ(SRAM_Begin, SRAM_Finish, data);
				if (NtagVersion == NTAG_VERSION_2K)
						END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
			}

			return lReturn;
		}
		
		// Writes the SRAM with the content of the variable data
		LONG WriteSram(BYTE* data)
		{
			LONG lReturn;
			BYTE page[4];

			// In Pass-through mode, the SRAM may be mirrored to sector 0 or sector 1
			BYTE NtagVersion;
			lReturn = GET_VERSION(&NtagVersion);
			if (lReturn == SCARD_S_SUCCESS)
			{
				if (NtagVersion == NTAG_VERSION_2K)
					lReturn = SECTOR_SELECT(1);
				if (lReturn == SCARD_S_SUCCESS)
				{
					// The 64-bytes SRAM Blocks are mapped in 16 pages
					int i = 0;
					do
					{
						page[0] = data[(i * 4) + 0];
						page[1] = data[(i * 4) + 1];
						page[2] = data[(i * 4) + 2];
						page[3] = data[(i * 4) + 3];
						lReturn = WRITE(SRAM_Begin + i, page);
						i++;
					} while (i < 16 && lReturn == SCARD_S_SUCCESS);
				}
				if (NtagVersion == NTAG_VERSION_2K)
					END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
			}

			return lReturn;
		}

		// Gets the config registers of the NTAG
		LONG GetConfigRegisters(Ntag_I2C_Registers_t* configReg)
		{
			LONG lReturn;
			BYTE data[16];

			// Get all the config registers. The Configuration Registers may be located in sector 0 or sector 1
			BYTE NtagVersion;
			lReturn = GET_VERSION(&NtagVersion);
			if (lReturn == SCARD_S_SUCCESS)
			{
				if (NtagVersion == NTAG_VERSION_2K)
					lReturn = SECTOR_SELECT(1);
				// Read configuration registers
				lReturn = READ(ConfigurationPage, data);
				if (lReturn == SCARD_S_SUCCESS)
					parseRegisters(configReg, data);
				if (NtagVersion == NTAG_VERSION_2K)
					END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
			}

			return lReturn;
		}

		// Writes the config registers with the specified content
		LONG SetConfigRegisters(Ntag_I2C_Registers_t configReg)
		{
			LONG lReturn;
			BYTE data[4];

			// Get the bytes in the right form to be written into the tag
			BYTE NC_Reg = 0;
			BYTE LD_Reg = 0;
			BYTE SM_Reg = 0;
			BYTE WD_LS_Reg = 0;
			BYTE WD_MS_Reg = 0;
			BYTE I2C_CLOCK_STR_Reg = 0;
			createConfigRegisters(configReg, &NC_Reg, &LD_Reg, &SM_Reg, &WD_LS_Reg, &WD_MS_Reg, &I2C_CLOCK_STR_Reg);

			// The Configuration Registers may be located in sector 0 or sector 1
			BYTE NtagVersion;
			lReturn = GET_VERSION(&NtagVersion);
			if (lReturn == SCARD_S_SUCCESS)
			{
				if (NtagVersion == NTAG_VERSION_2K)
					lReturn = SECTOR_SELECT(1);

				// Write the Config Regs
				data[0] = NC_Reg;
				data[1] = LD_Reg;
				data[2] = SM_Reg;
				data[3] = WD_LS_Reg;
				lReturn = WRITE(ConfigurationPage, data);
				if (lReturn == SCARD_S_SUCCESS)
				{
					data[0] = WD_MS_Reg;
					data[1] = I2C_CLOCK_STR_Reg;
					data[2] = 0x00;
					data[3] = 0x00;
					lReturn = WRITE(ConfigurationPage + 1, data);
				}
				if (NtagVersion == NTAG_VERSION_2K)
					END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
			}

			return lReturn;
		}

		// Waits for the microcontroller to read the content written in the SRAM
		LONG WaitForI2CRead()
		{
			// The reader can check if the microcontroller has finished reading by checking the bit SRAM_I2C_READY
			// As soon as the microcontroller finishes reading the SRAM the bit SRAM_I2C_READY is set to 1
			// The bit SRAM_I2C_READY is part of the session registers, located in sector 3
			// In order to avoid using the Sector Select commands, this has been implemented with timers
			System::Threading::Thread::Sleep(100);

			return SCARD_S_SUCCESS;
		}

		// Waits for the microcontroller to write content into the SRAM
		LONG WaitForI2CWrite()
		{
			// The reader can check if the microcontroller has finished reading by checking the bit SRAM_RF_READY
			// As soon as the microcontroller finishes reading the SRAM the bit SRAM_RF_READY is set to 0
			// The bit SRAM_RF_READY is part of the session registers, located in sector 3
			// In order to avoid using the Sector Select commands, this has been implemented with timers
			System::Threading::Thread::Sleep(100);

			return SCARD_S_SUCCESS;
		}

		// Waits for the Passthrough mode to be activated
		LONG WaitForPassthroughActive()
		{
			// The reader can check if the Passthrough mode has been activated reading by checking the bit PTHRU_ON_OFF
			// As soon as the Passthrough mode is activated the bit PTHRU_ON_OFF is set to 1
			// The bit PTHRU_ON_OFF is part of the session registers, located in sector 3
			// In order to avoid using the Sector Select commands, this has been implemented with timers
			System::Threading::Thread::Sleep(20);

			return SCARD_S_SUCCESS;
		}
		
		// Reads an NDEF message from the tag
		LONG ReadNdefMessage(BYTE* data, int* length)
		{
			LONG lReturn;
			BYTE cc[16];

			// Check that in page 3 there is the NDEF Magic Number, that in page 4 the tag field is an NDEF message, and the length of the NDEF message
			lReturn = READ(3, cc);
			if (lReturn == SCARD_S_SUCCESS && cc[0] == 0xE1 && cc[4] == 0x03)
			{
				*length = cc[5];
				// Copy into data the bytes of the NDEF message that I already have
				memcpy(data, cc+6, 10);
				// Send read commands until I have read the whole NDEF
				int i = (int)ceil(((float)(*length-10+1)) / 16);
				BYTE* pos = data + 10;
				BYTE page = 7;
				while (i > 0 && lReturn == SCARD_S_SUCCESS)
				{
					lReturn = READ(page, pos);
					i--;
					pos += 16;
					page += 4;
				}
			}
			else if (lReturn == SCARD_S_SUCCESS)	// If the tag is not NDEF formatted
				lReturn = SCARD_E_INVALID_TARGET;

			return lReturn;
		}

		// Writes an NDEF message into the tag
		LONG WriteNdefMessage(BYTE* data, int length)
		{
			LONG lReturn;
			BYTE cc[16];

			// Check that in page 3 there is the NDEF Magic Number
			lReturn = READ(3, cc);
			if (lReturn == SCARD_S_SUCCESS && cc[0] == 0xE1)
			{
				// Send write commands until I have written the whole NDEF
				int i = (int)ceil(((float)(length)) / 4);
				BYTE* pos = data;
				BYTE page = 4;
				data[length] = 0x00;
				data[length + 1] = 0x00;
				data[length + 2] = 0x00;
				while (i > 0 && lReturn == SCARD_S_SUCCESS)
				{
					lReturn = WRITE(page, pos);
					i--;
					pos += 4;
					page ++;
				}
			}
			else if (lReturn == SCARD_S_SUCCESS)	// If the tag is not NDEF formatted
				lReturn = SCARD_E_INVALID_TARGET;

			return lReturn;
		}

		////////////////////////////////////////////////////////////////////////////////
		////////////////////////// COMMAND SENDING FUNCTIONS ///////////////////////////
		////////////////////////////////////////////////////////////////////////////////

		// Gets the version of the NTAG I2C IC
		LONG GET_VERSION(BYTE* version)
		{
			LONG lReturn;
			BYTE cmdGetVersion[] = { 0xFF, 0xEF, 0x00, 0x00, 0x01, 0x60 };
			DWORD cmdLength = 6;
			BYTE respGetVersion[10];
			DWORD respLength = 10;

			lReturn = SCardTransmit(*Reader::phCardHandle, Reader::ppioSendPci, cmdGetVersion, cmdLength, NULL, respGetVersion, &respLength);
			if (lReturn == SCARD_S_SUCCESS && respLength == 10) // Should also check CRC
			{
				if (respGetVersion[6] == 0x13)
					*version = NTAG_VERSION_1K;
				else if (respGetVersion[6] == 0x15)
					*version = NTAG_VERSION_2K;
				else
					lReturn = SCARD_E_UNKNOWN_CARD;	// The version is unknown by this function
			}
			// Check if an error has occurred even though lReturn indicates success
			else if (lReturn == SCARD_S_SUCCESS)
				lReturn = SCARD_E_COMM_DATA_LOST;

			return lReturn;
		}

		// Disables the polling and selects the sector passed as parameter
		// Note that it is necessary to execute the END_SECTOR_SELECT function later, to enable the polling again and to go back to sector 0
		LONG SECTOR_SELECT(BYTE nb_sector)
		{
			LONG lReturn;
			BYTE cmdDisPoll[] = { 0xFF, 0xCC, 0x00, 0x00, 0x02, 0xAC, 0x01 };
			DWORD cmdDisLength = 7;
			BYTE respDisPoll[2];
			DWORD respDisLength = 2;
			BYTE cmdSectorSelect0[] = { 0xFF, 0xEF, 0x00, 0x00, 0x02, 0xC2, 0xFF };
			DWORD cmdSS0Length = 7;
			BYTE respSectorSelect0[1];
			DWORD respSS0Length = 1;
			BYTE cmdSectorSelect1[] = { 0xFF, 0xEF, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00 };
			DWORD cmdSS1Length = 9;
			BYTE respSectorSelect1[1];
			DWORD respSS1Length = 1;

			// Disable polling
			lReturn = SCardTransmit(*Reader::phCardHandle, Reader::ppioSendPci, cmdDisPoll, cmdDisLength, NULL, respDisPoll, &respDisLength);
			if (lReturn == SCARD_S_SUCCESS && respDisLength == 2 && respDisPoll[0] == 0x90 && respDisPoll[1] == 0x00)
			{
				// Send the first command of Sector Select
				lReturn = SCardTransmit(*Reader::phCardHandle, Reader::ppioSendPci, cmdSectorSelect0, cmdSS0Length, NULL, respSectorSelect0, &respSS0Length);
				if (lReturn == SCARD_S_SUCCESS && respSS0Length == 1 && respSectorSelect0[0] == 0x0A)
				{
					// Send the second command of the sector select, indicating the sector
					cmdSectorSelect1[5] = nb_sector;
					lReturn = SCardTransmit(*Reader::phCardHandle, Reader::ppioSendPci, cmdSectorSelect1, cmdSS1Length, NULL, respSectorSelect1, &respSS1Length);

					// Check if an error has occurred even though lReturn indicates success
					if (lReturn == SCARD_S_SUCCESS && respSS1Length != 0)
						lReturn = SCARD_E_COMM_DATA_LOST;
				}
				else if (lReturn == SCARD_S_SUCCESS)
					lReturn = SCARD_E_COMM_DATA_LOST;
			}
			else if (lReturn == SCARD_S_SUCCESS)
				lReturn = SCARD_E_COMM_DATA_LOST;

			return lReturn;
		}

		// Enables the polling and goes back to sector 0
		LONG END_SECTOR_SELECT()
		{
			LONG lReturn;
			BYTE cmdEnPoll[] = { 0xFF, 0xCC, 0x00, 0x00, 0x02, 0xAC, 0x00 };
			DWORD cmdEnLength = 7;
			BYTE respEnPoll[2];
			DWORD respEnLength = 2;
			BYTE cmdError[] = { 0xFF, 0xEF, 0x00, 0x00, 0x01, 0x00 };
			DWORD cmdErrorLength = 6;
			BYTE respError[1];
			DWORD respErrorLength = 1;

			// Enable polling
			lReturn = SCardTransmit(*Reader::phCardHandle, Reader::ppioSendPci, cmdEnPoll, cmdEnLength, NULL, respEnPoll, &respEnLength);
			// Check if an error has occurred even though lReturn indicates success
			if (lReturn == SCARD_S_SUCCESS && (respEnLength != 2 || respEnPoll[0] != 0x90 || respEnPoll[1] != 0x00))
				lReturn = SCARD_E_COMM_DATA_LOST;

			// Send a command that causes an error. This way we ensure that the polling is working again and that we are in sector 0
			SCardTransmit(*Reader::phCardHandle, Reader::ppioSendPci, cmdError, cmdErrorLength, NULL, respError, &respErrorLength);

			return lReturn;
		}

		// Sends a Read command and stores the result in the variable data
		LONG READ(BYTE page, BYTE* data)
		{
			LONG lReturn;
			BYTE cmdRead[] = { 0xFF, 0xEF, 0x00, 0x00, 0x02, 0x30, 0x00 };
			DWORD cmdReadLength = 7;
			BYTE respRead[18];
			DWORD respReadLength = 18;

			// Send Read command
			cmdRead[6] = page;
			lReturn = SCardTransmit(*Reader::phCardHandle, Reader::ppioSendPci, cmdRead, cmdReadLength, NULL, respRead, &respReadLength);
			if (lReturn == SCARD_S_SUCCESS && respReadLength == 18) // Should also check CRC
			{
				memcpy(data, respRead, respReadLength - 2);
			}
			// Check if an error has occurred even though lReturn indicates success
			else if (lReturn == SCARD_S_SUCCESS)
				lReturn = SCARD_E_COMM_DATA_LOST;

			return lReturn;
		}
		
		// Sends a Fast Read command and stores the result in the variable data
		LONG FAST_READ(BYTE startPage, BYTE endPage, BYTE* data)
		{
			LONG lReturn;
			BYTE cmdFastRead[] = { 0xFF, 0xEF, 0x00, 0x00, 0x03, 0x3A, 0x00, 0x00 };
			DWORD cmdFastReadLength = 8;
			BYTE respFastRead[1026];
			DWORD respFastReadLength = 1026;

			// Send Fast Read command
			cmdFastRead[6] = startPage;
			cmdFastRead[7] = endPage;
			lReturn = SCardTransmit(*Reader::phCardHandle, Reader::ppioSendPci, cmdFastRead, cmdFastReadLength, NULL, respFastRead, &respFastReadLength);
			if (lReturn == SCARD_S_SUCCESS && respFastReadLength == (endPage - startPage + 1) * 4 + 2) // Should also check CRC
			{
				memcpy(data, respFastRead, respFastReadLength-2);
			}
			// Check if an error has occurred even though lReturn indicates success
			else if (lReturn == SCARD_S_SUCCESS)
				lReturn = SCARD_E_COMM_DATA_LOST;

			return lReturn;
		}

		// Sends a Write command with the content of the variable data
		LONG WRITE(BYTE page, BYTE* data)
		{
			LONG lReturn;
			BYTE cmdWrite[] = { 0xFF, 0xEF, 0x00, 0x00, 0x06, 0xA2, 0x00, 0x00, 0x00, 0x00, 0x00 };
			DWORD cmdWriteLength = 11;
			BYTE respWrite[1];
			DWORD respWriteLength = 1;

			// Send Write command
			cmdWrite[6] = page;
			cmdWrite[7] = data[0];
			cmdWrite[8] = data[1];
			cmdWrite[9] = data[2];
			cmdWrite[10] = data[3];
			lReturn = SCardTransmit(*Reader::phCardHandle, Reader::ppioSendPci, cmdWrite, cmdWriteLength, NULL, respWrite, &respWriteLength);
			// Check if an error has occurred even though lReturn indicates success
			if (lReturn == SCARD_S_SUCCESS && (respWriteLength != 1 || respWrite[0] != 0x0A))
				lReturn = SCARD_E_COMM_DATA_LOST;

			return lReturn;
		}

		////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////// PARSING FUNCTIONS //////////////////////////////
		////////////////////////////////////////////////////////////////////////////////

		// Gets an URI type identifier and returns the URI string
		LONG getUriType(BYTE uriType, char* payload, BYTE* uriLength)
		{
			LONG lReturn = SCARD_S_SUCCESS;

			switch (uriType)
			{
			case 0x01:
				strcpy_s(payload, 30, "http://www.");
				*uriLength = 11;
				break;
			case 0x02:
				strcpy_s(payload, 30, "https://www.");
				*uriLength = 12;
				break;
			case 0x03:
				strcpy_s(payload, 30, "http://");
				*uriLength = 7;
				break;
			case 0x04:
				strcpy_s(payload, 30, "https://");
				*uriLength = 8;
				break;
			case 0x05:
				strcpy_s(payload, 30, "tel:");
				*uriLength = 4;
				break;
			case 0x06:
				strcpy_s(payload, 30, "mailto:");
				*uriLength = 7;
				break;
			case 0x07:
				strcpy_s(payload, 30, "ftp://anonymous:anonymous@");
				*uriLength = 26;
				break;
			case 0x08:
				strcpy_s(payload, 30, "ftp://ftp.");
				*uriLength = 10;
				break;
			case 0x09:
				strcpy_s(payload, 30, "ftps://");
				*uriLength = 7;
				break;
			case 0x0A:
				strcpy_s(payload, 30, "sftp://");
				*uriLength = 7;
				break;
			case 0x0B:
				strcpy_s(payload, 30, "smb://");
				*uriLength = 6;
				break;
			case 0x0C:
				strcpy_s(payload, 30, "nfs://");
				*uriLength = 6;
				break;
			case 0x0D:
				strcpy_s(payload, 30, "ftp://");
				*uriLength = 6;
				break;
			case 0x0E:
				strcpy_s(payload, 30, "dav://");
				*uriLength = 6;
				break;
			case 0x0F:
				strcpy_s(payload, 30, "news:");
				*uriLength = 5;
				break;
			case 0x10:
				strcpy_s(payload, 30, "telnet://");
				*uriLength = 9;
				break;
			case 0x11:
				strcpy_s(payload, 30, "imap:");
				*uriLength = 5;
				break;
			case 0x12:
				strcpy_s(payload, 30, "rtsp://");
				*uriLength = 7;
				break;
			case 0x13:
				strcpy_s(payload, 30, "urn:");
				*uriLength = 4;
				break;
			case 0x14:
				strcpy_s(payload, 30, "pop:");
				*uriLength = 4;
				break;
			case 0x15:
				strcpy_s(payload, 30, "sip:");
				*uriLength = 4;
				break;
			case 0x16:
				strcpy_s(payload, 30, "sips:");
				*uriLength = 5;
				break;
			case 0x17:
				strcpy_s(payload, 30, "tftp:");
				*uriLength = 5;
				break;
			case 0x18:
				strcpy_s(payload, 30, "btspp://");
				*uriLength = 8;
				break;
			case 0x19:
				strcpy_s(payload, 30, "btl2cap://");
				*uriLength = 10;
				break;
			case 0x1A:
				strcpy_s(payload, 30, "btgoep://");
				*uriLength = 9;
				break;
			case 0x1B:
				strcpy_s(payload, 30, "tcpobex://");
				*uriLength = 10;
				break;
			case 0x1C:
				strcpy_s(payload, 30, "irdaobex://");
				*uriLength = 11;
				break;
			case 0x1D:
				strcpy_s(payload, 30, "file://");
				*uriLength = 7;
				break;
			case 0x1E:
				strcpy_s(payload, 30, "urn:epc:id:");
				*uriLength = 11;
				break;
			case 0x1F:
				strcpy_s(payload, 30, "urn:epc:tag:");
				*uriLength = 12;
				break;
			case 0x20:
				strcpy_s(payload, 30, "urn:epc:pat:");
				*uriLength = 12;
				break;
			case 0x21:
				strcpy_s(payload, 30, "urn:epc:raw:");
				*uriLength = 12;
				break;
			case 0x22:
				strcpy_s(payload, 30, "urn:epc:");
				*uriLength = 8;
				break;
			case 0x23:
				strcpy_s(payload, 30, "urn:epc:raw");
				*uriLength = 11;
				break;
			default:
				lReturn = SCARD_E_INVALID_TARGET;
			}

			return lReturn;
		}

		// Gets an URI string and returns the URI type identifier
		LONG getUriIdentifier(char* payload, BYTE *uriType, BYTE* uriLength)
		{
			LONG lReturn = SCARD_S_SUCCESS;

			// Change from strstr to strncmp
			if (strstr(payload, "http://www.") != NULL) {
				*uriType = 0x01;
				*uriLength = 11;
			}
			else if (strstr(payload, "https://www.") != NULL) {
				*uriType = 0x02;
				*uriLength = 12;
			}
			else if (strstr(payload, "http://") != NULL) {
				*uriType = 0x03;
				*uriLength = 7;
			}
			else if (strstr(payload, "https://") != NULL) {
				*uriType = 0x04;
				*uriLength = 8;
			}
			else if (strstr(payload, "tel:") != NULL) {
				*uriType = 0x05;
				*uriLength = 4;
			}
			else if (strstr(payload, "mailto:") != NULL) {
				*uriType = 0x06;
				*uriLength = 7;
			}
			else if (strstr(payload, "ftp://anonymous:anonymous@") != NULL) {
				*uriType = 0x07;
				*uriLength = 26;
			}
			else if (strstr(payload, "ftp://ftp.") != NULL) {
				*uriType = 0x08;
				*uriLength = 10;
			}
			else if (strstr(payload, "ftps://") != NULL) {
				*uriType = 0x09;
				*uriLength = 7;
			}
			else if (strstr(payload, "sftp://") != NULL) {
				*uriType = 0x0A;
				*uriLength = 7;
			}
			else if (strstr(payload, "smb://") != NULL) {
				*uriType = 0x0B;
				*uriLength = 6;
			}
			else if (strstr(payload, "nfs://") != NULL) {
				*uriType = 0x0C;
				*uriLength = 6;
			}
			else if (strstr(payload, "ftp://") != NULL) {
				*uriType = 0x0D;
				*uriLength = 6;
			}
			else if (strstr(payload, "dav://") != NULL) {
				*uriType = 0x0E;
				*uriLength = 6;
			}
			else if (strstr(payload, "news:") != NULL) {
				*uriType = 0x0F;
				*uriLength = 5;
			}
			else if (strstr(payload, "telnet://") != NULL) {
				*uriType = 0x10;
				*uriLength = 9;
			}
			else if (strstr(payload, "imap:") != NULL) {
				*uriType = 0x11;
				*uriLength = 5;
			}
			else if (strstr(payload, "rtsp://") != NULL) {
				*uriType = 0x12;
				*uriLength = 7;
			}
			else if (strstr(payload, "urn:") != NULL) {
				*uriType = 0x13;
				*uriLength = 4;
			}
			else if (strstr(payload, "pop:") != NULL) {
				*uriType = 0x14;
				*uriLength = 4;
			}
			else if (strstr(payload, "sip:") != NULL) {
				*uriType = 0x15;
				*uriLength = 4;
			}
			else if (strstr(payload, "sips:") != NULL) {
				*uriType = 0x16;
				*uriLength = 5;
			}
			else if (strstr(payload, "tftp:") != NULL) {
				*uriType = 0x17;
				*uriLength = 5;
			}
			else if (strstr(payload, "btspp://") != NULL) {
				*uriType = 0x18;
				*uriLength = 8;
			}
			else if (strstr(payload, "btl2cap://") != NULL) {
				*uriType = 0x19;
				*uriLength = 10;
			}
			else if (strstr(payload, "btgoep://") != NULL) {
				*uriType = 0x1A;
				*uriLength = 9;
			}
			else if (strstr(payload, "tcpobex://") != NULL) {
				*uriType = 0x1B;
				*uriLength = 10;
			}
			else if (strstr(payload, "irdaobex://") != NULL) {
				*uriType = 0x1C;
				*uriLength = 11;
			}
			else if (strstr(payload, "file://") != NULL) {
				*uriType = 0x1D;
				*uriLength = 7;
			}
			else if (strstr(payload, "urn:epc:id:") != NULL) {
				*uriType = 0x1E;
				*uriLength = 11;
			}
			else if (strstr(payload, "urn:epc:tag:") != NULL) {
				*uriType = 0x1F;
				*uriLength = 12;
			}
			else if (strstr(payload, "urn:epc:pat:") != NULL) {
				*uriType = 0x20;
				*uriLength = 12;
			}
			else if (strstr(payload, "urn:epc:raw:") != NULL) {
				*uriType = 0x21;
				*uriLength = 12;
			}
			else if (strstr(payload, "urn:epc:") != NULL) {
				*uriType = 0x22;
				*uriLength = 8;
			}
			else if (strstr(payload, "urn:epc:raw") != NULL) {
				*uriType = 0x23;
				*uriLength = 11;
			}
			else {
				*uriType = 0x00;
				*uriLength = 0;

				lReturn = SCARD_E_INVALID_VALUE;
			}

			return lReturn;
		}

		// Gets a bluetooth pairing NDEF message and returns the Bluetooth information parsed
		LONG parseBTPairRecord(char* input, char* output, int* payloadSize)
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
		LONG createTextRecord(BYTE* payload, int payloadSize, BYTE* message, int* length)
		{
			// NDEF header
			BYTE ndef_header[] = { 0x03, payloadSize + 7, 0xD1, 0x01, payloadSize + 3, 0x54, 0x02, 0x65, 0x6E };
			int ndefHeaderSize = ARRAY_SIZE(ndef_header);

			// NDEF message
			memcpy(message, ndef_header, ndefHeaderSize);
			memcpy(message + ndefHeaderSize, payload, payloadSize);
			message[ndefHeaderSize + payloadSize] = 0xFE;
			*length = ndefHeaderSize + payloadSize + 1;

			return SCARD_S_SUCCESS;
		}

		// Creates a URI-type NDEF message
		LONG createUriRecord(BYTE* payload, int payloadSize, BYTE* message, int* length)
		{
			LONG lReturn;
			BYTE uriType = 0;
			BYTE uriLength = 0;
			
			// We have to filter the URI type and get the appropriate URI Identifier
			lReturn = getUriIdentifier((char*)payload, &uriType, &uriLength);
			if (lReturn == SCARD_S_SUCCESS)
			{
				// Recalculate the new size
				payloadSize = payloadSize - uriLength;

				// NDEF header
				BYTE ndef_header[] = { 0x03, payloadSize + 5, 0xD1, 0x01, payloadSize + 1, 0x55 };
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
		LONG createBTPairRecord(BYTE* payload, int payloadSize, BYTE* message, int* length)
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
			BYTE recordHs[] = { 0x03, 15 + headerBtLength + strlen(MIME_BTPAIR) + payloadBtLength, 0x91, 0x02, 0x0A, 0x48, 0x73, 0x12, 0xD1, 0x02, 0x04, 0x61, 0x63, 0x01, 0x01, 0x30, 0x00 };
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
		LONG createSPRecord(BYTE* payload, int payloadSize, BYTE* message, int* length)
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
			lReturn = getUriIdentifier((char*)link, &uriType, &uriLength);
			if (lReturn == SCARD_S_SUCCESS)
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

		// Appends an AAR to an NDEF message
		LONG AppendAAR(BYTE* message, int* length)
		{
			// AAR header
			BYTE AARheader[] = {0x54, 0x0F, 0x17 };
			int AARheaderSize = ARRAY_SIZE(AARheader);

			// AAR text
			BYTE AARtext [] = "android.com:pkgcom.nxp.ntagi2cdemo_dev";
			int AARtextSize = ARRAY_SIZE(AARtext) - 1;	// We don't count here the '\0' at the end

			// NDEF message
			memcpy(message + *length - 1, AARheader, AARheaderSize);
			memcpy(message + *length - 1 + AARheaderSize, AARtext, AARtextSize);
			message[*length - 1 + AARheaderSize + AARtextSize] = 0xFE;
			*length += AARheaderSize + AARtextSize;
			message[1] += AARheaderSize + AARtextSize;
			message[2] = 0x91;

			return SCARD_S_SUCCESS;
		}

		// Parses all the registers from the input and returns it in an NTAG_I2C_Registers variable
		void parseRegisters(Ntag_I2C_Registers *regs, BYTE input[16])
		{
			BYTE NtagVersion = 0;
			if (GET_VERSION(&NtagVersion) == SCARD_S_SUCCESS)
			{
				if (NtagVersion == NTAG_VERSION_1K) {
					memcpy(regs->REG_Manufacture, "NXP NTAG I2C 1K", strlen("NXP NTAG I2C 1K") + 1);
					regs->REG_Mem_size = NTAG_I2C_1k_MemSize;
				}
				else if (NtagVersion == NTAG_VERSION_2K) {
					memcpy(regs->REG_Manufacture, "NXP NTAG I2C 2K", strlen("NXP NTAG I2C 2K") + 1);
					regs->REG_Mem_size = NTAG_I2C_2k_MemSize;
				}
				else
				{
					memcpy(regs->REG_Manufacture, "", strlen("") + 1);
					regs->REG_Mem_size = 0;
				}
			}
			else
			{
				memcpy(regs->REG_Manufacture, "", strlen("") + 1);
				regs->REG_Mem_size = 0;
			}

			BYTE NC_Reg = input[NC_REG];

			// check I2C_RST_ON_OFF
			//// more sense to do: regs->REG_I2C_RST_ON_OFF = (NC_Reg & I2C_RST_ON_OFF == I2C_RST_ON_OFF) , here and in all the rest
			if ((NC_Reg & I2C_RST_ON_OFF) == I2C_RST_ON_OFF)
				regs->REG_I2C_RST_ON_OFF = TRUE;
			else
				regs->REG_I2C_RST_ON_OFF = FALSE;

			// check FD_OFF
			BYTE tmpReg = (NC_Reg & FD_OFF);
			//// change to switch
			if (tmpReg == (0x30))
				memcpy(regs->REG_FD_OFF, "11b", 3);
			if (tmpReg == (0x20))
				memcpy(regs->REG_FD_OFF, "10b", 3);
			if (tmpReg == (0x10))
				memcpy(regs->REG_FD_OFF, "01b", 3);
			if (tmpReg == (0x00))
				memcpy(regs->REG_FD_OFF, "00b", 3);;

			// check FD_ON
			tmpReg = (NC_Reg & FD_ON);
			//// change to switch
			if (tmpReg == (0x0c))
				memcpy(regs->REG_FD_ON, "11b", 3);
			if (tmpReg == (0x08))
				memcpy(regs->REG_FD_ON, "10b", 3);
			if (tmpReg == (0x04))
				memcpy(regs->REG_FD_ON, "01b", 3);
			if (tmpReg == (0x00))
				memcpy(regs->REG_FD_ON, "00b", 3);

			// Last NDEF Page
			regs->REG_LAST_NDEF_PAGE = (0x00000FF & input[LAST_NDEF_PAGE]);

			BYTE NS_Reg = input[NS_REG];

			// check NDEF_DATA_READ
			if ((NS_Reg & NDEF_DATA_READ) == NDEF_DATA_READ)
				regs->REG_NDEF_DATA_READ = TRUE;
			else
				regs->REG_NDEF_DATA_READ = FALSE;

			// check RF_FIELD
			if ((NS_Reg & RF_FIELD_PRESENT) == RF_FIELD_PRESENT)
				regs->REG_RF_FIELD_PRESENT = TRUE;
			else
				regs->REG_RF_FIELD_PRESENT = FALSE;

			// check PTHRU_ON_OFF
			if ((NC_Reg & PTHRU_ON_OFF) == PTHRU_ON_OFF)
				regs->REG_PTHRU_ON_OFF = TRUE;
			else
				regs->REG_PTHRU_ON_OFF = FALSE;

			// check I2C_LOCKED
			if ((NS_Reg & I2C_LOCKED) == I2C_LOCKED)
				regs->REG_I2C_LOCKED = TRUE;
			else
				regs->REG_I2C_LOCKED = FALSE;

			// check RF_LOCK
			if ((NS_Reg & RF_LOCKED) == RF_LOCKED)
				regs->REG_RF_LOCKED = TRUE;
			else
				regs->REG_RF_LOCKED = FALSE;

			// check check SRAM_I2C_Ready
			if ((NS_Reg & SRAM_I2C_READY) == SRAM_I2C_READY)
				regs->REG_SRAM_I2C_READY = TRUE;
			else
				regs->REG_SRAM_I2C_READY = FALSE;

			// check SRAM_RF_READY
			tmpReg = (BYTE)(NS_Reg & SRAM_RF_READY);
			if ((NS_Reg & SRAM_RF_READY) == SRAM_RF_READY)
				regs->REG_SRAM_RF_READY = TRUE;
			else
				regs->REG_SRAM_RF_READY = FALSE;

			// check SRAM_RF_READY
			tmpReg = (BYTE)(NS_Reg & EEPROM_WR_BUSY);
			if ((NS_Reg & EEPROM_WR_BUSY) == EEPROM_WR_BUSY)
				regs->REG_EEPROM_WR_BUSY = TRUE;
			else
				regs->REG_EEPROM_WR_BUSY = FALSE;

			// check PTHRU_DIR
			tmpReg = (BYTE)(NC_Reg & (BYTE)0x01);
			if (tmpReg == (0x01))
				regs->REG_PTHRU_DIR = TRUE;
			else
				regs->REG_PTHRU_DIR = FALSE;

			// SM_Reg
			regs->REG_SM_Reg = (0x00000FF & input[SM_REG]);

			// WD_LS_Reg
			regs->REG_WD_LS_Reg = (0x00000FF & input[WDT_LS]);

			// WD_MS_Reg
			regs->REG_WD_MS_Reg = (0x00000FF & input[WDT_MS]);

			// check SRAM_MIRROR_ON_OFF
			if ((NC_Reg & SRAM_MIRROR_ON_OFF) == SRAM_MIRROR_ON_OFF)
				regs->REG_SRAM_MIRROR_ON_OFF = TRUE;
			else
				regs->REG_SRAM_MIRROR_ON_OFF = FALSE;

			// I2C_CLOCK_STR
			if (input[I2C_CLOCK_STR] == 1)
				regs->REG_I2C_CLOCK_STR = TRUE;
			else
				regs->REG_I2C_CLOCK_STR = FALSE;
		}

		// Gets an NTAG_I2C_Registers variable and leaves them in the right form to be written into the tag
		void createConfigRegisters(Ntag_I2C_Registers regs, BYTE* NC_Reg, BYTE* LD_Reg, BYTE* SM_Reg, BYTE* WD_LS_Reg, BYTE* WD_MS_Reg, BYTE* I2C_CLOCK_STR_Reg)
		{
			char* FD_OFF_Value = regs.REG_FD_OFF;
			char* FD_ON_Value = regs.REG_FD_ON;

			if (strncmp(FD_OFF_Value, "11b", 3) == 0)
				*NC_Reg = (*NC_Reg | 0x30);

			if (strncmp(FD_OFF_Value, "10b", 3) == 0) {
				*NC_Reg = (*NC_Reg & 0xcf);
				*NC_Reg = (*NC_Reg | 0x20);
			}

			if (strncmp(FD_OFF_Value, "01b", 3) == 0) {
				*NC_Reg = (*NC_Reg & 0xcf);
				*NC_Reg = (*NC_Reg | 0x10);
			}

			if (strncmp(FD_OFF_Value, "00b", 3) == 0)
				*NC_Reg = (*NC_Reg & 0xcf);

			if (strncmp(FD_ON_Value, "11b", 3) == 0)
				*NC_Reg = (*NC_Reg | 0x0c);

			if (strncmp(FD_ON_Value, "10b", 3) == 0)  {
				*NC_Reg = (*NC_Reg & 0xf3);
				*NC_Reg = (*NC_Reg | 0x08);
			}

			if (strncmp(FD_ON_Value, "01b", 3) == 0) {
				*NC_Reg = (*NC_Reg & 0xf3);
				*NC_Reg = (*NC_Reg | 0x04);
			}

			if (strncmp(FD_ON_Value, "00b", 3) == 0)
				*NC_Reg = (*NC_Reg & 0xf3);

			if (regs.REG_PTHRU_DIR == TRUE)
				*NC_Reg = (*NC_Reg | 0x01);
			else
				*NC_Reg = (*NC_Reg & 0xfe);

			*LD_Reg = regs.REG_LAST_NDEF_PAGE;
			*SM_Reg = regs.REG_SM_Reg;
			*WD_LS_Reg = regs.REG_WD_LS_Reg;
			*WD_MS_Reg = regs.REG_WD_MS_Reg;

			if (regs.REG_I2C_CLOCK_STR == TRUE)
				*I2C_CLOCK_STR_Reg = 1;
			else
				*I2C_CLOCK_STR_Reg = 0;

			if (regs.REG_I2C_RST_ON_OFF == TRUE)
				*NC_Reg = (*NC_Reg | 0x80);
			else
				*NC_Reg = (*NC_Reg & 0x7f);
		}
	};
}*/