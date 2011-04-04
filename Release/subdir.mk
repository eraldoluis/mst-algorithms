################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../disjointset.cpp \
../graph.cpp \
../kruskal.cpp \
../prim.cpp \
../test.cpp \
../test_heap.cpp 

OBJS += \
./disjointset.o \
./graph.o \
./kruskal.o \
./prim.o \
./test.o \
./test_heap.o 

CPP_DEPS += \
./disjointset.d \
./graph.d \
./kruskal.d \
./prim.d \
./test.d \
./test_heap.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


