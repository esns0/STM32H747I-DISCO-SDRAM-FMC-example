################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/workspace/c/H747_DISCO/Common/is42s32800g/is42s32800g.c 

OBJS += \
./Common/is42s32800g/is42s32800g.o 

C_DEPS += \
./Common/is42s32800g/is42s32800g.d 


# Each subdirectory must supply rules for building sources it contributes
Common/is42s32800g/is42s32800g.o: C:/workspace/c/H747_DISCO/Common/is42s32800g/is42s32800g.c Common/is42s32800g/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H747xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I"C:/workspace/c/H747_DISCO/Common/is42s32800g" -I"C:/workspace/c/H747_DISCO/CM7/Core/Inc" -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-is42s32800g

clean-Common-2f-is42s32800g:
	-$(RM) ./Common/is42s32800g/is42s32800g.cyclo ./Common/is42s32800g/is42s32800g.d ./Common/is42s32800g/is42s32800g.o ./Common/is42s32800g/is42s32800g.su

.PHONY: clean-Common-2f-is42s32800g

