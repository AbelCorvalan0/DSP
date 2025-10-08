################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/str/subdir.mk
-include utilities/debug_console_lite/subdir.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include board/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := CTIMER0_GPIO00_LEDRGB-ConInterrupciones
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: CTIMER0_GPIO00_LEDRGB-ConInterrupciones.axf

# Tool invocations
CTIMER0_GPIO00_LEDRGB-ConInterrupciones.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -no-warn-rwx-segments -Xlinker -Map="CTIMER0_GPIO00_LEDRGB-ConInterrupciones.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -T CTIMER0_GPIO00_LEDRGB-ConInterrupciones_Debug.ld -o "CTIMER0_GPIO00_LEDRGB-ConInterrupciones.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) CTIMER0_GPIO00_LEDRGB-ConInterrupciones.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "CTIMER0_GPIO00_LEDRGB-ConInterrupciones.axf"; # arm-none-eabi-objcopy -v -O binary "CTIMER0_GPIO00_LEDRGB-ConInterrupciones.axf" "CTIMER0_GPIO00_LEDRGB-ConInterrupciones.bin" ; # checksum -p MCXN947 -d "CTIMER0_GPIO00_LEDRGB-ConInterrupciones.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
