#ifndef NTAG_I2C_Connection_H
#define NTAG_I2C_Connection_H

#include "RF_Commands.h"
#include "NTAG_I2C_Glossary.h"

namespace NTAG_I2C_Demo {

	class NTAG_I2C_Connection
	{
	public:

		RF_Commands* rf_commands;

		//Constructors
		NTAG_I2C_Connection();

	//	long establishConnection(int mode, DWORD* pAP);				//COMMENTED TO CONTROL DEPENDENCIES
	//	void releaseConnection(long lReturn);

	};
}
#endif