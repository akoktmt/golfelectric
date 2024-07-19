################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CAN_Handle/CAN_Handle.c 

OBJS += \
./CAN_Handle/CAN_Handle.o 

C_DEPS += \
./CAN_Handle/CAN_Handle.d 


# Each subdirectory must supply rules for building sources it contributes
CAN_Handle/%.o CAN_Handle/%.su CAN_Handle/%.cyclo: ../CAN_Handle/%.c CAN_Handle/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../GPShandle -I../GPSNodeStateMachine -I../CAN_Handle -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CAN_Handle

clean-CAN_Handle:
	-$(RM) ./CAN_Handle/CAN_Handle.cyclo ./CAN_Handle/CAN_Handle.d ./CAN_Handle/CAN_Handle.o ./CAN_Handle/CAN_Handle.su

.PHONY: clean-CAN_Handle

