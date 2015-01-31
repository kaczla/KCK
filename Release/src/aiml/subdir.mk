################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/aiml/aiml.cpp \
../src/aiml/aiml_parser.cpp \
../src/aiml/caiml_parser.cpp \
../src/aiml/config_parser.cpp \
../src/aiml/core.cpp \
../src/aiml/errors.cpp \
../src/aiml/graphmaster.cpp \
../src/aiml/javascript.cpp \
../src/aiml/serializer.cpp \
../src/aiml/stuff.cpp \
../src/aiml/template_parser.cpp \
../src/aiml/user.cpp \
../src/aiml/user_manager.cpp 

OBJS += \
./src/aiml/aiml.o \
./src/aiml/aiml_parser.o \
./src/aiml/caiml_parser.o \
./src/aiml/config_parser.o \
./src/aiml/core.o \
./src/aiml/errors.o \
./src/aiml/graphmaster.o \
./src/aiml/javascript.o \
./src/aiml/serializer.o \
./src/aiml/stuff.o \
./src/aiml/template_parser.o \
./src/aiml/user.o \
./src/aiml/user_manager.o 

CPP_DEPS += \
./src/aiml/aiml.d \
./src/aiml/aiml_parser.d \
./src/aiml/caiml_parser.d \
./src/aiml/config_parser.d \
./src/aiml/core.d \
./src/aiml/errors.d \
./src/aiml/graphmaster.d \
./src/aiml/javascript.d \
./src/aiml/serializer.d \
./src/aiml/stuff.d \
./src/aiml/template_parser.d \
./src/aiml/user.d \
./src/aiml/user_manager.d 


# Each subdirectory must supply rules for building sources it contributes
src/aiml/%.o: ../src/aiml/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


