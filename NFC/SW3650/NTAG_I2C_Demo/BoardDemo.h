#ifndef BoardDemo_H
#define BoardDemo_H
#include "NTAG_I2C_API.h"

namespace NTAG_I2C_Demo
{

	// My LED color identifiers
	#define RED		1
	#define BLUE	2
	#define GREEN	3
	#define OFF     0

	typedef struct Versions
	{
		char	Board_Version[18];
		char	Board_FW_Version[18];
	}Versions_t;

	class BoardDemo
	{
	public:
		BYTE* prevTempC;
		BYTE* prevTempF;
		BYTE* prevVolt;
		NTAG_I2C_API *api;
		
		BoardDemo();
		VOID initialize();
		VOID destroy();
		LONG Run(char ledColor, BOOL enTemp, BOOL enLCD, BOOL dispNDEF, BOOL* redButton, BOOL* greenButton, BOOL* blueButton, float* tempC, float* tempF, float* voltage, float* version);
		LONG ReadVersions(Versions_t* versions);
	};

}

#endif