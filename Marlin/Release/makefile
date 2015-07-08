################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include arduino/variant/subdir.mk
-include arduino/core/avr/subdir.mk
-include arduino/core/USB/subdir.mk
-include arduino/core/subdir.mk
-include Libraries/Wire/subdir.mk
-include Libraries/U8glib/utility/subdir.mk
-include Libraries/U8glib/subdir.mk
-include Libraries/SPI/subdir.mk
-include Libraries/LiquidTWI2/subdir.mk
-include Libraries/LiquidCrystal_I2C/subdir.mk
-include Libraries/LiquidCrystal/src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
arduino.ar \

ELF += \
Marlin.elf \

EEP += \
Marlin.eep \

FLASH_IMAGE += \
Marlin.bin \


# All Target
all: Marlin

# Tool invocations
Marlin: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/home/nico/Tools/arduino-1.5.8/hardware/tools/gcc-arm-none-eabi-4.8.3-2014q1/bin/arm-none-eabi-size" -A "/home/nico/github/wurstnase/Marlin4Due/Marlin/Release/Marlin.elf"
	@echo 'Finished building target: $@'
	@echo ' '

arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/home/nico/Tools/arduino-1.5.8/hardware/tools/gcc-arm-none-eabi-4.8.3-2014q1/bin/arm-none-eabi-ar" rcs  "/home/nico/github/wurstnase/Marlin4Due/Marlin/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

Marlin.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/home/nico/Tools/arduino-1.5.8/hardware/tools/gcc-arm-none-eabi-4.8.3-2014q1/bin/arm-none-eabi-gcc" -Os -Wl,--gc-sections -mcpu=cortex-m3 "-T/home/nico/Tools/arduino-1.5.8/hardware/arduino/sam/variants/arduino_due_x/linker_scripts/gcc/flash.ld" "-Wl,-Map,/home/nico/github/wurstnase/Marlin4Due/Marlin/Release/Marlin.map"  -o "/home/nico/github/wurstnase/Marlin4Due/Marlin/Release/Marlin.elf" "-L/home/nico/github/wurstnase/Marlin4Due/Marlin/Release" -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--warn-unresolved-symbols -Wl,--start-group "/home/nico/github/wurstnase/Marlin4Due/Marlin/Release/arduino/syscalls_sam3.c.o"   $(LINK_OBJ) $(AR)  "/home/nico/Tools/arduino-1.5.8/hardware/arduino/sam/variants/arduino_due_x/libsam_sam3x8e_gcc_rel.a" "/home/nico/github/wurstnase/Marlin4Due/Marlin/Release/arduino.ar" -Wl,--end-group -lm -gcc
	@echo 'Finished building: $@'
	@echo ' '

Marlin.eep: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

Marlin.bin: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"/home/nico/Tools/arduino-1.5.8/hardware/tools/gcc-arm-none-eabi-4.8.3-2014q1/bin/arm-none-eabi-objcopy" -O binary  "/home/nico/github/wurstnase/Marlin4Due/Marlin/Release/Marlin.elf" "/home/nico/github/wurstnase/Marlin4Due/Marlin/Release/Marlin.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(C_DEPS)$(AR)$(EEP)$(FLASH_IMAGE)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS) Marlin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
