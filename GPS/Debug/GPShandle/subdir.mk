################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPShandle/gpshandle.c 

OBJS += \
./GPShandle/gpshandle.o 

C_DEPS += \
./GPShandle/gpshandle.d 


# Each subdirectory must supply rules for building sources it contributes
GPShandle/%.o GPShandle/%.su GPShandle/%.cyclo: ../GPShandle/%.c GPShandle/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../GPShandle -I../GPSNodeStateMachine -I../CAN_Handle -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-GPShandle

clean-GPShandle:
	-$(RM) ./GPShandle/gpshandle.cyclo ./GPShandle/gpshandle.d ./GPShandle/gpshandle.o ./GPShandle/gpshandle.su

.PHONY: clean-GPShandle

