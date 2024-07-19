################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPSNodeStateMachine/GPS_StateMachine.c 

OBJS += \
./GPSNodeStateMachine/GPS_StateMachine.o 

C_DEPS += \
./GPSNodeStateMachine/GPS_StateMachine.d 


# Each subdirectory must supply rules for building sources it contributes
GPSNodeStateMachine/%.o GPSNodeStateMachine/%.su GPSNodeStateMachine/%.cyclo: ../GPSNodeStateMachine/%.c GPSNodeStateMachine/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../GPShandle -I../GPSNodeStateMachine -I../CAN_Handle -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-GPSNodeStateMachine

clean-GPSNodeStateMachine:
	-$(RM) ./GPSNodeStateMachine/GPS_StateMachine.cyclo ./GPSNodeStateMachine/GPS_StateMachine.d ./GPSNodeStateMachine/GPS_StateMachine.o ./GPSNodeStateMachine/GPS_StateMachine.su

.PHONY: clean-GPSNodeStateMachine

