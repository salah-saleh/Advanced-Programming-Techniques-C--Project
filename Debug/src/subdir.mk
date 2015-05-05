################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BuildFactory.cpp \
../src/Building.cpp \
../src/ElemConst.cpp \
../src/Entity.cpp \
../src/FileIO.cpp \
../src/Simulation.cpp \
../src/StarCraft.cpp \
../src/Unit.cpp 

OBJS += \
./src/BuildFactory.o \
./src/Building.o \
./src/ElemConst.o \
./src/Entity.o \
./src/FileIO.o \
./src/Simulation.o \
./src/StarCraft.o \
./src/Unit.o 

CPP_DEPS += \
./src/BuildFactory.d \
./src/Building.d \
./src/ElemConst.d \
./src/Entity.d \
./src/FileIO.d \
./src/Simulation.d \
./src/StarCraft.d \
./src/Unit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


