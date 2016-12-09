#ifndef SRAM_H
#define SRAM_H

#include <time.h>
#include <windows.h>
#include "Utils.h"
#include "crc32.h"
#include "RF_Commands.h"

namespace NTAG_I2C_Demo {

	///
	/// SRAM class will manage the SRAM operations, for instance
	/// read, write, speed test, etc.
	///
	class SRAM
	{
	public:
		SRAM(RF_Commands* rf_in);

		bool auth = false;
		bool blocked = false;
		std::string pass_sram;

		/** @brief Performs a typical SRAM communication.
		*
		*  First we will send a write command and later we will
		*  read the response.
		*
		*  @param cmd Command that will be written.
		*  @param resp Pointer that will store the response.
		*  @return Returns true if both communications are correct.
		*/
		long PerformSramCom(byte* cmd, byte* resp);

		/** @brief Reads the SRAM and stores the respond in the parameter 'data'.
		*
		*  First of all we need to get the version of the product.
		*  Then, depending on the version we will select sector 0 or 1.
		*  Finally we will do a FAST_READ command.
		*
		*  @param data Data read.
		*  @return Result of the commands, if all are correct we will get success (0 value).
		*/
		long ReadSram(byte* data);

		/** @brief Writes the SRAM with the value of the parameter 'data'.
		*
		*  First of all we need to get the version of the product.
		*  Then, depending on the version we will select sector 0 or 1.
		*  Finally we will do a WRITE command.
		*
		*  @param data Data written.
		*  @return Result of the commands, if all are correct we will get success (0 value).
		*/
		long WriteSram(byte* data);

		/** @brief Speed test of the SRAM memory.
		*
		*  First we establish an exclusive connection and later we write data into the SRAM
		*  while a timer is running. Finally we calculate the value of the speed by taking into account
		*  the bytes written and the time taken.
		*
		*  @param chMultiplier Counter variable.
		*  @param polling Check if polling is required.
		*  @param integritySent Check if the microcontroller detected an error in the CRC.
		*  @param integrityRecv Check if the CRC values in reception are valid.
		*  @param writeTime Time needed to write the data.
		*  @param readTime Time needed to read the data.
		*  @return SRAM speed test result (if success it will be 0).
		*/
		long SRAMSpeedTest(int chMultiplier, bool polling, bool* integritySent, bool* integrityRecv, float* writeTime, float* readTime);

		/** @brief Checks if the write command indicated in 'cmd' is successful.
		*
		*  @param cmd Write command.
		*  @param lReturn Return of write command.
		*/
		void checkIfSuccess(BYTE* cmd, long lReturn);
	};
}
#endif