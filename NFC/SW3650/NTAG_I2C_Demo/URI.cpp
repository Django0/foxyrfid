#include "stdafx.h"
#include "URI.h"

// Gets an URI type identifier and returns the URI string
LONG URI::getUriType(BYTE uriType, char* payload, BYTE* uriLength)
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
	LONG URI::getUriIdentifier(char* payload, BYTE *uriType, BYTE* uriLength)
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
