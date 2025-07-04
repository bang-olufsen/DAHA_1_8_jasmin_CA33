################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/analog/cces/3.0.2/SHARC/lib/src/services/Source/pcg/adi_pcg.c 

SRC_OBJS += \
./system/services/pcg/adi_pcg.doj 

C_DEPS += \
./system/services/pcg/adi_pcg.d 


# Each subdirectory must supply rules for building sources it contributes
system/services/pcg/adi_pcg.doj: C:/analog/cces/3.0.2/SHARC/lib/src/services/Source/pcg/adi_pcg.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-20c5ddc32ea027188962c6c2deb03d18.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "system/services/pcg/adi_pcg.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


