#include "stdafx.h"
#include "NTAG_I2C_Logic.h"
#include "Reader.h"
#include "BoardDemo.h"

using namespace NTAG_I2C_Demo;

VOID NTAG_I2C_Logic::Init(){
	BoardDemo* demo = new BoardDemo();
	demo->initialize();
}



