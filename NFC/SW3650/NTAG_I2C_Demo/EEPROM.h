#ifndef EEPROM_H
#define EEPROM_H

#include <Windows.h>
#include "Utils.h"
#include "SRAM.h"
#include "RF_Commands.h"
#include "NDEFmsg.h"
#include "Registers.h"

namespace NTAG_I2C_Demo
{
	///
	/// This class will do all the EEPROM related transactions.
	///
	class EEPROM
	{
	public:

		//Constructor
		EEPROM(RF_Commands* rf_in);

		bool auth = false;
		bool blocked = false;
		std::string pass_eeprom;

		/** @brief Read the EEPROM memory.
		*
		*  Gets version of the product, later we start a time counter and
		*  execute a readMem command, this readMem method will execute a FAST_READ
		*  inside a loop until we read all the EEPROM memory.
		*
		*  @param data BYTES that will be read in the FAST_READ command.
		*  @param readBytes BYTES multiple of 4 read.
		*  @param readTime Time taken to execute this read EEPROM command.
		*  @return Read EEPROM result (if success it will be 0).
		*/
		long Read(BYTE* data, DWORD* readBytes, float* readTime);

		/** @brief Resets the EEPROM memory.
		*
		*  First of all we establish a connection in exclusive mode, then
		*  we execute a GET_VERSION command and we call the resetMem method,
		*  this method will check static lock bytes and call checkStaticLockBytes
		*  and checkDynLockBytes method, later we execute the Write method in the
		*  writeCapabilityContainer method that will write the capability containers in the
		*  apropriate page of the memory. Finally we execute a WRITE command in order to write 0's in
		*  all memory positions.
		*
		*  @param resetBytes BYTES that will be read in the FAST_READ command.
		*  @param resetTime Time taken to execute this reset EEPROM command.
		*  @return Reset EEPROM result (if success it will be 0).
		*/
		long ResetMemory(DWORD* resetBytes, float* resetTime);

		/** @brief Speed test of the EEPROM memory.
		*
		*  We start by establishing an exclusive connection, later we get the version and
		*  run the speed test by calling speedTest method. This method will check the NDEF header (long NDEF), the
		*  NDEF message and check if the message fits in the NTAG memory, if the message fits we execute the
		*  write test and the read test.
		*
		*  @param chMultiplier Counter variable.
		*  @param text Text created in order to run the test.
		*  @param nWrittenBytes NDEF message written bytes.
		*  @param writeTime Time taken to execute this write test EEPROM command.
		*  @param nReadBytes NDEF message read bytes.
		*  @param readTime Time taken to execute this read test EEPROM command.
		*  @return EEPROM speed test result (if success it will be 0).
		*/
		long EEPROMSpeedTest(int chMultiplier, BYTE* text, int* nWrittenBytes, float* writeTime, int* nReadBytes, float* readTime);


	private:
		int getMemSize(BYTE NtagVersion);
		void speedTest(int* nWrittenBytes, float* writeTime, int* nReadBytes, float* readTime, long lReturn, int ndefMessageSize, int memSize, BYTE* text, int chMultiplier);
		void readMem(int fetch_start, long lReturn, int memSize, BYTE* data, DWORD* readBytes);
		int checkMemSize(BYTE NtagVersion, DWORD* resetBytes);
		BYTE Write(LONG lReturn, BYTE* rPage, BYTE* wPage, float* resetTime, BYTE* message, int length, int memSize, BYTE NtagVersion);
		void writeCapabilityContainer(BYTE* wPage, BYTE NtagVersion, LONG lReturn, BYTE* rPage, float* resetTime, BYTE* message, int length, int memSize);
		void checkDynLockBytes(LONG lReturn, BYTE* rPage, BYTE* wPage, BYTE NtagVersion, float* resetTime, BYTE* message, int length, int memSize);
		void checkStaticLockBytes(LONG lReturn, BYTE* rPage, BYTE* wPage, BYTE NtagVersion, float* resetTime, BYTE* message, int length, int memSize);
		void resetMem(LONG lReturn, BYTE* rPage, BYTE* wPage, BYTE NtagVersion, float* resetTime, BYTE* message, int length, int memSize);
		bool isReturnSuccess(LONG response);

	};

}
#endif