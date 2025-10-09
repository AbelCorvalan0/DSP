################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_ctimer.c \
../drivers/fsl_dac.c \
../drivers/fsl_gpio.c \
../drivers/fsl_inputmux.c \
../drivers/fsl_lpadc.c \
../drivers/fsl_lpflexcomm.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_reset.c \
../drivers/fsl_spc.c \
../drivers/fsl_vref.c 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_ctimer.d \
./drivers/fsl_dac.d \
./drivers/fsl_gpio.d \
./drivers/fsl_inputmux.d \
./drivers/fsl_lpadc.d \
./drivers/fsl_lpflexcomm.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_reset.d \
./drivers/fsl_spc.d \
./drivers/fsl_vref.d 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_ctimer.o \
./drivers/fsl_dac.o \
./drivers/fsl_gpio.o \
./drivers/fsl_inputmux.o \
./drivers/fsl_lpadc.o \
./drivers/fsl_lpflexcomm.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_reset.o \
./drivers/fsl_spc.o \
./drivers/fsl_vref.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MCXN947VDF -DCPU_MCXN947VDF_cm33 -DCPU_MCXN947VDF_cm33_core0 -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DMCXN947_cm33_core0_SERIES -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_DAC0_pruebaRampa\drivers" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_DAC0_pruebaRampa\CMSIS" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_DAC0_pruebaRampa\CMSIS\m-profile" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_DAC0_pruebaRampa\device" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_DAC0_pruebaRampa\device\periph" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_DAC0_pruebaRampa\utilities" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_DAC0_pruebaRampa\utilities\str" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_DAC0_pruebaRampa\utilities\debug_console_lite" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_DAC0_pruebaRampa\component\uart" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_DAC0_pruebaRampa\source" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_DAC0_pruebaRampa\board" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -fno-builtin -imacros "C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_DAC0_pruebaRampa\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_ctimer.d ./drivers/fsl_ctimer.o ./drivers/fsl_dac.d ./drivers/fsl_dac.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_inputmux.d ./drivers/fsl_inputmux.o ./drivers/fsl_lpadc.d ./drivers/fsl_lpadc.o ./drivers/fsl_lpflexcomm.d ./drivers/fsl_lpflexcomm.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_reset.d ./drivers/fsl_reset.o ./drivers/fsl_spc.d ./drivers/fsl_spc.o ./drivers/fsl_vref.d ./drivers/fsl_vref.o

.PHONY: clean-drivers

