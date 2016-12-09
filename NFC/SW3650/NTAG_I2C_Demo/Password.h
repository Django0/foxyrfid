#ifndef PASSWORD_H
#define PASSWORD_H

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
	class PASSWORD
	{
	public:

		//Constructor
		PASSWORD(RF_Commands* rf_in);
		
		/** @brief Read the EEPROM memory.
		*
		*  Sends a PWD_AUTH command with the selected password
		*
		*  @param pass String which will contain the password selected.
		*  @return setAuthentication result (if success it will be 0).
		*/
		LONG setAuthentication(System::String^ pass);

		/** @brief Writes the password in the PWD register.
		*
		*  Writes the password in the PWD register in memory.
		*
		*  @param pass string containing the password selected.
		*  @return setPassword result (if success it will be 0).
		*/
		LONG setPassword(System::String^ pass);

		/** @brief Blocks the tag
		*
		*  Sets the registers AUTH0, ACCESS and PT_I2C to the apropriate values for blocking the tag.
		*
		*  @return Void result
		*/
		VOID lockTag();

		/** @brief Unlocks the tag
		*
		*  Sets the registers AUTH0, ACCESS and PT_I2C to the apropriate values for unblocking the tag.
		*
		*  @return Void result
		*/
		VOID unlockTag();
		
		/** @brief Checks if the tag is locked
		*
		*  Tries to read without authentication the AUTH0 register, if this registers cannot be read it means the tag is blocked.
		*
		*  @return True if the tag is locked.
		*/
		BOOLEAN checkBlocked();

	};

}
#endif