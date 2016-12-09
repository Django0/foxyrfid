#include "winscard.h"
#include "Reader.h"
#include <iostream>
#include <string>

using namespace NTAG_I2C_Demo;

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

	Reader::Reader(){
		szReader = L"Identiv CLOUD 3700 F Contactless Reader 0";
	}

	Reader::Reader(LPCTSTR readerIdentifierString){
		szReader = readerIdentifierString;
	}

	long Reader::setContext(){
		phContext = (SCARDCONTEXT*)malloc(sizeof(SCARDCONTEXT));
		return SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, phContext);
	};

	long Reader::releaseContext(){

		long res = SCardReleaseContext(*phContext);
		free(phContext);
		return res;
	};

	long Reader::getConnectedReaders(LPTSTR* pmszReaders, DWORD* cch){
		return SCardListReaders(*phContext, NULL, (LPTSTR)pmszReaders, cch);
	}

	void getReaderFWVersionFromReaderInfo(ReaderInfoExtended strReaderInfo, char* IdentivReaderFWversion){
		IdentivReaderFWversion[0] = '0' + strReaderInfo.byMajorVersion;
		IdentivReaderFWversion[1] = '.';
		IdentivReaderFWversion[2] = '0' + strReaderInfo.byMinorVersion;
	}

	long Reader::readIdentivFWversion(char* IdentivReaderFWversion)
	{
		ReaderInfoExtended strReaderInfo;
		BYTE inByte;
		DWORD BytesRead;
		LONG ret;

				inByte = 0x1E;
				ret = SCardControl(*phCardHandle, IOCTL_CCID_ESCAPE, &inByte, 1, &strReaderInfo, sizeof(strReaderInfo), &BytesRead);
				if (ret == SCARD_S_SUCCESS)
				{
					getReaderFWVersionFromReaderInfo(strReaderInfo, IdentivReaderFWversion);
				}
		return ret;
	};

	long Reader::cardConnect_DIRECT_Mode(DWORD* pActiveProtocol){
		phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
		return SCardConnect(*phContext, szReader, SCARD_SHARE_DIRECT, SCARD_PROTOCOL_UNDEFINED, phCardHandle, pActiveProtocol);
	}

	long Reader::cardConnect_SHARED_Mode(DWORD* pActiveProtocol){
		phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
		return SCardConnect(*phContext, szReader, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, phCardHandle, pActiveProtocol);
	}

	long Reader::cardConnect_EXCLUSIVE_Mode(DWORD* pActiveProtocol){
		phCardHandle = (SCARDHANDLE*)malloc(sizeof(SCARDHANDLE));
		long nr_return;
		int i = 0;
		do
		{
			nr_return = SCardConnect(*phContext, szReader, SCARD_SHARE_EXCLUSIVE, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, phCardHandle, pActiveProtocol);
			Sleep(50);
			i++;
		} while (nr_return == SCARD_E_SHARING_VIOLATION && i < 10);
		return nr_return;
	}

	void Reader::sendPciConfig(DWORD nr_dwAP){
		ppioSendPci = (SCARD_IO_REQUEST*)malloc(sizeof(SCARD_IO_REQUEST));
		ppioSendPci->dwProtocol = nr_dwAP;
		ppioSendPci->cbPciLength = 8;
	}

	long Reader::cardTransmit(LPCBYTE rpSendBuffer, DWORD rSendLength, LPSCARD_IO_REQUEST rpRecvPci, LPBYTE rpRecvBuffer, LPDWORD rpRecvLength){
		return SCardTransmit(*phCardHandle, ppioSendPci, rpSendBuffer, rSendLength, rpRecvPci, rpRecvBuffer, rpRecvLength);					 
	}																																		

	long Reader::cardDisconnect(){
		return SCardDisconnect(*phCardHandle, SCARD_LEAVE_CARD);
	}

	boolean Reader::isReaderConnected(){
		return isReader;
	}





