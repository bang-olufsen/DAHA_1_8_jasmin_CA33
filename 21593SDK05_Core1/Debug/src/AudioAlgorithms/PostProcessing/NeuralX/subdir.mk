################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AudioAlgorithms/PostProcessing/NeuralX/NeuralX.c 

SRC_OBJS += \
./src/AudioAlgorithms/PostProcessing/NeuralX/NeuralX.doj 

C_DEPS += \
./src/AudioAlgorithms/PostProcessing/NeuralX/NeuralX.d 


# Each subdirectory must supply rules for building sources it contributes
src/AudioAlgorithms/PostProcessing/NeuralX/NeuralX.doj: ../src/AudioAlgorithms/PostProcessing/NeuralX/NeuralX.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-0e2f664e1d185cfc49eb9196736881a5.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "src/AudioAlgorithms/PostProcessing/NeuralX/NeuralX.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


