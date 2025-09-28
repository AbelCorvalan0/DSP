################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_MCXN947_cm33_core0.c 

C_DEPS += \
./device/system_MCXN947_cm33_core0.d 

OBJS += \
./device/system_MCXN947_cm33_core0.o 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c device/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MCXN947VDF -DCPU_MCXN947VDF_cm33 -DCPU_MCXN947VDF_cm33_core0 -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DMCXN947_cm33_core0_SERIES -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/source" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/drivers" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/CMSIS" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/CMSIS/m-profile" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/device" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/device/periph" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/utilities" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/utilities/str" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/utilities/debug_console_lite" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/component/uart" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/board" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -fno-builtin -imacros "/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/source/mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-device

clean-device:
	-$(RM) ./device/system_MCXN947_cm33_core0.d ./device/system_MCXN947_cm33_core0.o

.PHONY: clean-device

