/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-2013
 * (c) NXP Semiconductors 2013-2016
 * Generated linker script file for LPC11U24/401
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.23
 * LPCXpresso v8.2.2 [Build 650] [2016-09-09]  on Dec 8, 2016 10:19:06 PM
 */

MEMORY
{
  /* Define each memory region */
  MFlash32 (rx) : ORIGIN = 0x4000, LENGTH = 0x4000 /* 16K bytes (alias Flash) */  
  RamLoc8 (rwx) : ORIGIN = 0x10000200, LENGTH = 0x1de0 /* 7648 bytes (alias RAM) */  
}

  /* Define a symbol for the top of each memory region */
  __base_MFlash32 = 0x4000  ; /* MFlash32 */  
  __base_Flash = 0x4000 ; /* Flash */  
  __top_MFlash32 = 0x4000 + 0x4000 ; /* 16K bytes */  
  __top_Flash = 0x4000 + 0x4000 ; /* 16K bytes */  
  __base_RamLoc8 = 0x10000200  ; /* RamLoc8 */  
  __base_RAM = 0x10000200 ; /* RAM */  
  __top_RamLoc8 = 0x10000200 + 0x1de0 ; /* 7648 bytes */  
  __top_RAM = 0x10000200 + 0x1de0 ; /* 7648 bytes */  
