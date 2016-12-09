#include "stdafx.h"
#include "NTAG_I2C_API.h"

using namespace System;

using namespace NTAG_I2C_Demo;

		NTAG_I2C_API::NTAG_I2C_API()
		{
			my_rf = new RF_Commands();
			eeprom = new EEPROM(my_rf);
			sram = new SRAM(my_rf);
			registers = new Registers(my_rf);
			ndef = new NDEFmsg(my_rf);
			password = new PASSWORD(my_rf);
		}
		
		//Inherited Methods

		bool NTAG_I2C_API::isReaderConnected(){
			return my_rf->isReaderConnected();
		}

		long NTAG_I2C_API::readIdentivFWversion(char* IdentivReaderFWversion){
			return my_rf->readIdentivFWversion(IdentivReaderFWversion);
		}
		
		/*bool NTAG_I2C_API::checkIfTag(){
			return my_rf->checkIfTag();
		}*/

		long NTAG_I2C_API::establishConnection(int mode, DWORD* pAP){		//Mode: 1=DIRECT; 2=SHARED; 3=EXCLUSIVE
			return my_rf->establishConnection(mode, pAP);
		}

		void NTAG_I2C_API::releaseConnection(long lReturn){
			my_rf->releaseConnection(lReturn);
		}

		bool NTAG_I2C_API::releaseContext(){
			bool res = false;
			res = my_rf->releaseContext();
			return res;
		}

		bool NTAG_I2C_API::readerInit(){
			bool res = false;

			res = my_rf->readerInit();

			return res;
		}

		//Get version:
		BYTE NTAG_I2C_API::GetVersion()
		{
			LONG lReturn;
			BYTE version;
			lReturn = my_rf->GET_VERSION(&version);
			return version;
		}

		//NDEF Methods:

		LONG NTAG_I2C_API::ReadNdef(int* NdefType, BYTE* payload, int* payloadSize, BOOL *AARPresent, BYTE* AAR, int*AARSize, DWORD* readBytes, float* readTime){
			return ndef->ReadNdef(NdefType, payload, payloadSize, AARPresent, AAR, AARSize, readBytes, readTime);
		}
		
		LONG NTAG_I2C_API::WriteNdef(int NdefType, BYTE* payload, int payloadSize, BOOL addAAR, DWORD* writeBytes, float* writeTime){
			return ndef->WriteNdef(NdefType, payload, payloadSize, addAAR, writeBytes, writeTime);
		}
		
		LONG NTAG_I2C_API::ReadNdefMessage(BYTE* data, int* length){
			return ndef->ReadNdefMessage(data, length);
		}
		
		LONG NTAG_I2C_API::WriteNdefMessage(BYTE* data, int length){
			return ndef->WriteNdefMessage(data, length);
		}

		int NTAG_I2C_API::numberBytes2Write(int payloadSize){
			return ndef->numberBytes2Write(payloadSize);
		}

		//EEPROM Methods:

		LONG NTAG_I2C_API::Read_EEPROM(BYTE* data, DWORD* readBytes, float* readTime){
			return eeprom->Read(data, readBytes, readTime);
		}

		LONG NTAG_I2C_API::ResetEEPROMMemory(DWORD* resetBytes, float* resetTime){
			return eeprom->ResetMemory(resetBytes, resetTime);
		}

		LONG NTAG_I2C_API::EEPROMSpeedTest(int chMultiplier, BYTE* text, int* nWrittenBytes, float* writeTime, int* nReadBytes, float* readTime){
			return eeprom->EEPROMSpeedTest(chMultiplier, text, nWrittenBytes, writeTime, nReadBytes, readTime);
		}

		//SRAM Methods:

		LONG NTAG_I2C_API::Read_SRAM(BYTE* data){
			return sram->ReadSram(data);
		}
						
		LONG NTAG_I2C_API::Write_SRAM(BYTE* data){
			return sram->WriteSram(data);
		}

		LONG NTAG_I2C_API::PerformSRAMCom(BYTE*cmd, BYTE* resp){
			return sram->PerformSramCom(cmd, resp);
		}

		LONG NTAG_I2C_API::SRAMSpeedTest(int chMultiplier, bool polling, bool* integritySent, bool* integrityRecv, float* writeTime, float* readTime){
			return sram->SRAMSpeedTest(chMultiplier, polling, integritySent, integrityRecv, writeTime, readTime);
		}

		//Registers Methods:

		LONG NTAG_I2C_API::ReadSessionRegisters(Ntag_I2C_Registers_t* sessionReg){
			return registers->ReadSessionRegisters(sessionReg);
		}

		LONG NTAG_I2C_API::ReadConfigRegisters(Ntag_I2C_Registers_t* sessionReg){
			return registers->ReadConfigRegisters(sessionReg);
		}
		
		LONG NTAG_I2C_API::WriteConfigRegisters(Ntag_I2C_Registers_t sessionReg){
			return registers->WriteConfigRegisters(sessionReg);
		}

		LONG NTAG_I2C_API::ReadAccessRegisters(Ntag_I2C_Access_Registers_t* accessReg){
			return registers->ReadAccessRegisters(accessReg);
		}

		LONG NTAG_I2C_API::WriteAccessRegisters(Ntag_I2C_Access_Registers_t accessReg){
			return registers->WriteAccessRegisters(accessReg);
		}

		//Password Methods:

		LONG NTAG_I2C_API::setAuthentication(System::String^ pass)
		{
			return password->setAuthentication(pass);
			
		}

		LONG NTAG_I2C_API::setPassword(System::String^ pass)
		{
			return password->setPassword(pass);
			
		}

		VOID NTAG_I2C_API::lockTag()
		{
			password->lockTag();
			
		}

		VOID NTAG_I2C_API::unlockTag()
		{
			password->unlockTag();
			
		}


		BOOLEAN NTAG_I2C_API::checkBlocked()
		{
			return password->checkBlocked();
			
		}