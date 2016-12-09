#ifndef NDEFmsg_H
#define NDEFmsg_H
#include "SRAM.h"

namespace NTAG_I2C_Demo
{
	///
	/// NDEFmsg will execute basic NDEF operations like read/write.
	///
	class  NDEFmsg
	{
	public:

		RF_Commands* rf_cmd; /**< This atribute is a pointer to a RF_Commands object in order to execute some methods of that class. */
		bool auth = false;
		std::string pass_ndef;

		NDEFmsg(RF_Commands *rf_in);

		LONG setAuthentication(std::string pass);

		/** @brief Reads a NDEF message received.
		*
		*  First of all we need to establish a shared connection.
		*  Then we start a timer for the read operation and call ReadNdefMessage method.
		*  This method will execute READ operations in order to get the NDEF message.
		*  Once we have the NDEF message we check what kind of message it is (Smart Poster, URI, etc.).
		*  Finally we free the memory used and release the connection.
		*
		*  @param NdefType In this variable we will store the type of the NDEF message.
		*  @param payload This parameter will contain the data to be read.
		*  @param payloadSize Contains the size of the payload.
		*  @param AARPresent This boolean checks if the AAR is present.
		*  @param AAR Value of the AAR record.
		*  @param AARSize AAR size.
		*  @param readBytes Bytes are read 16 by 16 so this parameter will set a multiple of 16.
		*  @param readTime This parameter will contain the time needed to execute this method.
		*  @return Returns a long value, if this value is 0 means that we have been able to read correctly the NDEF message.
		*/
		LONG ReadNdef(int* NdefType, BYTE* payload, int* payloadSize, BOOL *AARPresent, BYTE* AAR, int*AARSize, DWORD* readBytes, float* readTime);

		/** @brief Writes a NDEF message.
		*
		*  First of all we need to establish a shared connection.
		*  Then we start a timer for the write operation and create the NDEF message.
		*  Once we have the message created, we add the AAR if needed and later we call
		*  WriteNdefMessage method that will actually write into the memory the NDEF message created.
		*  Finally we need to release the current connection.
		*
		*  @param NdefType In this variable we will store the type of the NDEF message.
		*  @param payload This parameter will contain the data to be read.
		*  @param payloadSize Contains the size of the payload.
		*  @param addAAR This boolean checks if the AAR is needed.
		*  @param writeBytes Bytes are writen 4 by 4 so this parameter will set a multiple of 4.
		*  @param writeTime This parameter will contain the time needed to execute this method.
		*  @return Returns a long value, if this value is 0 means that we have been able to write correctly the NDEF message.
		*/
		LONG WriteNdef(int NdefType, BYTE* payload, int payloadSize, BOOL addAAR, DWORD* writeBytes, float* writeTime);

		LONG ReadNdefMessage(BYTE* data, int* length);
		LONG WriteNdefMessage(BYTE* data, int length);

		BYTE* CreateDefaultNDEFmessage();
		LONG AppendAAR(BYTE* message, int* length);
		int numberBytes2Write(int payloadNDEFSize);

		LONG createSPRecord(BYTE payload[], int payloadSize, BYTE* message, int* length);

	private:
		bool isReturnSuccess(LONG response);

	};
}

#endif