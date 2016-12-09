#ifndef NTAG_I2C_API_H
#define NTAG_I2C_API_H
#include "EEPROM.h"
#include "SRAM.h"
#include "Registers.h"
#include "NDEFmsg.h"
#include "Password.h"

namespace NTAG_I2C_Demo
{
	///
	/// This NTAG_I2C_API class will contain the API part of the app,
	/// this will call to all the lower layers methods like sram, eeprom, etc.
	///
	class NTAG_I2C_API
	{
	public:

		EEPROM* eeprom; /**< This atribute will be a pointer to an EEPROM object. */
		SRAM* sram; /**< This atribute will be a pointer to a SRAM object. */
		Registers* registers; /**< This atribute will be a pointer to a Registers object. */
		RF_Commands* my_rf; /**< This atribute will be a pointer to a RF_Commands object. */
		NDEFmsg* ndef; /**< This atribute will be a pointer to a NDEFmsg object. */
		PASSWORD* password; /**< This atribute will be a pointer to a PASSWORD object. */

		//Constructor
		NTAG_I2C_API();

		//Inherited Methods
		bool isReaderConnected();
		long readIdentivFWversion(char* IdentivReaderFWversion);
		bool checkIfTag();
		long establishConnection(int mode, DWORD* pAP);
		void releaseConnection(long lReturn);
		bool readerInit();
		bool releaseContext();

		//RF COMMANDS
		/** @brief This method will retrieve the version of the tag connected.
		*
		*  @return If success it return 0.
		*/
		BYTE GetVersion();

		//NDEF Methods

		/** @brief This method just calls the ReadNDEF method of the ndef object.
		*
		*  @return ReadNdef result (if success it will be 0).
		*/
		LONG ReadNdef(int* NdefType, BYTE* payload, int* payloadSize, BOOL *AARPresent, BYTE* AAR, int*AARSize, DWORD* readBytes, float* readTime);

		/** @brief This method just calls the WriteNdef method of the ndef object.
		*
		*  @return WriteNdef result (if success it will be 0).
		*/
		LONG WriteNdef(int NdefType, BYTE* payload, int payloadSize, BOOL addAAR, DWORD* writeBytes, float* writeTime);

		/** @brief This method just calls the ReadNdefMessage method of the ndef object.
		*
		*  @return ReadNdefMessage result (if success it will be 0).
		*/
		LONG ReadNdefMessage(BYTE* data, int* length);

		/** @brief This method just calls the WriteNdefMessage method of the ndef object.
		*
		*  @return WriteNdefMessage result (if success it will be 0).
		*/
		LONG WriteNdefMessage(BYTE* data, int length);
		int numberBytes2Write(int payloadSize);

		//EEPROM Methods

		/** @brief This method just calls the Read_EEPROM method of the eeprom object.
		*
		*  @return Read_EEPROM result (if success it will be 0).
		*/
		LONG Read_EEPROM(BYTE* data, DWORD* readBytes, float* readTime);

		/** @brief This method just calls the ResetEEPROMMemory method of the eeprom object.
		*
		*  @return ResetEEPROMMemory result (if success it will be 0).
		*/
		LONG ResetEEPROMMemory(DWORD* resetBytes, float* resetTime);

		/** @brief This method just calls the EEPROMSpeedTest method of the eeprom object.
		*
		*  @return EEPROMSpeedTest result (if success it will be 0).
		*/
		LONG EEPROMSpeedTest(int chMultiplier, BYTE* text, int* nWrittenBytes, float* writeTime, int* nReadBytes, float* readTime);

		//SRAM Methods

		/** @brief This method just calls the Read_SRAM method of the sram object.
		*
		*  @return Read_SRAM result (if success it will be 0).
		*/
		LONG Read_SRAM(BYTE* data);

		/** @brief This method just calls the Write_SRAM method of the sram object.
		*
		*  @return Write_SRAM result (if success it will be 0).
		*/
		LONG Write_SRAM(BYTE* data);

		/** @brief This method just calls the FlashMemory method of the sram object.
		*
		*  This method will reserve memory for the reader
		*  and will establish the context.
		*
		*  @return FlashMemory result (if success it will be 0).
		*/
		LONG FlashMemory(BYTE* newFW, int newFWLength, DWORD* flashBytes, float* flashTime);

		/** @brief This method just calls the PerformSRAMCom method of the sram object.
		*
		*  This method will reserve memory for the reader
		*  and will establish the context.
		*
		*  @return PerformSRAMCom result (if success it will be 0).
		*/
		LONG PerformSRAMCom(BYTE*cmd, BYTE* resp);

		/** @brief This method just calls the SRAMSpeedTest method of the sram object.
		*
		*  This method will reserve memory for the reader
		*  and will establish the context.
		*
		*  @return SRAMSpeedTest result (if success it will be 0).
		*/
		LONG SRAMSpeedTest(int chMultiplier, bool polling, bool* integritySent, bool* integrityRecv, float* writeTime, float* readTime);

		//Registers Methods

		/** @brief This method just calls the ReadSessionRegisters method of the registers object.
		*
		*  @return ReadSessionRegisters result (if success it will be 0).
		*/
		LONG ReadSessionRegisters(Ntag_I2C_Registers_t* sessionReg);

		/** @brief This method just calls the ReadConfigRegisters method of the registers object.
		*
		*  @return ReadConfigRegisters result (if success it will be 0).
		*/
		LONG ReadConfigRegisters(Ntag_I2C_Registers_t* sessionReg);

		/** @brief This method just calls the WriteConfigRegisters method of the registers object.
		*
		*  @return WriteConfigRegisters result (if success it will be 0).
		*/
		LONG WriteConfigRegisters(Ntag_I2C_Registers_t sessionReg);

		/** @brief This method just calls the ReadAccessRegisters method of the registers object.
		*
		*  @return ReadAccessRegisters result (if success it will be 0).
		*/
		LONG ReadAccessRegisters(Ntag_I2C_Access_Registers_t* accessReg);

		/** @brief This method just calls the WriteAccessRegisters method of the registers object.
		*
		*  @return WriteAccessRegisters result (if success it will be 0).
		*/
		LONG WriteAccessRegisters(Ntag_I2C_Access_Registers_t accessReg);

		//PASSWORD
		/** @brief This method send the password to the memory in order to set it.
		*
		*  @return setPassword result (if success it will be SCARD_SUCESS).
		*/
		LONG NTAG_I2C_API::setPassword(System::String^ pass);

		/** @brief This method implements the authentication.
		*
		*  @return setAuthentication result (if success it will be SCARD_SUCESS).
		*/
		LONG NTAG_I2C_API::setAuthentication(System::String^ pass);

		/** @brief This method sets the parameters of the password and consequently locks the tag.
		*
		*  @return lockTag result (if success it will be SCARD_SUCESS).
		*/
		VOID NTAG_I2C_API::lockTag();

		/** @brief This method unlocks the tag.
		*
		*  @return unlockTag result (if success it will be SCARD_SUCESS).
		*/
		VOID NTAG_I2C_API::unlockTag();

		/** @brief Checks if AUTH0 is locking the tag
		*
		*  @return checkBlocked returns a boolean, if the tag is blocked = true, if not = false.
		*/
		BOOLEAN NTAG_I2C_API::checkBlocked();
	};
}
#endif