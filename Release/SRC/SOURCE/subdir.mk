################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/SOURCE/main.c \
../SRC/SOURCE/termo.c 

OBJS += \
./SRC/SOURCE/main.o \
./SRC/SOURCE/termo.o 

C_DEPS += \
./SRC/SOURCE/main.d \
./SRC/SOURCE/termo.d 


# Each subdirectory must supply rules for building sources it contributes
SRC/SOURCE/%.o: ../SRC/SOURCE/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

