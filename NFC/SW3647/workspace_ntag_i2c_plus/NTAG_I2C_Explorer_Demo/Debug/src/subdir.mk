################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/HW_functions.c \
../src/crc32.c \
../src/main.c \
../src/ndef_parser.c 

OBJS += \
./src/HW_functions.o \
./src/crc32.o \
./src/main.o \
./src/ndef_parser.o 

C_DEPS += \
./src/HW_functions.d \
./src/crc32.d \
./src/main.d \
./src/ndef_parser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DBoard_NTAG_I2C_Explorer -D__LPC11U37H__ -DHAVE_NTAG_INTERRUPT -DHAVE_STDINT_H -DCORE_M0 -D__MTB_BUFFER_SIZE=2048 -DHAVE_STDBOOL_H -D__USE_LPC -DNDEBUG -D__CODE_RED -DBOARD_NTAG_I2C_EXPLORER -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/NTAG_I2C_API/src/inc" -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/NTAG_I2C_Explorer_Demo/inc" -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/nxp_lpcxpresso_11u24h_board_lib/inc" -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/lpc_chip_11uxx_lib/inc" -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/lpc_chip_11uxx_lib/inc/usbd" -O0 -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


