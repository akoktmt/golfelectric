################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32-Hardware-Driver/BNO055/bno055.c 

OBJS += \
./STM32-Hardware-Driver/BNO055/bno055.o 

C_DEPS += \
./STM32-Hardware-Driver/BNO055/bno055.d 


# Each subdirectory must supply rules for building sources it contributes
STM32-Hardware-Driver/BNO055/%.o STM32-Hardware-Driver/BNO055/%.su STM32-Hardware-Driver/BNO055/%.cyclo: ../STM32-Hardware-Driver/BNO055/%.c STM32-Hardware-Driver/BNO055/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DSTM32_THREAD_SAFE_STRATEGY=4 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"C:/Users/win 10/OneDrive/Desktop/GolfCar/GoftCar_Code/enginenode/Code/STM32_RTOS_PeripheralDriver" -I"C:/Users/win 10/OneDrive/Desktop/GolfCar/GoftCar_Code/enginenode/Code/STM32-Hardware-Driver" -I"C:/Users/win 10/OneDrive/Desktop/GolfCar/GoftCar_Code/enginenode/Code/Periodics" -I../Core/ThreadSafe -I"C:/Users/win 10/OneDrive/Desktop/GolfCar/GoftCar_Code/enginenode/Code/UtilitySmallFunction" -I"C:/Users/win 10/OneDrive/Desktop/GolfCar/GoftCar_Code/enginenode/Code/CRC" -I../CAN_Handle -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-STM32-2d-Hardware-2d-Driver-2f-BNO055

clean-STM32-2d-Hardware-2d-Driver-2f-BNO055:
	-$(RM) ./STM32-Hardware-Driver/BNO055/bno055.cyclo ./STM32-Hardware-Driver/BNO055/bno055.d ./STM32-Hardware-Driver/BNO055/bno055.o ./STM32-Hardware-Driver/BNO055/bno055.su

.PHONY: clean-STM32-2d-Hardware-2d-Driver-2f-BNO055

