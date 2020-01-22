################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../index3.c \
../index4.c \
../search2.c \
../split.c \
../textread.c \
../translate.c \
../wts.c 

O_SRCS += \
../index3.o \
../index4.o \
../search2.o \
../split.o \
../textread.o \
../translate.o \
../wts.o 

OBJS += \
./index3.o \
./index4.o \
./search2.o \
./split.o \
./textread.o \
./translate.o \
./wts.o 

C_DEPS += \
./index3.d \
./index4.d \
./search2.d \
./split.d \
./textread.d \
./translate.d \
./wts.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


