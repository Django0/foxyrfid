################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/HAL_I2C/i2c_lpc11u37h.c 

OBJS += \
./src/HAL_I2C/i2c_lpc11u37h.o 

C_DEPS += \
./src/HAL_I2C/i2c_lpc11u37h.d 


# Each subdirectory must supply rules for building sources it contributes
src/HAL_I2C/%.o: ../src/HAL_I2C/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -D__LPC11U37H__ -DCORE_M0 -D__USE_LPC -DHAVE_NTAG_INTERRUPT -DHAVE_STDBOOL_H -DHAVE_STDINT_H -D__USE_LPCOPEN -DDEBUG_SEMIHOSTING -DCR_INTEGER_PRINTF -DDEBUG -D__CODE_RED -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/nxp_lpcxpresso_11u24h_board_lib/inc" -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/NTAG_I2C_API/src/inc" -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/NTAG_I2C_API/src/HAL_BSP_LPC8xx/inc" -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/NTAG_I2C_API/src/HAL_BSP11U6x/inc" -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/NTAG_I2C_API/src/HAL_I2C/inc" -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/NTAG_I2C_API/src/HAL_ISR/inc" -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/NTAG_I2C_API/src/HAL_NTAG/inc" -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/NTAG_I2C_API/src/HAL_TMR/inc" -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/lpc_chip_11uxx_lib/inc" -I"/home/django/Documents/Foxy/Gitting/foxyrfid/NFC/SW3647/workspace_ntag_i2c_plus/nxp_lpcxpresso_11u24h_board_lib/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


