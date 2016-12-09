#include "SRAM.h"
#include "stdafx.h"

using namespace NTAG_I2C_Demo;

RF_Commands* rf_cm;

SRAM::SRAM(RF_Commands* rf_in)
{
	rf_cm = rf_in;
}

LONG setAuthentication(std::string pass)
{
	LONG lReturn;
	BYTE password_bytes[4];

	if (pass == "SUN")
	{
		password_bytes[0] = 0xFF;
		password_bytes[1] = 0xFF;
		password_bytes[2] = 0xFF;
		password_bytes[3] = 0xFF;
	}
	else if (pass == "STAR")
	{
		password_bytes[0] = 0x55;
		password_bytes[1] = 0x55;
		password_bytes[2] = 0x55;
		password_bytes[3] = 0x55;
	}
	else if (pass == "MOON")
	{
		password_bytes[0] = 0xAA;
		password_bytes[1] = 0xAA;
		password_bytes[2] = 0xAA;
		password_bytes[3] = 0xAA;
	}

	lReturn = rf_cm->PWD_AUTH(password_bytes);

	return lReturn;
}

// Performs a cycle of writing into the SRAM, waiting for the microcontroller to read it and to respond, and reading the response
long SRAM::PerformSramCom(BYTE* cmd, BYTE* resp)
{
	long lReturn;

	//Check if the lock is not red
	if (((!this->auth) && (!this->blocked)) || ((this->auth) && (this->blocked)))
	{
		if (this->auth) // If the tag is authenticated I need to authenticate each time after performing FAST_WRITE or WRITE
		{
			setAuthentication(this->pass_sram);
		}

		// Send Fast Write SRAM command
		lReturn = WriteSram(cmd);
		if (lReturn == SCARD_S_SUCCESS)
		{
			// Wait for I2C Read
			lReturn = Utils::WaitForI2CRead();
			if (lReturn == SCARD_S_SUCCESS)
			{
				// Wait for I2C Write
				lReturn = Utils::WaitForI2CWrite();
				if (lReturn == SCARD_S_SUCCESS)
				{
					if (this->auth) // If the tag is authenticated I need to authenticate each time after performing FAST_WRITE or WRITE
					{
						setAuthentication(this->pass_sram);
					}
					// Fast Read SRAM response
					lReturn = ReadSram(resp);
				}
			}
		}
	}
	return lReturn;
}

void SRAM::checkIfSuccess(BYTE* cmd, long lReturn)
{
	if (lReturn == SCARD_S_SUCCESS)
	{
		// If the writting has been ccompleted successfully, we indicate it to the board
		memset(cmd, 0, NTAG_MEM_SIZE_SRAM);
		cmd[60] = 'F';
		cmd[61] = 'S';
		lReturn = WriteSram(cmd);
		//if (this->auth)	setAuthentication(this->pass_sram);
		if (lReturn == SCARD_S_SUCCESS)
			lReturn = Utils::WaitForI2CRead();
	}
	else
	{
		// If the writting has not been completed successfully, we indicate it to the board (we don't update lReturn)
		memset(cmd, 0, NTAG_MEM_SIZE_SRAM);
		cmd[60] = 'F';
		cmd[61] = 'F';
		WriteSram(cmd);
		if (this->auth)	setAuthentication(this->pass_sram);
		Utils::WaitForI2CRead();
	}
}

void selectSector0(BYTE NtagVersion, BYTE* data, long* lReturn)
{
	*lReturn = rf_cm->SECTOR_SELECT(0);
	if (*lReturn == SCARD_S_SUCCESS)
	{	
		*lReturn = rf_cm->FAST_READ(SRAM_Begin, SRAM_Finish, data);
	}
	if (NtagVersion == NTAG_VERSION_2K)
		rf_cm->END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
}

void selectSector1(BYTE NtagVersion, BYTE* data, long* lReturn)
{
	*lReturn = rf_cm->SECTOR_SELECT(1);
	if (*lReturn == SCARD_S_SUCCESS)
		*lReturn = rf_cm->FAST_READ(SRAM_Begin, SRAM_Finish, data);
	if (NtagVersion == NTAG_VERSION_2K)
		rf_cm->END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
}

// Reads the SRAM and stores the result in the variable data
long SRAM::ReadSram(BYTE* data)
{
	long lReturn;

	// In Pass-through mode, the SRAM may be mirrored to sector 0 or sector 1 (depending on the NTAG version)
	BYTE NtagVersion;
	lReturn = rf_cm->GET_VERSION(&NtagVersion);
	if (lReturn == SCARD_S_SUCCESS)
	{
		if (NtagVersion == NTAG_VERSION_1K)
			selectSector0(NtagVersion, data, &lReturn);
		else if (NtagVersion == NTAG_VERSION_2K)
			selectSector1(NtagVersion, data, &lReturn);
		else if ((NtagVersion == NTAG_VERSION_1K_PLUS) || (NtagVersion == NTAG_VERSION_2K_PLUS))
			selectSector0(NtagVersion, data, &lReturn);
	}

	return lReturn;
}

long ReadSramTest(BYTE* data)
{
	long lReturn;

	// In Pass-through mode, the SRAM may be mirrored to sector 0 or sector 1 (depending on the NTAG version)
	BYTE NtagVersion;
	lReturn = rf_cm->GET_VERSION(&NtagVersion);
	if (lReturn == SCARD_S_SUCCESS)
	{
		if (NtagVersion == NTAG_VERSION_1K)
			selectSector0(NtagVersion, data, &lReturn);
		else if (NtagVersion == NTAG_VERSION_2K)
			selectSector1(NtagVersion, data, &lReturn);
		else if ((NtagVersion == NTAG_VERSION_1K_PLUS) || (NtagVersion == NTAG_VERSION_2K_PLUS))
			selectSector0(NtagVersion, data, &lReturn);
	}

	return lReturn;
}

void write1K(BYTE NtagVersion, BYTE* data, BYTE* page, long* lReturn)
{
	if (NtagVersion != NTAG_VERSION_2K)
		*lReturn = rf_cm->SECTOR_SELECT(0);
	if (*lReturn == SCARD_S_SUCCESS)
	{
			// The 64-bytes SRAM Blocks are mapped in 16 pages
			int i = 0;
			do
			{
				page[0] = data[(i * 4) + 0];
				page[1] = data[(i * 4) + 1];
				page[2] = data[(i * 4) + 2];
				page[3] = data[(i * 4) + 3];
				*lReturn = rf_cm->WRITE(SRAM_Begin + i, page);
				i++;
			} while (i < 16 && *lReturn == SCARD_S_SUCCESS);
	}
	if (NtagVersion == NTAG_VERSION_2K)
		rf_cm->END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed

}

void write2K(BYTE NtagVersion, BYTE* data, BYTE* page, long* lReturn)
{
	if (NtagVersion != NTAG_VERSION_1K)
		*lReturn = rf_cm->SECTOR_SELECT(1);
	if (*lReturn == SCARD_S_SUCCESS)
	{
		// The 64-bytes SRAM Blocks are mapped in 16 pages
		int i = 0;
		do
		{
			page[0] = data[(i * 4) + 0];
			page[1] = data[(i * 4) + 1];
			page[2] = data[(i * 4) + 2];
			page[3] = data[(i * 4) + 3];
			*lReturn = rf_cm->WRITE(SRAM_Begin + i, page);
			i++;
		} while (i < 16 && *lReturn == SCARD_S_SUCCESS);
	}
	if (NtagVersion == NTAG_VERSION_2K)
		rf_cm->END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
}

void write_Plus(BYTE NtagVersion, BYTE* data, long* lReturn)
{
	if ((NtagVersion == NTAG_VERSION_1K_PLUS) || (NtagVersion == NTAG_VERSION_2K_PLUS))
		*lReturn = rf_cm->SECTOR_SELECT(0);
	if (*lReturn == SCARD_S_SUCCESS)
	{
		*lReturn = rf_cm->FAST_WRITE(data); // NTAG I²C plus supports FAST_WRITE
	}
	if ((NtagVersion == NTAG_VERSION_1K_PLUS) || (NtagVersion == NTAG_VERSION_2K_PLUS))
		rf_cm->END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
}

// Writes the SRAM with the content of the variable data
long SRAM::WriteSram(BYTE* data)
{
	long lReturn;
	BYTE page[4];
	
	// In Pass-through mode, the SRAM may be mirrored to sector 0 or sector 1
	BYTE NtagVersion;
	lReturn = rf_cm->GET_VERSION(&NtagVersion);
	if (lReturn == SCARD_S_SUCCESS)
	{
		if (NtagVersion == NTAG_VERSION_1K)
			write1K(NtagVersion, data, page, &lReturn);
		else if (NtagVersion == NTAG_VERSION_2K)
			write2K(NtagVersion, data, page, &lReturn);
		else if ((NtagVersion == NTAG_VERSION_1K_PLUS) || (NtagVersion == NTAG_VERSION_2K_PLUS))
		{	
			write_Plus(NtagVersion, data, &lReturn);
		}
	}

	return lReturn;
}

// Performs a test on the speed for writing and reading from the SRAM
long SRAM::SRAMSpeedTest(int chMultiplier, bool polling, bool* integritySent, bool* integrityRecv, float* writeTime, float* readTime)
{
	long lReturn;
	BYTE dataBlock[NTAG_MEM_SIZE_SRAM] = { 0 };

	// During the SRAM test we write 64 bytes in the memory space dedicated for it
	// S: reference for the SpeedTest
	dataBlock[60] = 'S';
	lReturn = WriteSram(dataBlock);
	if (this->auth)	setAuthentication(this->pass_sram);
	if (lReturn == SCARD_S_SUCCESS)
	{
		// if the Passthrough mode was not activated, wait for it to be activated
		lReturn = Utils::WaitForPassthroughActive();
		if (lReturn == SCARD_S_SUCCESS)
		{
			dataBlock[60] = 0;
			// Initialize the seed for the CRC32 calculation
			uint32_t seed = 0xFFFFFFFF;
			uint32_t crcTx = 0;

			// Execute write test
			*writeTime = (float)clock();
			int i = chMultiplier;
			while (i > 0 && lReturn == SCARD_S_SUCCESS)
			{
				// The last block contains the "finish_S_" string to notify the LPC board about the message transmission completion
				if (i == 1)
				{
					memcpy(dataBlock, "finish_S_", 9);

					// Update content for the CRC32 calculation (last 4 bytes are the CRC32)
					crcTx = crc32(seed, dataBlock, NTAG_MEM_SIZE_SRAM - 4);

					// Append the CRC32 to the block as this is the last block to be transmitted
					dataBlock[60] = (crcTx >> 0) & 0xFF;
					dataBlock[61] = (crcTx >> 8) & 0xFF;
					dataBlock[62] = (crcTx >> 16) & 0xFF;
					dataBlock[63] = (crcTx >> 24) & 0xFF;
				}
				else
				{
					// Update content for the CRC32 calculation
					crcTx = crc32(seed, dataBlock, NTAG_MEM_SIZE_SRAM);
					seed = crcTx;
				}

				// Write Data to SRAM
				lReturn = WriteSram(dataBlock);
				if (this->auth)	setAuthentication(this->pass_sram);
				if (lReturn == SCARD_S_SUCCESS)
				{
					// Check if polling is required
					if (polling == TRUE)
						lReturn = Utils::WaitForI2CRead();
					else
						Sleep(30);
				}

				i--;
			}

			*writeTime = (float)clock() - *writeTime;

			Sleep(10);
			
			// Reset the seed to its initial value for the CRC32 calculation
			seed = 0xFFFFFFFF;
			uint32_t crcRx = 0;

			// Execute read test
			*readTime = (float)clock();
			i = chMultiplier;
			while (i > 0 && lReturn == SCARD_S_SUCCESS)
			{
				// Check if polling is required
				if (polling == TRUE)
					lReturn = Utils::WaitForI2CWrite();
				else
					Sleep(30);
				if (lReturn == SCARD_S_SUCCESS)
				{
					// data is ready, read from SRAM
					lReturn = ReadSramTest(dataBlock);
					if (i > 1)
					{
						crcRx = crc32(seed, dataBlock, NTAG_MEM_SIZE_SRAM);
						seed = crcRx;
					}
					else
						crcRx = crc32(seed, dataBlock, NTAG_MEM_SIZE_SRAM - 4);
				}
				i--;
			}

			*readTime = (float)clock() - *readTime;
			if (lReturn == SCARD_S_SUCCESS)
			{
				// Get the CRC values in reception
				uint32_t crcReceived = dataBlock[NTAG_MEM_SIZE_SRAM - 1] << 24 | dataBlock[NTAG_MEM_SIZE_SRAM - 2] << 16 |
					dataBlock[NTAG_MEM_SIZE_SRAM - 3] << 8 | dataBlock[NTAG_MEM_SIZE_SRAM - 4];
				*integrityRecv = (crcReceived == crcRx);

				// Check if the microcontroller detected an error in the CRC
				*integritySent = dataBlock[59] == 0x01 ? FALSE : TRUE;
			}
		}
	}

	return lReturn;
};
