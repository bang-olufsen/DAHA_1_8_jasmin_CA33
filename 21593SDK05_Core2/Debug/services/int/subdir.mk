################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/analog/cces/3.0.2/SHARC/lib/src/services/Source/int/adi_int.c 

C_DEPS += \
./services/int/adi_int.d 

SRC_OBJS += \
./services/int/adi_int.doj 


# Each subdirectory must supply rules for building sources it contributes
services/int/adi_int.doj: C:/analog/cces/3.0.2/SHARC/lib/src/services/Source/int/adi_int.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core2" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE2 -D_DEBUG -DADI_MCAPI @includes-597faf3a7a069a7cc8711af36196c1c6.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "services/int/adi_int.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


