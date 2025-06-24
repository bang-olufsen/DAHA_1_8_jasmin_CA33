################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AudioAlgorithms/PostProcessing/AU_ENG/Kernal/AU_ENG_Kernal.c 

SRC_OBJS += \
./src/AudioAlgorithms/PostProcessing/AU_ENG/Kernal/AU_ENG_Kernal.doj 

C_DEPS += \
./src/AudioAlgorithms/PostProcessing/AU_ENG/Kernal/AU_ENG_Kernal.d 


# Each subdirectory must supply rules for building sources it contributes
src/AudioAlgorithms/PostProcessing/AU_ENG/Kernal/AU_ENG_Kernal.doj: ../src/AudioAlgorithms/PostProcessing/AU_ENG/Kernal/AU_ENG_Kernal.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-0e2f664e1d185cfc49eb9196736881a5.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "src/AudioAlgorithms/PostProcessing/AU_ENG/Kernal/AU_ENG_Kernal.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


