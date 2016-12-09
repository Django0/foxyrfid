#include "Utils.h"

// Waits for the microcontroller to read the content written in the SRAM
LONG Utils::WaitForI2CRead()
{
	// The reader can check if the microcontroller has finished reading by checking the bit SRAM_I2C_READY
	// As soon as the microcontroller finishes reading the SRAM the bit SRAM_I2C_READY is set to 1
	// The bit SRAM_I2C_READY is part of the session registers, located in sector 3
	// In order to avoid using the Sector Select commands, this has been implemented with timers
	System::Threading::Thread::Sleep(100);

	return SCARD_S_SUCCESS;
}

// Waits for the microcontroller to write content into the SRAM
LONG Utils::WaitForI2CWrite()
{
	// The reader can check if the microcontroller has finished reading by checking the bit SRAM_RF_READY
	// As soon as the microcontroller finishes reading the SRAM the bit SRAM_RF_READY is set to 0
	// The bit SRAM_RF_READY is part of the session registers, located in sector 3
	// In order to avoid using the Sector Select commands, this has been implemented with timers
	System::Threading::Thread::Sleep(100);

	return SCARD_S_SUCCESS;
}

// Waits for the Passthrough mode to be activated
LONG Utils::WaitForPassthroughActive()
{
	// The reader can check if the Passthrough mode has been activated reading by checking the bit PTHRU_ON_OFF
	// As soon as the Passthrough mode is activated the bit PTHRU_ON_OFF is set to 1
	// The bit PTHRU_ON_OFF is part of the session registers, located in sector 3
	// In order to avoid using the Sector Select commands, this has been implemented with timers
	System::Threading::Thread::Sleep(20);

	return SCARD_S_SUCCESS;
}