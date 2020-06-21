################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Source/SPI.c \
../Libraries/Source/delay.c \
../Libraries/Source/eeprom.c \
../Libraries/Source/gpio.c \
../Libraries/Source/lcd.c \
../Libraries/Source/uart.c 

OBJS += \
./Libraries/Source/SPI.o \
./Libraries/Source/delay.o \
./Libraries/Source/eeprom.o \
./Libraries/Source/gpio.o \
./Libraries/Source/lcd.o \
./Libraries/Source/uart.o 

C_DEPS += \
./Libraries/Source/SPI.d \
./Libraries/Source/delay.d \
./Libraries/Source/eeprom.d \
./Libraries/Source/gpio.d \
./Libraries/Source/lcd.d \
./Libraries/Source/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Source/%.o: ../Libraries/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


