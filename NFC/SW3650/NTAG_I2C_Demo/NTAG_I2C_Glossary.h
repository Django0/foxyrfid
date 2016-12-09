
//**************************
//DEFINES IN RF_COMMANDS
//

#define NTAG_PAGE_SIZE 4
#define NTAG_CRC_SIZE 2

#define CMD_GET_VERSION  0x60
#define CMD_GET_VERSION_RESP_LENGTH 10

#define NTAG_V1K_CODE 0x13
#define NTAG_V2K_CODE 0x15

#define CMD_DISABLE_POLLING 0xFF, 0xCC, 0x00, 0x00, 0x02, 0xAC, 0x01
#define CMD_DISABLE_POLLING_RESP_LENGTH 2

#define CMD_SECTOR_SELECT 0xC2
#define CMD0_SECTOR_SELECT_RESP_LENGTH 1


#define CMD1_SECTOR_SELECT 0xFF, 0xEF, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00
#define CMD1_SECTOR_SELECT_RESP_LENGTH 1

#define CMD_ENABLE_POLLING 0xFF, 0xCC, 0x00, 0x00, 0x02, 0xAC, 0x00
#define CMD_ENABLE_POLLING_RESP_LENGTH 2

#define CMD_ERROR 0xFF, 0xEF, 0x00, 0x00, 0x01, 0x00
#define CMD_ERROR_RESP_LENGTH 1

#define CMD_READ 0x30
#define CMD_READ_RESP_LENGTH 18 

#define CMD_FAST_READ 0x3A
#define CMD_FAST_READ_RESP_LENGTH 1026

#define CMD_WRITE 0xA2
#define CMD_WRITE_RESP_LENGTH 1 

#define CMD_FAST_WRITE 0xA6
#define CMD_FAST_WRITE_START 0xF0
#define CMD_FAST_WRITE_END 0xFF
#define CMD_FAST_WRITE_RESP_LENGTH 1
#define DATA_64_BYTES 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#define CMD_PWD_AUTH 0x1B
#define CMD_PWD_AUTH_RESP_LENGTH 4

//**************************
//DEFINES IN REGISTERS
//

#define SESSION_REGISTER_SECTOR 3
#define CONFIG_REGISTER_SECTOR 0
#define REG_LOCK_ENABLE 0x00
#define FIXED_CONF_PAGE2_BYTE3	0x00
#define FD_OFF_SWITCHEDOFF	"00b"
#define FD_OFF_SWITCHEDOFF_OR_HALTSTATE "01b"
#define FD_OFF_SWITCHEDOFF_OR_LASTPAGEREAD "10b"
#define FD_OFF_SWITCHEDOFF_OR_LASTDATAREADWRITE "11b"

#define FD_ON_SWITCHEDON "00b"
#define FD_ON_FIRST_VALID_SoC "01b"
#define FD_ON_SELECTION_TAG "10b"
#define FD_ON_DATAREADY_OR_DATAREAD "11b"

#define REG_AUTHLIM_000 "000b"
#define REG_AUTHLIM_001 "001b"
#define REG_AUTHLIM_010 "010b"
#define REG_AUTHLIM_011 "011b"
#define REG_AUTHLIM_100 "100b"
#define REG_AUTHLIM_101 "101b"
#define REG_AUTHLIM_110 "110b"
#define REG_AUTHLIM_111 "111b"

#define REG_I2C_PROT_00 "00b"
#define REG_I2C_PROT_01 "01b"
#define REG_I2C_PROT_10 "10b"
#define REG_I2C_PROT_11 "11b"
//**************************
//DEFINES FOR NDEF
//
#define NDEF_NFCF_TYPE2 0x03
#define NDEF_TNF_SHORT 0xD1
#define NDEF_TNF_LONG 0xC1
#define NDEF_SMARTPOSTER_TYPE 0x53
#define NDEF_TEXT_TYPE 0x54
#define NDEF_URI_TYPE 0x55
#define NDEF_TEXT_LANG_P1 0x65 //E for En (English)
#define NDEF_TEXT_LANG_P2 0x6E //N for eN (English)

//**************************
//DEFINES FOR PASSWORD
//
#define PWD_PAGE 0xE5
#define CLEAN_PWD 0xFFFFFFFF
#define AUTH0_PAGE 0xE3
#define SET_AUTH0 0x03
#define CLEAN_AUTH0 0xFF
#define ACCESS_PAGE 0xE4
#define PACK_PAGE 0xE6
#define SET_ACCESS 0x80
#define CLEAN_ACCESS 0x00
#define PT_I2C_PAGE 0xE7
#define SET_PT_I2C 0x04
#define CLEAN_PT_I2C 0x00