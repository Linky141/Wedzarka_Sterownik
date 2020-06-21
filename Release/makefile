################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SRC/SOURCE/subdir.mk
-include Libraries/Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
WedzarkaSterownik.lss \

FLASH_IMAGE += \
WedzarkaSterownik.hex \

EEPROM_IMAGE += \
WedzarkaSterownik.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: WedzarkaSterownik.elf secondary-outputs

# Tool invocations
WedzarkaSterownik.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,WedzarkaSterownik.map -mmcu=atmega16 -o "WedzarkaSterownik.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

WedzarkaSterownik.lss: WedzarkaSterownik.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S WedzarkaSterownik.elf  >"WedzarkaSterownik.lss"
	@echo 'Finished building: $@'
	@echo ' '

WedzarkaSterownik.hex: WedzarkaSterownik.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex WedzarkaSterownik.elf  "WedzarkaSterownik.hex"
	@echo 'Finished building: $@'
	@echo ' '

WedzarkaSterownik.eep: WedzarkaSterownik.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex WedzarkaSterownik.elf  "WedzarkaSterownik.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: WedzarkaSterownik.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 WedzarkaSterownik.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) WedzarkaSterownik.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
