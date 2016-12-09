#ifndef Ntag_I2C_Registers_H
#define Ntag_I2C_Registers_H
#include "RF_Commands.h"

namespace NTAG_I2C_Demo
{
	///
	/// This struct will hold the values of the Config/Session registers
	///
	typedef struct Ntag_I2C_Registers
	{
		char	REG_Manufacture[25];
		int		REG_Mem_size;
		BOOL	REG_I2C_RST_ON_OFF;
		char	REG_FD_OFF[3];
		char	REG_FD_ON[3];
		int		REG_LAST_NDEF_PAGE;
		BOOL	REG_NDEF_DATA_READ;
		BOOL	REG_RF_FIELD_PRESENT;
		BOOL	REG_PTHRU_ON_OFF;
		BOOL	REG_I2C_LOCKED;
		BOOL	REG_RF_LOCKED;
		BOOL	REG_SRAM_I2C_READY;
		BOOL	REG_SRAM_RF_READY;
		BOOL	REG_EEPROM_WR_BUSY;
		BOOL	REG_PTHRU_DIR;
		int		REG_SM_Reg;
		int		REG_WD_LS_Reg;
		int		REG_WD_MS_Reg;
		//	String	REG_NDEF_Message;
		BOOL	REG_SRAM_MIRROR_ON_OFF;
		BOOL	REG_I2C_CLOCK_STR;
	} Ntag_I2C_Registers_t;

	///
	/// This struct will hold the values of the Access registers
	///
	typedef struct Ntag_I2C_Access_Registers
	{
		int		REG_AUTH0;
		int		REG_AUTHLIM;
		int		REG_I2C_PROT;
		BOOL	REG_NFC_PROT;
		BOOL	REG_NFC_DIS_SEC1;
		BOOL	REG_SECT1_2K_PROT;
		BOOL	REG_SRAM_PROT;
	} Ntag_I2C_Access_Registers_t;

	///
	/// This registers class will contain the main features of the session and configuration
	/// registers. The main characteristics are: Read Session/Config registers and Write Config registers.
	///
	class Registers
	{
	public:

		//Constructors
		Registers(RF_Commands *rf_in);
		Registers(LPCTSTR readerIdentifierString);

		/** @brief Reads the session registers of the NTAG_I2C_IC
		*
		*  At first we have to establish a exclusive connection,
		*  later we have to select the sector where the session registers are placed.
		*  When we are in the correct sector, we read the page where the session registers are.
		*  Finally we parse the registers in order to accommodate the data in the struct and release the current connection.
		*
		*  @param sessionReg Struct of type NTAG_I2C_Registers_t that will contain the session registers.
		*  @return ReadSessionRegisters result (if success it will be 0).
		*/
		LONG ReadSessionRegisters(Ntag_I2C_Registers_t* sessionReg);

		/** @brief Reads the configuration registers of the NTAG_I2C_IC
		*
		*  At first we have to establish a exclusive connection,
		*  later we have to select the sector where the configuration registers are placed.
		*  When we are in the correct sector, we read the page where the configuration registers are.
		*  Finally we parse the registers in order to accommodate the data in the struct and release the current connection.
		*
		*  @param configReg Struct of type NTAG_I2C_Registers_t that will contain the config registers.
		*  @return ReadConfigRegisters result (if success it will be 0).
		*/
		LONG ReadConfigRegisters(Ntag_I2C_Registers_t* configReg);

		/** @brief Writes the configuration registers of the NTAG_I2C_IC
		*
		*  First of all we have to establish a exclusive connection,
		*  then we have to select the sector where the configuration registers are placed.
		*  Later we call createConfigRegisters in order to create a new Config Registers struct.
		*  When we are in the correct sector, we write into the page where the configuration registers are.
		*  Finally we parse the registers in order to accommodate the data in the struct and release the current connection.
		*
		*  @param configReg Struct of type NTAG_I2C_Registers_t that will contain the config registers.
		*  @return WriteConfigRegisters result (if success it will be 0).
		*/
		LONG WriteConfigRegisters(Ntag_I2C_Registers_t configReg);

		/** @brief Writes the access registers of the NTAG_I2C_IC
		*
		*  @param accessReg Struct of type NTAG_I2C_Registers_t that will contain the access registers.
		*  @return WriteAccessRegisters result (if success it will be 0).
		*/
		LONG WriteAccessRegisters(Ntag_I2C_Access_Registers_t accessReg);

		/** @brief Reads the access registers of the NTAG_I2C_IC
		*
		*  @param accessReg Struct of type NTAG_I2C_Registers_t that will contain the access registers.
		*  @return ReadAccessRegisters result (if success it will be 0).
		*/
		LONG ReadAccessRegisters(Ntag_I2C_Access_Registers_t* accessReg);

		LONG SetConfigRegisters(Ntag_I2C_Registers_t configReg);
		LONG SetAccessRegisters(Ntag_I2C_Access_Registers_t accessReg);
		void parseRegisters(Ntag_I2C_Registers *regs, BYTE input[16]);
		void Registers::parseAccessRegisters_PT_I2C(Ntag_I2C_Access_Registers *regs, BYTE input[8]);
		void Registers::parseAccessRegisters_AUTH_ACCESS(Ntag_I2C_Access_Registers *regs, BYTE input[16]);
		void createConfigRegisters(Ntag_I2C_Registers regs, BYTE* NC_Reg, BYTE* LD_Reg, BYTE* SM_Reg, BYTE* WD_LS_Reg, BYTE* WD_MS_Reg, BYTE* I2C_CLOCK_STR_Reg);
		LONG createAccessRegisters(Ntag_I2C_Access_Registers regs, BYTE* auth0, BYTE* access, BYTE* pt_i2c);
		LONG GetConfigRegisters(Ntag_I2C_Registers_t* configReg);
		LONG Registers::GetAccessRegisters(Ntag_I2C_Access_Registers_t* accessReg);

	private:

		bool isGetVersionSuccess(BYTE* PointerNtagVersion);
		bool isReturnSuccess(LONG response);
		void freePciAndDisconnectCard();
		void freeCardHandle();
	};

}
#endif