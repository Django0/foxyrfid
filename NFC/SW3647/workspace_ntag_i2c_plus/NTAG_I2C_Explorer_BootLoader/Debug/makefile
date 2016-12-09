################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: NTAG_I2C_Explorer_BootLoader.axf

dependents:
	-cd /home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/NTAG_I2C_API/Debug && $(MAKE) clean all
	-cd /home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/lpc_chip_11uxx_lib/Debug && $(MAKE) clean all

# Tool invocations
NTAG_I2C_Explorer_BootLoader.axf: $(OBJS) $(USER_OBJS) /home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/NTAG_I2C_API/Debug/libNTAG_I2C_API.a /home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/lpc_chip_11uxx_lib/Debug/liblpc_chip_11uxx_lib.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/nxp_lpcxpresso_11u24h_board_lib/Debug" -L"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/lpc_chip_11uxx_lib/Debug" -L"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/NTAG_I2C_API/Debug" -Xlinker -Map="NTAG_I2C_Explorer_BootLoader.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "NTAG_I2C_Explorer_BootLoader_Debug.ld" -o "NTAG_I2C_Explorer_BootLoader.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) NTAG_I2C_Explorer_BootLoader.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size NTAG_I2C_Explorer_BootLoader.axf ; arm-none-eabi-objcopy -O binary NTAG_I2C_Explorer_BootLoader.axf NTAG_I2C_Explorer_BootLoader.bin ; checksum -p LPC11U24_401 -d NTAG_I2C_Explorer_BootLoader.bin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/NTAG_I2C_API/Debug/libNTAG_I2C_API.a:
/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/lpc_chip_11uxx_lib/Debug/liblpc_chip_11uxx_lib.a:

-include ../makefile.targets
