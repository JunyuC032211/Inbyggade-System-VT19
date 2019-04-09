################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/bluetooth.c \
../Src/crc.c \
../Src/display.c \
../Src/gpio.c \
../Src/main.c \
../Src/rtc.c \
../Src/setuartrtc.c \
../Src/spi.c \
../Src/stm32f3xx_hal_msp.c \
../Src/stm32f3xx_it.c \
../Src/system_stm32f3xx.c \
../Src/telldus.c \
../Src/tim.c \
../Src/usart.c 

OBJS += \
./Src/bluetooth.o \
./Src/crc.o \
./Src/display.o \
./Src/gpio.o \
./Src/main.o \
./Src/rtc.o \
./Src/setuartrtc.o \
./Src/spi.o \
./Src/stm32f3xx_hal_msp.o \
./Src/stm32f3xx_it.o \
./Src/system_stm32f3xx.o \
./Src/telldus.o \
./Src/tim.o \
./Src/usart.o 

C_DEPS += \
./Src/bluetooth.d \
./Src/crc.d \
./Src/display.d \
./Src/gpio.d \
./Src/main.d \
./Src/rtc.d \
./Src/setuartrtc.d \
./Src/spi.d \
./Src/stm32f3xx_hal_msp.d \
./Src/stm32f3xx_it.d \
./Src/system_stm32f3xx.d \
./Src/telldus.d \
./Src/tim.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F303xC -I"/home/johan/Dropbox/KTH/Avklarade Kurser/IS1300-InbyggdaSystem/STM32-Projects/DigTemp-Projekt/DigTemp-Projekt/DigTemp/Inc" -I"/home/johan/Dropbox/KTH/Avklarade Kurser/IS1300-InbyggdaSystem/STM32-Projects/DigTemp-Projekt/DigTemp-Projekt/DigTemp/Drivers/STM32F3xx_HAL_Driver/Inc" -I"/home/johan/Dropbox/KTH/Avklarade Kurser/IS1300-InbyggdaSystem/STM32-Projects/DigTemp-Projekt/DigTemp-Projekt/DigTemp/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"/home/johan/Dropbox/KTH/Avklarade Kurser/IS1300-InbyggdaSystem/STM32-Projects/DigTemp-Projekt/DigTemp-Projekt/DigTemp/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"/home/johan/Dropbox/KTH/Avklarade Kurser/IS1300-InbyggdaSystem/STM32-Projects/DigTemp-Projekt/DigTemp-Projekt/DigTemp/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


