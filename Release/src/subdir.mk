################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/KCK.cpp \
../src/anim.cpp \
../src/bot.cpp \
../src/game.cpp \
../src/img.cpp \
../src/init.cpp \
../src/log_game.cpp \
../src/map.cpp \
../src/settings.cpp \
../src/text.cpp 

OBJS += \
./src/KCK.o \
./src/anim.o \
./src/bot.o \
./src/game.o \
./src/img.o \
./src/init.o \
./src/log_game.o \
./src/map.o \
./src/settings.o \
./src/text.o 

CPP_DEPS += \
./src/KCK.d \
./src/anim.d \
./src/bot.d \
./src/game.d \
./src/img.d \
./src/init.d \
./src/log_game.d \
./src/map.d \
./src/settings.d \
./src/text.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


