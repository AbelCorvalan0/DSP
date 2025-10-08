################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/hardware_init.c \
../board/peripherals.c \
../board/pin_mux.c 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/hardware_init.d \
./board/peripherals.d \
./board/pin_mux.d 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/hardware_init.o \
./board/peripherals.o \
./board/pin_mux.o 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MCXN947VDF -DCPU_MCXN947VDF_cm33 -DCPU_MCXN947VDF_cm33_core0 -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DMCXN947_cm33_core0_SERIES -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_LEDRGB-ConInterrupciones\drivers" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_LEDRGB-ConInterrupciones\CMSIS" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_LEDRGB-ConInterrupciones\CMSIS\m-profile" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_LEDRGB-ConInterrupciones\device" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_LEDRGB-ConInterrupciones\device\periph" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_LEDRGB-ConInterrupciones\utilities" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_LEDRGB-ConInterrupciones\utilities\str" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_LEDRGB-ConInterrupciones\utilities\debug_console_lite" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_LEDRGB-ConInterrupciones\component\uart" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_LEDRGB-ConInterrupciones\source" -I"C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_LEDRGB-ConInterrupciones\board" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -fno-builtin -imacros "C:\Users\ferok\Documents\MCUXpressoIDE_25.6.136\workspace_FRDMMCXN947\CTIMER0_GPIO00_LEDRGB-ConInterrupciones\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-board

clean-board:
	-$(RM) ./board/board.d ./board/board.o ./board/clock_config.d ./board/clock_config.o ./board/hardware_init.d ./board/hardware_init.o ./board/peripherals.d ./board/peripherals.o ./board/pin_mux.d ./board/pin_mux.o

.PHONY: clean-board

