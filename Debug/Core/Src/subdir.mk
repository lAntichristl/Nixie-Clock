################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Button.c \
../Core/Src/d_debug.c \
../Core/Src/freertos.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/rtc.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_hal_timebase_tim.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/tim.c 

CPP_SRCS += \
../Core/Src/Clock.cpp \
../Core/Src/GPin.cpp \
../Core/Src/Gpio.cpp \
../Core/Src/Menu.cpp \
../Core/Src/Object.cpp \
../Core/Src/PWM.cpp \
../Core/Src/Pin.cpp \
../Core/Src/PinController.cpp \
../Core/Src/SoftwareTimer.cpp \
../Core/Src/Task.cpp \
../Core/Src/d_main.cpp 

C_DEPS += \
./Core/Src/Button.d \
./Core/Src/d_debug.d \
./Core/Src/freertos.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/rtc.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_hal_timebase_tim.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/tim.d 

OBJS += \
./Core/Src/Button.o \
./Core/Src/Clock.o \
./Core/Src/GPin.o \
./Core/Src/Gpio.o \
./Core/Src/Menu.o \
./Core/Src/Object.o \
./Core/Src/PWM.o \
./Core/Src/Pin.o \
./Core/Src/PinController.o \
./Core/Src/SoftwareTimer.o \
./Core/Src/Task.o \
./Core/Src/d_debug.o \
./Core/Src/d_main.o \
./Core/Src/freertos.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/rtc.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_hal_timebase_tim.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/tim.o 

CPP_DEPS += \
./Core/Src/Clock.d \
./Core/Src/GPin.d \
./Core/Src/Gpio.d \
./Core/Src/Menu.d \
./Core/Src/Object.d \
./Core/Src/PWM.d \
./Core/Src/Pin.d \
./Core/Src/PinController.d \
./Core/Src/SoftwareTimer.d \
./Core/Src/Task.d \
./Core/Src/d_main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DconfigMESSAGE_BUFFER_LENGTH_TYPE=size_t -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Button.cyclo ./Core/Src/Button.d ./Core/Src/Button.o ./Core/Src/Button.su ./Core/Src/Clock.cyclo ./Core/Src/Clock.d ./Core/Src/Clock.o ./Core/Src/Clock.su ./Core/Src/GPin.cyclo ./Core/Src/GPin.d ./Core/Src/GPin.o ./Core/Src/GPin.su ./Core/Src/Gpio.cyclo ./Core/Src/Gpio.d ./Core/Src/Gpio.o ./Core/Src/Gpio.su ./Core/Src/Menu.cyclo ./Core/Src/Menu.d ./Core/Src/Menu.o ./Core/Src/Menu.su ./Core/Src/Object.cyclo ./Core/Src/Object.d ./Core/Src/Object.o ./Core/Src/Object.su ./Core/Src/PWM.cyclo ./Core/Src/PWM.d ./Core/Src/PWM.o ./Core/Src/PWM.su ./Core/Src/Pin.cyclo ./Core/Src/Pin.d ./Core/Src/Pin.o ./Core/Src/Pin.su ./Core/Src/PinController.cyclo ./Core/Src/PinController.d ./Core/Src/PinController.o ./Core/Src/PinController.su ./Core/Src/SoftwareTimer.cyclo ./Core/Src/SoftwareTimer.d ./Core/Src/SoftwareTimer.o ./Core/Src/SoftwareTimer.su ./Core/Src/Task.cyclo ./Core/Src/Task.d ./Core/Src/Task.o ./Core/Src/Task.su ./Core/Src/d_debug.cyclo ./Core/Src/d_debug.d ./Core/Src/d_debug.o ./Core/Src/d_debug.su ./Core/Src/d_main.cyclo ./Core/Src/d_main.d ./Core/Src/d_main.o ./Core/Src/d_main.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/rtc.cyclo ./Core/Src/rtc.d ./Core/Src/rtc.o ./Core/Src/rtc.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_hal_timebase_tim.cyclo ./Core/Src/stm32f1xx_hal_timebase_tim.d ./Core/Src/stm32f1xx_hal_timebase_tim.o ./Core/Src/stm32f1xx_hal_timebase_tim.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su

.PHONY: clean-Core-2f-Src

