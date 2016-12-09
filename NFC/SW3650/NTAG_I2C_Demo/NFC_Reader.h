#ifndef Reader_H
#define Reader_H

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

static ref class Reader
{
public:
	static SCARDCONTEXT* phContext;	
	static LPCTSTR szReader;
	static SCARDHANDLE* phCardHandle;	
	static SCARD_IO_REQUEST* ppioSendPci; 

	static event System::EventHandler^ TagEvent;
	static event System::EventHandler^ TagRemovedEvent;

	//TODO: move to application layer
	static bool isReader = false;
	static bool isLedDemo = false;
	static bool endWait; 
	static bool killThread = false;

	static VOID setContext();
	static VOID releaseContext();

	static VOID initReader();
	static LONG readIdentivFWversion(char* IdentivReaderFWversion); 

	static LONG cardConnect_DIRECT_Mode(){}
	static LONG cardConnect_SHARED_Mode(){}
	static LONG cardConnect_EXCLUSIVE_Mode(){}
};

#endif