################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/boot_multicore_slave.c \
../startup/startup_mcxn947_cm33_core0.c 

C_DEPS += \
./startup/boot_multicore_slave.d \
./startup/startup_mcxn947_cm33_core0.d 

OBJS += \
./startup/boot_multicore_slave.o \
./startup/startup_mcxn947_cm33_core0.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DMCUXPRESSO_SDK -DCPU_MCXN947VDF_cm33_core0 -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DMCXN947_cm33_core0_SERIES -DCPU_MCXN947VDF -DCPU_MCXN947VDF_cm33 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/source" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/drivers" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/CMSIS" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/CMSIS/m-profile" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/device" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/device/periph" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/utilities" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/utilities/str" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/utilities/debug_console_lite" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/component/uart" -I"/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/board" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -fno-builtin -imacros "/home/abel/Documents/MCUXpresso_25.6.136/workspaceMCX/frdmmcxn947_lpadc_interrupt_cm33_core0/source/mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-startup

clean-startup:
	-$(RM) ./startup/boot_multicore_slave.d ./startup/boot_multicore_slave.o ./startup/startup_mcxn947_cm33_core0.d ./startup/startup_mcxn947_cm33_core0.o

.PHONY: clean-startup

