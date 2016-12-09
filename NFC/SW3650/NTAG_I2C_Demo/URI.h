#ifndef URI_H
#define URI_H
static ref class URI
{
public:
	static LONG getUriType(BYTE uriType, char* payload, BYTE* uriLength);
	static LONG getUriIdentifier(char* payload, BYTE *uriType, BYTE* uriLength);
};

#endif