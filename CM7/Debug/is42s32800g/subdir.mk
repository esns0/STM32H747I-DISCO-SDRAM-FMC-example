################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../is42s32800g/is42s32800g.c 

OBJS += \
./is42s32800g/is42s32800g.o 

C_DEPS += \
./is42s32800g/is42s32800g.d 


# Each subdirectory must supply rules for building sources it contributes
is42s32800g/%.o is42s32800g/%.su is42s32800g/%.cyclo: ../is42s32800g/%.c is42s32800g/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H747xx -c -I../Core/Inc -I../is42s32800g -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-is42s32800g

clean-is42s32800g:
	-$(RM) ./is42s32800g/is42s32800g.cyclo ./is42s32800g/is42s32800g.d ./is42s32800g/is42s32800g.o ./is42s32800g/is42s32800g.su

.PHONY: clean-is42s32800g

