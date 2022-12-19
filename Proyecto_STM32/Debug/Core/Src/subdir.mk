################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/BH1750.c \
../Core/Src/Bluetooth.c \
../Core/Src/DOT_MATRIX.c \
../Core/Src/DOT_MATRIX_cfg.c \
../Core/Src/RTC.c \
../Core/Src/dht11.c \
../Core/Src/fatfs_app.c \
../Core/Src/fatfs_sd.c \
../Core/Src/freertos.c \
../Core/Src/inicializaciones.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_hal_timebase_tim.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tareas_rutina.c 

OBJS += \
./Core/Src/BH1750.o \
./Core/Src/Bluetooth.o \
./Core/Src/DOT_MATRIX.o \
./Core/Src/DOT_MATRIX_cfg.o \
./Core/Src/RTC.o \
./Core/Src/dht11.o \
./Core/Src/fatfs_app.o \
./Core/Src/fatfs_sd.o \
./Core/Src/freertos.o \
./Core/Src/inicializaciones.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_hal_timebase_tim.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tareas_rutina.o 

C_DEPS += \
./Core/Src/BH1750.d \
./Core/Src/Bluetooth.d \
./Core/Src/DOT_MATRIX.d \
./Core/Src/DOT_MATRIX_cfg.d \
./Core/Src/RTC.d \
./Core/Src/dht11.d \
./Core/Src/fatfs_app.d \
./Core/Src/fatfs_sd.d \
./Core/Src/freertos.d \
./Core/Src/inicializaciones.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_hal_timebase_tim.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tareas_rutina.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/BH1750.d ./Core/Src/BH1750.o ./Core/Src/BH1750.su ./Core/Src/Bluetooth.d ./Core/Src/Bluetooth.o ./Core/Src/Bluetooth.su ./Core/Src/DOT_MATRIX.d ./Core/Src/DOT_MATRIX.o ./Core/Src/DOT_MATRIX.su ./Core/Src/DOT_MATRIX_cfg.d ./Core/Src/DOT_MATRIX_cfg.o ./Core/Src/DOT_MATRIX_cfg.su ./Core/Src/RTC.d ./Core/Src/RTC.o ./Core/Src/RTC.su ./Core/Src/dht11.d ./Core/Src/dht11.o ./Core/Src/dht11.su ./Core/Src/fatfs_app.d ./Core/Src/fatfs_app.o ./Core/Src/fatfs_app.su ./Core/Src/fatfs_sd.d ./Core/Src/fatfs_sd.o ./Core/Src/fatfs_sd.su ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/inicializaciones.d ./Core/Src/inicializaciones.o ./Core/Src/inicializaciones.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_hal_timebase_tim.d ./Core/Src/stm32f4xx_hal_timebase_tim.o ./Core/Src/stm32f4xx_hal_timebase_tim.su ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/tareas_rutina.d ./Core/Src/tareas_rutina.o ./Core/Src/tareas_rutina.su

.PHONY: clean-Core-2f-Src

