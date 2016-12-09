#ifndef NTAG_I2C_RF_H
#define NTAG_I2C_RF_H
#include "Reader.h"
#include "NTAG_I2C_Glossary.h"
#include "Ntag_I2C.h"

namespace NTAG_I2C_Demo {

	///
	/// RF Commands class is suposed to manage the
	/// communications between the reader and the card i.e. Read, Fast_read, Write, Sector select, etc.
	///
	class RF_Commands
	{
	public:

		Reader* sCardReader; /**< This atribute will be a pointer to an object of the class Reader. */

		//Constructors
		RF_Commands();
		RF_Commands(LPCTSTR readerIdentifierString);

		/** @brief Gets the version of the NTAG I2C IC.
		*
		*  With the sCardReader object we transmit a GET_VERSION command,
		*  then we store the response of that command in order to get the version.
		*
		*  @param version is a pointer to the byte that stores the version of the NTAG I2C IC.
		*  @return Result of the Get_Version command (if success it will be 0).
		*/
		LONG GET_VERSION(BYTE* version);

		/** @brief Select a sector from the NTAG I2C IC.
		*
		*  First of all we transmit a Disable polling command, later we send a sector select 0
		*  or a sector select 1, depending on the parameter
		*
		*  @param nb_sector sector to be selected (0 or 1).
		*  @return Result of the SECTOR_SELECT command (if success it will be 0).
		*/
		LONG SECTOR_SELECT(BYTE nb_sector);

		/** @brief Ends the sector selection.
		*
		*  Transmits a command to enable the polling and later we ensure that polling is working
		*  by sending a command that we know it will cause an error so the polling can detects it.
		*
		*  @return Result of the END_SECTOR_SELECT command (if success it will be 0).
		*/
		LONG END_SECTOR_SELECT();

		/** @brief Sends a Read command and stores the result in the variable 'data'.
		*
		*  Sends a CardTransmit read command.
		*
		*  @param page establish the desired page for reading.
		*  @param data is a pointer to the read data.
		*  @return Result of the READ command (if success it will be 0).
		*/
		LONG READ(BYTE page, BYTE* data);

		/** @brief Sends a PWD_AUTH command.
		*
		*  Sends a PWD_AUTH command.
		*
		*  @param page establish the desired page for reading.
		*  @param password is a pointer to the password chosen.
		*  @return Result of the PWD_AUTH command (if success it will be 0).
		*/
		LONG PWD_AUTH(BYTE* password);

		/** @brief Sends a Fast_Read command and stores the result in the variable 'data'.
		*
		*  Sends a CardTransmit fast read command.
		*
		*  @param startPage Sets the first page for reading.
		*  @param endPage Sets the last page for reading.
		*  @param data is a pointer to the read data.
		*  @return Result of the FAST_READ command (if success it will be 0).
		*/
		LONG FAST_READ(BYTE startPage, BYTE endPage, BYTE* data);

		/** @brief Sends a Write command with the content of the variable 'data'.
		*
		*  Sends a CardTransmit write command.
		*
		*  @param page establish the desired page for writing.
		*  @param data is a pointer to the data to be written.
		*  @return Result of the WRITE command (if success it will be 0).
		*/
		LONG WRITE(BYTE page, BYTE* data);

		/** @brief Sends a Fast Write command with the content of the variable 'data'.
		*
		*  Sends a CardTransmit fast write command.
		*
		*  @param startAddr Sets the first page for writing.
		*  @param endAddr Sets the last page for writing.
		*  @param data is a pointer to the data to be written.
		*  @return Result of the FAST_WRITE command (if success it will be 0).
		*/
		LONG FAST_WRITE(BYTE* data);

		/** @brief Establishes a connection mode (DIRECT, SHARED, EXCLUSIVE).
		*
		*  @param mode establish the desired transmition mode (DIRECT, SHARED, EXCLUSIVE).
		*  @param pAP is a pointer to set the PCI configuration.
		*  @return Result of the card connect and set PCI config commands (if success it will be 0).
		*/
		long establishConnection(int mode, DWORD* pAP);

		/** @brief Frees the memory reserved for PCI config and Card Handler.
		*
		*  @param lReturn Status of the current connection, if true then we will free the memory.
		*/
		void releaseConnection(long lReturn);

		/** @brief Calls the method 'isReaderConnected' with the sCardReader object.
		*
		*  @return Result of the isReaderConnected() call.
		*/
		bool isReaderConnected();

		/** @brief Calls the method 'checkIfTag' with the sCardReader object.
		*
		* @return Result of the checkIfTag() call.
		*/
		bool checkIfTag();

		/** @brief Calls the method 'readIdentivFWversion' with the sCardReader object.
		*
		*  @param IdentivReaderFWversion pointer to the FW version of the NTAG I2C IC.
		*  @return Result of the readIdentivFWversion call (if success it will be 0).
		*/
		long readIdentivFWversion(char* IdentivReaderFWversion);

		/** @brief This method is similar to the Reader's init() method.
		*
		*  @return Returns if the reader matches or not.
		*/
		bool readerInit();

		/** @brief Calls to the releaseContext() method of the sCardReader object.
		*
		*  @return Result of the releaseContext() call.
		*/
		long releaseContext();

	private:

		/** @brief We introduce a response from another method and we check if that response is correct.
		*
		*  @param response Response obtained from another method.
		*  @return Result is true if response equals 0.
		*/
		bool isReturnSuccess(LONG response);

		/** @brief Check if the length of both parameters is the same.
		*
		*  @param resp_length Length of the response.
		*  @param expected_length Length expected.
		*  @return Result of the comparison between both paramters.
		*/
		bool isResponseLengthAsExpected(DWORD resp_length, DWORD expected_length);

		/** @brief Gets the version of the current IC.
		*
		*  @param GVByte Stores the version of the tag.
		*  @param vrsn sets the version of the IC (NTAG_VERSION_1K or NTAG_VERSION_2K).
		*  @return Result of the get version command, if the GVByte doesn't correspond to any of the versions it will return an UNKNOWN CARD value.
		*/
		LONG getVersion(BYTE GVByte_6, BYTE GVByte_5, BYTE GVByte_4, BYTE* vrsn);

		/** @brief Sends a Read command and stores the result in the variable 'data'.
		*
		*  Sends a CardTransmit read command.
		*
		*  @param response is a pointer to the obtained response.
		*  @param swOffset offset that will be applied to the response array.
		*  @return Returns true if the response is different to certain values.
		*/
		bool checkStatusWordSuccess(BYTE * response, int swOffset);

		BYTE selectedSector;
	};
}
#endif