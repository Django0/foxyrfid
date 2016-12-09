#ifndef NDEFRecord_H
#define NDEFRecord_H

ref class NDEFRecord
{
public:
	static LONG parseBTPairRecord(char* input, char* output, int* payloadSize);
	static LONG createTextRecord(BYTE* payload, int payloadSize, BYTE* message, int* length);
	static LONG createUriRecord(BYTE* payload, int payloadSize, BYTE* message, int* length);
	static LONG createBTPairRecord(BYTE* payload, int payloadSize, BYTE* message, int* length);
	static LONG createSPRecord(BYTE* payload, int payloadSize, BYTE* message, int* length);
};

#endif