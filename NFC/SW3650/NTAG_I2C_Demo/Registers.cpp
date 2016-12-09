#include "Registers.h"
#include <string.h>

using namespace NTAG_I2C_Demo;

RF_Commands* rf_cmm;

//Constructors
Registers::Registers(RF_Commands *rf_in){
	rf_cmm = rf_in;
}

Registers::Registers(LPCTSTR readerIdentifierString){
	rf_cmm = new RF_Commands(readerIdentifierString);
}


LONG Registers::ReadSessionRegisters(Ntag_I2C_Registers_t* sessionReg)
{
	LONG lReturn;
	BYTE data[16];
	BYTE NtagVersion = 0;

	if (isGetVersionSuccess(&NtagVersion))
	{
		if ((NtagVersion == NTAG_VERSION_1K) || (NtagVersion == NTAG_VERSION_2K))
		{
			lReturn = rf_cmm->SECTOR_SELECT(SESSION_REGISTER_SECTOR);
			if (isReturnSuccess(lReturn)){
				lReturn = rf_cmm->READ(SessionPage, data);				// Read registers
				if (isReturnSuccess(lReturn)){
					parseRegisters(sessionReg, data);
				}
			}
			rf_cmm->END_SECTOR_SELECT();
		}
		else
		{
			lReturn = rf_cmm->SECTOR_SELECT(0);
			if (isReturnSuccess(lReturn)){
				lReturn = rf_cmm->READ(SessionPagePlus, data);				// Read registers
				if (isReturnSuccess(lReturn)){
					parseRegisters(sessionReg, data);
				}
			}
		}
	}
	return lReturn;
}


LONG Registers::ReadConfigRegisters(Ntag_I2C_Registers_t* configReg)
{
	LONG lReturn;

		lReturn = GetConfigRegisters(configReg);

	return lReturn;
}


LONG Registers::WriteConfigRegisters(Ntag_I2C_Registers_t configReg)
{
	LONG lReturn;

		lReturn = SetConfigRegisters(configReg);

	return lReturn;
};

LONG Registers::ReadAccessRegisters(Ntag_I2C_Access_Registers_t* accessReg)
{
	LONG lReturn;

	lReturn = GetAccessRegisters(accessReg);

	return lReturn;
};

LONG Registers::WriteAccessRegisters(Ntag_I2C_Access_Registers_t accessReg)
{
	LONG lReturn;

	lReturn = SetAccessRegisters(accessReg);

	return lReturn;
};

LONG Registers::SetConfigRegisters(Ntag_I2C_Registers_t configReg)
{
	LONG lReturn;
	BYTE data[4];

	// Get the bytes in the right form to be written into the tag
	// Registers Names as present in documentation (Table 11):
	BYTE NC_Reg = 0;				//	NC_REG		
	BYTE LD_Reg = 0;				//	LAST_NDEF_BLOCK
	BYTE SM_Reg = 0;				//	SRAM_MIRROR_BLOCK
	BYTE WD_LS_Reg = 0;				//	WDT_LS
	BYTE WD_MS_Reg = 0;				//  WDT_MS
	BYTE I2C_CLOCK_STR_Reg = 0;		//  I2C_CLOCK_STR
	BYTE NtagVersion;

	createConfigRegisters(configReg, &NC_Reg, &LD_Reg, &SM_Reg, &WD_LS_Reg, &WD_MS_Reg, &I2C_CLOCK_STR_Reg);

	// The Configuration Registers may be located in sector 0 or sector 1
	lReturn = rf_cmm->GET_VERSION(&NtagVersion);
	if (isReturnSuccess(lReturn)){
		if (NtagVersion == NTAG_VERSION_2K){
			lReturn = rf_cmm->SECTOR_SELECT(1);
		}
		data[0] = NC_Reg;
		data[1] = LD_Reg;
		data[2] = SM_Reg;
		data[3] = WD_LS_Reg;

		lReturn = rf_cmm->WRITE(ConfigurationPage, data);
		if (isReturnSuccess(lReturn))
		{
			data[0] = WD_MS_Reg;
			data[1] = I2C_CLOCK_STR_Reg;
			data[2] = REG_LOCK_ENABLE;			//REG_LOCK set to enable writing of the configuration files
			data[3] = FIXED_CONF_PAGE2_BYTE3;
			lReturn = rf_cmm->WRITE(ConfigurationPage2, data);
		}
		if (NtagVersion == NTAG_VERSION_2K)
			rf_cmm->END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SECTOR_SELECT Function has been executed
	}

	return lReturn;
}

LONG Registers::SetAccessRegisters(Ntag_I2C_Access_Registers_t accessReg)
{
	LONG lReturn;
	BYTE data[4];

	// Get the bytes in the right form to be written into the tag
	// Registers Names as present in documentation (Table 10):
	BYTE auth0 = 0;					//	Authentication (AUTH0)		
	BYTE access = 0;				//	Access Conditions (ACCESS)
	BYTE pt_i2c = 0;				//	Protection bits(PT_I2C)

	lReturn = createAccessRegisters(accessReg, &auth0, &access, &pt_i2c);

	if (lReturn == SCARD_S_SUCCESS)
	{
		data[0] = 0x00;
		data[1] = 0x00;
		data[2] = 0x00;
		data[3] = auth0;

		lReturn = rf_cmm->WRITE(AUTH0_Page, data);
		if (lReturn == SCARD_S_SUCCESS)
		{
			data[0] = access;
			data[1] = 0x00;
			data[2] = 0x00;
			data[3] = 0x00;
			lReturn = rf_cmm->WRITE(ACCESS_Page, data);
			if (lReturn == SCARD_S_SUCCESS)
			{
				data[0] = pt_i2c;
				data[1] = 0x00;
				data[2] = 0x00;
				data[3] = 0x00;
				lReturn = rf_cmm->WRITE(PT_I2C_Page, data);
			}
		}
	}
	return lReturn;
}

void Registers::parseRegisters(Ntag_I2C_Registers *regs, BYTE input[16])
{
	BYTE NtagVersion = 0;
	if (isGetVersionSuccess(&NtagVersion)){
		if (NtagVersion == NTAG_VERSION_1K) {
			memcpy(regs->REG_Manufacture, "NXP NTAG I2C 1K", strlen("NXP NTAG I2C 1K") + 1);
			regs->REG_Mem_size = NTAG_I2C_1k_MemSize;
		}
		else if (NtagVersion == NTAG_VERSION_2K) {
			memcpy(regs->REG_Manufacture, "NXP NTAG I2C 2K", strlen("NXP NTAG I2C 2K") + 1);
			regs->REG_Mem_size = NTAG_I2C_2k_MemSize;
		}
		else if (NtagVersion == NTAG_VERSION_1K_PLUS) {
			memcpy(regs->REG_Manufacture, "NXP NTAG I2C plus 1K", strlen("NXP NTAG I2C plus 1K") + 5);
			regs->REG_Mem_size = NTAG_I2C_PLUS_1k_MemSize;
		}
		else if (NtagVersion == NTAG_VERSION_2K_PLUS) {
			memcpy(regs->REG_Manufacture, "NXP NTAG I2C plus 2K", strlen("NXP NTAG I2C plus 2K") + 5);
			regs->REG_Mem_size = NTAG_I2C_PLUS_2k_MemSize;
		}
		else{
			memcpy(regs->REG_Manufacture, "", strlen("") + 1);
			regs->REG_Mem_size = 0;
		}
	}
	else{
		memcpy(regs->REG_Manufacture, "", strlen("") + 1);
		regs->REG_Mem_size = 0;
	}

	BYTE NC_Reg = input[NC_REG];

	// check I2C_RST_ON_OFF
	if ((NC_Reg & I2C_RST_ON_OFF) == I2C_RST_ON_OFF)
		regs->REG_I2C_RST_ON_OFF = TRUE;
	else
		regs->REG_I2C_RST_ON_OFF = FALSE;

	// check FD_OFF
	BYTE tmpReg = (NC_Reg & FD_OFF);
	if (tmpReg == (0x30))
		memcpy(regs->REG_FD_OFF, "11b", 3);
	if (tmpReg == (0x20))
		memcpy(regs->REG_FD_OFF, "10b", 3);
	if (tmpReg == (0x10))
		memcpy(regs->REG_FD_OFF, "01b", 3);
	if (tmpReg == (0x00))
		memcpy(regs->REG_FD_OFF, "00b", 3);;

	// check FD_ON
	tmpReg = (NC_Reg & FD_ON);
	if (tmpReg == (0x0c))
		memcpy(regs->REG_FD_ON, "11b", 3);
	if (tmpReg == (0x08))
		memcpy(regs->REG_FD_ON, "10b", 3);
	if (tmpReg == (0x04))
		memcpy(regs->REG_FD_ON, "01b", 3);
	if (tmpReg == (0x00))
		memcpy(regs->REG_FD_ON, "00b", 3);

	// Last NDEF Page
	regs->REG_LAST_NDEF_PAGE = (0x00000FF & input[LAST_NDEF_PAGE]);

	BYTE NS_Reg = input[NS_REG];

	// check NDEF_DATA_READ
	if ((NS_Reg & NDEF_DATA_READ) == NDEF_DATA_READ)
		regs->REG_NDEF_DATA_READ = TRUE;
	else
		regs->REG_NDEF_DATA_READ = FALSE;

	// check RF_FIELD
	if ((NS_Reg & RF_FIELD_PRESENT) == RF_FIELD_PRESENT)
		regs->REG_RF_FIELD_PRESENT = TRUE;
	else
		regs->REG_RF_FIELD_PRESENT = FALSE;

	// check PTHRU_ON_OFF
	if ((NC_Reg & PTHRU_ON_OFF) == PTHRU_ON_OFF)
		regs->REG_PTHRU_ON_OFF = TRUE;
	else
		regs->REG_PTHRU_ON_OFF = FALSE;

	// check I2C_LOCKED
	if ((NS_Reg & I2C_LOCKED) == I2C_LOCKED)
		regs->REG_I2C_LOCKED = TRUE;
	else
		regs->REG_I2C_LOCKED = FALSE;

	// check RF_LOCK
	if ((NS_Reg & RF_LOCKED) == RF_LOCKED)
		regs->REG_RF_LOCKED = TRUE;
	else
		regs->REG_RF_LOCKED = FALSE;

	// check check SRAM_I2C_Ready
	if ((NS_Reg & SRAM_I2C_READY) == SRAM_I2C_READY)
		regs->REG_SRAM_I2C_READY = TRUE;
	else
		regs->REG_SRAM_I2C_READY = FALSE;

	// check SRAM_RF_READY
	tmpReg = (BYTE)(NS_Reg & SRAM_RF_READY);
	if ((NS_Reg & SRAM_RF_READY) == SRAM_RF_READY)
		regs->REG_SRAM_RF_READY = TRUE;
	else
		regs->REG_SRAM_RF_READY = FALSE;

	// check SRAM_RF_READY
	tmpReg = (BYTE)(NS_Reg & EEPROM_WR_BUSY);
	if ((NS_Reg & EEPROM_WR_BUSY) == EEPROM_WR_BUSY)
		regs->REG_EEPROM_WR_BUSY = TRUE;
	else
		regs->REG_EEPROM_WR_BUSY = FALSE;

	// check PTHRU_DIR
	tmpReg = (BYTE)(NC_Reg & (BYTE)0x01);
	if (tmpReg == (0x01))
		regs->REG_PTHRU_DIR = TRUE;
	else
		regs->REG_PTHRU_DIR = FALSE;

	// SM_Reg
	regs->REG_SM_Reg = (0x00000FF & input[SM_REG]);

	// WD_LS_Reg
	regs->REG_WD_LS_Reg = (0x00000FF & input[WDT_LS]);

	// WD_MS_Reg
	regs->REG_WD_MS_Reg = (0x00000FF & input[WDT_MS]);

	// check SRAM_MIRROR_ON_OFF
	if ((NC_Reg & SRAM_MIRROR_ON_OFF) == SRAM_MIRROR_ON_OFF)
		regs->REG_SRAM_MIRROR_ON_OFF = TRUE;
	else
		regs->REG_SRAM_MIRROR_ON_OFF = FALSE;

	// I2C_CLOCK_STR
	if (input[I2C_CLOCK_STR] == 1)
		regs->REG_I2C_CLOCK_STR = TRUE;
	else
		regs->REG_I2C_CLOCK_STR = FALSE;

}

void Registers::parseAccessRegisters_AUTH_ACCESS(Ntag_I2C_Access_Registers *regs, BYTE input[16])
{	
	BYTE access = input[ACCESS_OFFSET];

	// check NFC_PROT
	if ((access & NFC_PROT) == NFC_PROT)
		regs->REG_NFC_PROT = TRUE;
	else
		regs->REG_NFC_PROT = FALSE;

	// check AUTHLIM
	BYTE tmpReg = (access & AUTHLIM);
	switch (tmpReg)
	{
	case 0x00: regs->REG_AUTHLIM = 0; break;
	case 0x01: regs->REG_AUTHLIM = 1; break;
	case 0x02: regs->REG_AUTHLIM = 2; break;
	case 0x03: regs->REG_AUTHLIM = 3; break;
	case 0x04: regs->REG_AUTHLIM = 4; break;
	case 0x05: regs->REG_AUTHLIM = 5; break;
	case 0x06: regs->REG_AUTHLIM = 6; break;
	case 0x07: regs->REG_AUTHLIM = 7; break;
	};

	// check NFC_DIS_SEC1
	if ((access & NFC_DIS_SEC1) == NFC_DIS_SEC1)
		regs->REG_NFC_DIS_SEC1 = TRUE;
	else
		regs->REG_NFC_DIS_SEC1 = FALSE;

	BYTE auth0 = input[AUTH_OFFSET];

	// REG_AUTH0
	regs->REG_AUTH0 = (0x00000FF & auth0);

}

void Registers::parseAccessRegisters_PT_I2C(Ntag_I2C_Access_Registers *regs, BYTE input[4])
{
	BYTE pt_i2c = input[PT_I2C_OFFSET];

	// check I2C_PROT
	BYTE tmpReg = (pt_i2c & I2C_PROT);
	switch (tmpReg)
	{
	case 0x00: regs->REG_I2C_PROT = 0; break;
	case 0x01: regs->REG_I2C_PROT= 1; break;
	case 0x02: regs->REG_I2C_PROT= 2; break;
	case 0x03: regs->REG_I2C_PROT= 3; break;
	};

	// check SRAM_PROT
	if ((pt_i2c & SRAM_PROT) == SRAM_PROT)
		regs->REG_SRAM_PROT = TRUE;
	else
		regs->REG_SRAM_PROT = FALSE;

	// check SRAM_PROT
	if ((pt_i2c & SECT1_2K_PROT) == SECT1_2K_PROT)
		regs->REG_SECT1_2K_PROT = TRUE;
	else
		regs->REG_SECT1_2K_PROT = FALSE;
	
}

// Gets an NTAG_I2C_Registers variable and leaves them in the right form to be written into the tag
void Registers::createConfigRegisters(Ntag_I2C_Registers regs, BYTE* NC_Reg, BYTE* LD_Reg, BYTE* SM_Reg, BYTE* WD_LS_Reg, BYTE* WD_MS_Reg, BYTE* I2C_CLOCK_STR_Reg)
{
	char* FD_OFF_Value = regs.REG_FD_OFF;
	char* FD_ON_Value = regs.REG_FD_ON;

	if (strncmp(FD_OFF_Value, FD_OFF_SWITCHEDOFF_OR_LASTDATAREADWRITE, 3) == 0)
		*NC_Reg = (*NC_Reg | 0x30);

	if (strncmp(FD_OFF_Value, FD_OFF_SWITCHEDOFF_OR_LASTPAGEREAD, 3) == 0) {
		*NC_Reg = (*NC_Reg & 0xcf);
		*NC_Reg = (*NC_Reg | 0x20);
	}

	if (strncmp(FD_OFF_Value, FD_OFF_SWITCHEDOFF_OR_HALTSTATE, 3) == 0) {
		*NC_Reg = (*NC_Reg & 0xcf);
		*NC_Reg = (*NC_Reg | 0x10);
	}

	if (strncmp(FD_OFF_Value, FD_OFF_SWITCHEDOFF, 3) == 0)
		*NC_Reg = (*NC_Reg & 0xcf);

	if (strncmp(FD_ON_Value, FD_ON_DATAREADY_OR_DATAREAD, 3) == 0)
		*NC_Reg = (*NC_Reg | 0x0c);

	if (strncmp(FD_ON_Value, FD_ON_SELECTION_TAG, 3) == 0)  {
		*NC_Reg = (*NC_Reg & 0xf3);
		*NC_Reg = (*NC_Reg | 0x08);
	}

	if (strncmp(FD_ON_Value, FD_ON_FIRST_VALID_SoC, 3) == 0) {
		*NC_Reg = (*NC_Reg & 0xf3);
		*NC_Reg = (*NC_Reg | 0x04);
	}

	if (strncmp(FD_ON_Value, FD_ON_SWITCHEDON, 3) == 0)
		*NC_Reg = (*NC_Reg & 0xf3);

	if (regs.REG_PTHRU_DIR == TRUE)
		*NC_Reg = (*NC_Reg | 0x01);
	else
		*NC_Reg = (*NC_Reg & 0xfe);

	*LD_Reg = regs.REG_LAST_NDEF_PAGE;
	*SM_Reg = regs.REG_SM_Reg;
	*WD_LS_Reg = regs.REG_WD_LS_Reg;
	*WD_MS_Reg = regs.REG_WD_MS_Reg;

	if (regs.REG_I2C_CLOCK_STR == TRUE)
		*I2C_CLOCK_STR_Reg = 1;
	else
		*I2C_CLOCK_STR_Reg = 0;

	if (regs.REG_I2C_RST_ON_OFF == TRUE)
		*NC_Reg = (*NC_Reg | 0x80);
	else
		*NC_Reg = (*NC_Reg & 0x7f);
}

// Gets an NTAG_I2C_Registers variable and leaves them in the right form to be written into the tag
LONG Registers::createAccessRegisters(Ntag_I2C_Access_Registers regs, BYTE* auth0, BYTE* access, BYTE* pt_i2c)
{
	LONG lReturn;

	//AUTH0
	*auth0 = regs.REG_AUTH0;

	//ACCESS

	int AUTHLIM_Value = regs.REG_AUTHLIM;

	if (AUTHLIM_Value == 0)
		*access = (*access & 0xf8);

	if (AUTHLIM_Value == 1) {
		*access = (*access & 0xf8);
		*access = (*access | 0x01);
	}

	if (AUTHLIM_Value == 2) {
		*access = (*access & 0xf8);
		*access = (*access | 0x02);
	}

	if (AUTHLIM_Value == 3)
	{
		*access = (*access & 0xf8);
		*access = (*access | 0x03);
	}

	if (AUTHLIM_Value == 4)
	{
		*access = (*access & 0xf8);
		*access = (*access | 0x04);
	}

	if (AUTHLIM_Value == 5) {
		*access = (*access & 0xf8);
		*access = (*access | 0x05);
	}

	if (AUTHLIM_Value == 6) {
		*access = (*access & 0xf8);
		*access = (*access | 0x06);
	}

	if (AUTHLIM_Value == 7)
	{
		*access = (*access | 0x07);
	}

	if (regs.REG_NFC_DIS_SEC1 == TRUE)
		*access = (*access | 0x20);
	else
		*access = (*access & 0xdf);

	if (regs.REG_NFC_PROT == TRUE)
		*access = (*access | 0x80);
	else
		*access = (*access & 0x7f);

	//PT_I2C
	if (regs.REG_SECT1_2K_PROT == TRUE)
		*pt_i2c = (*pt_i2c | 0x08);
	else
		*pt_i2c = (*pt_i2c & 0xf7);

	if (regs.REG_SRAM_PROT == TRUE)
		*pt_i2c = (*pt_i2c | 0x04);
	else
		*pt_i2c = (*pt_i2c & 0xfb);


	int i2c_prot = regs.REG_I2C_PROT;

	if (i2c_prot  == 3)
		*pt_i2c = (*pt_i2c | 0x03);

	if (i2c_prot == 2) {
		*pt_i2c = (*pt_i2c & 0xfc);
		*pt_i2c = (*pt_i2c | 0x02);
	}

	if (i2c_prot == 1) {
		*pt_i2c = (*pt_i2c & 0xfc);
		*pt_i2c = (*pt_i2c | 0x01);
	}

	if (i2c_prot == 0)
		*pt_i2c = (*pt_i2c & 0xfc);

	lReturn = SCARD_S_SUCCESS;

	return lReturn;
}

// Gets the config registers of the NTAG
LONG Registers::GetConfigRegisters(Ntag_I2C_Registers_t* configReg)
{
	LONG lReturn;
	BYTE data[16];
	BYTE NtagVersion;

	// Get all the config registers. The Configuration Registers may be located in sector 0 or sector 1
	lReturn = rf_cmm->GET_VERSION(&NtagVersion);

	if (isReturnSuccess(lReturn))
	{
		if (NtagVersion == NTAG_VERSION_2K)
			lReturn = rf_cmm->SECTOR_SELECT(1);
		// Read configuration registers
		lReturn = rf_cmm->READ(ConfigurationPage, data);
		if (lReturn == SCARD_S_SUCCESS)
			parseRegisters(configReg, data);
		if (NtagVersion == NTAG_VERSION_2K)
			rf_cmm->END_SECTOR_SELECT();	// Necessary to enable the polling again and to go back to sector 0 when the SelectSector Function has been executed
	}

	return lReturn;
}

LONG Registers::GetAccessRegisters(Ntag_I2C_Access_Registers_t* accessReg)
{
	LONG lReturn;
	BYTE data1[16];
	BYTE data2[4];

		// Read access registers
		lReturn = rf_cmm->FAST_READ(AUTH0_Page, ACCESS_Page, data1);
		if (lReturn == SCARD_S_SUCCESS)
			parseAccessRegisters_AUTH_ACCESS(accessReg, data1);

		lReturn = rf_cmm->FAST_READ(PT_I2C_Page, PT_I2C_Page, data2);
		if (lReturn == SCARD_S_SUCCESS)
			parseAccessRegisters_PT_I2C(accessReg, data2);

	return lReturn;
}


bool Registers::isGetVersionSuccess(BYTE* PointerNtagVersion){
	return (rf_cmm->GET_VERSION(PointerNtagVersion) == SCARD_S_SUCCESS);
}

bool Registers::isReturnSuccess(LONG response){
	return (response == SCARD_S_SUCCESS);
}

