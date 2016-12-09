#include "stdafx.h"
#include "Password.h"

using namespace NTAG_I2C_Demo;

RF_Commands* my_rf;

		PASSWORD::PASSWORD(RF_Commands* rf_in)
		{
			my_rf = rf_in;
		}

		LONG PASSWORD::setAuthentication(System::String^ pass)
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

			lReturn = my_rf->PWD_AUTH(password_bytes);

			return lReturn;
		}

		LONG PASSWORD::setPassword(System::String^ pass)
		{
			BYTE password_bytes[4];
			LONG lReturn;

			//Set PWD
			if (pass == "SUN")
			{
				password_bytes[0] = 0xFF;
				password_bytes[1] = 0xFF;
				password_bytes[2] = 0xFF;
				password_bytes[3] = 0xFF;
				lReturn = my_rf->WRITE(PWD_PAGE, password_bytes);
			}
			else if (pass == "STAR")
			{
				password_bytes[0] = 0x55;
				password_bytes[1] = 0x55;
				password_bytes[2] = 0x55;
				password_bytes[3] = 0x55;
				lReturn = my_rf->WRITE(PWD_PAGE, password_bytes);
			}
			else if (pass == "MOON")
			{
				password_bytes[0] = 0xAA;
				password_bytes[1] = 0xAA;
				password_bytes[2] = 0xAA;
				password_bytes[3] = 0xAA;
				lReturn = my_rf->WRITE(PWD_PAGE, password_bytes);
			}
			else
			{
				return SCARD_STATE_UNKNOWN;
			}

			return lReturn;

		}

		VOID PASSWORD::lockTag()
		{
			BYTE auth0[4];
			BYTE access[4];
			BYTE pt_i2C[4];
			LONG lReturn;

			//Set ACCESS
			access[0] = SET_ACCESS;
			access[1] = 0x00;
			access[2] = 0x00;
			access[3] = 0x00;
			if (my_rf->WRITE(ACCESS_PAGE, access) == SCARD_S_SUCCESS)
			{
				lReturn = SCARD_S_SUCCESS;
			}

			//Set PT_I2C
			pt_i2C[0] = SET_PT_I2C;
			pt_i2C[1] = 0x00;
			pt_i2C[2] = 0x00;
			pt_i2C[3] = 0x00;
			if (my_rf->WRITE(PT_I2C_PAGE, pt_i2C) == SCARD_S_SUCCESS)
			{
				lReturn = SCARD_S_SUCCESS;
			}

			//Set AUTH0
			auth0[0] = 0x00;
			auth0[1] = 0x00;
			auth0[2] = 0x00;
			auth0[3] = SET_AUTH0;
			if (my_rf->WRITE(AUTH0_PAGE, auth0) == SCARD_S_SUCCESS)
			{
				lReturn = SCARD_S_SUCCESS;
			}

		}

		VOID PASSWORD::unlockTag()
		{
			BYTE auth0[4];
			BYTE password_bytes[4];
			BYTE access[4];
			BYTE pt_i2C[4];
			LONG lReturn;

			//Clean AUTH0
			auth0[0] = 0x00;
			auth0[1] = 0x00;
			auth0[2] = 0x00;
			auth0[3] = CLEAN_AUTH0;
			if (my_rf->WRITE(AUTH0_PAGE, auth0) == SCARD_S_SUCCESS)
			{
				lReturn = SCARD_S_SUCCESS;
			}

			//Clean password
			password_bytes[0] = 0xFF;
			password_bytes[1] = 0xFF;
			password_bytes[2] = 0xFF;
			password_bytes[3] = 0xFF;
			if (lReturn = my_rf->WRITE(PWD_PAGE, password_bytes) == SCARD_S_SUCCESS)
			{
				lReturn = SCARD_S_SUCCESS;
			}

			//Clean ACCESS
			access[0] = CLEAN_ACCESS;
			access[1] = 0x00;
			access[2] = 0x00;
			access[3] = 0x00;
			if (my_rf->WRITE(ACCESS_PAGE, access) == SCARD_S_SUCCESS)
			{
				lReturn = SCARD_S_SUCCESS;
			}

			//Clean PT_I2C
			pt_i2C[0] = CLEAN_PT_I2C;
			pt_i2C[1] = 0x00;
			pt_i2C[2] = 0x00;
			pt_i2C[3] = 0x00;
			if (my_rf->WRITE(PT_I2C_PAGE, pt_i2C) == SCARD_S_SUCCESS)
			{
				lReturn = SCARD_S_SUCCESS;
			}

		}


		BOOLEAN PASSWORD::checkBlocked()
		{
			BYTE auth0[4];
			BOOLEAN ret;

			//Read AUTH0
			if (my_rf->FAST_READ(AUTH0_PAGE, AUTH0_PAGE, auth0) == SCARD_S_SUCCESS)
			{
				if (auth0[3] > 0xEB)
				{
					ret = false;
				}
				else
				{
					ret = true;
				}
			}
			else
			{
				ret = true;
			}

			return ret;
		}