################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel_ASM.asm 

C_SRCS += \
../src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel.c 

SRC_OBJS += \
./src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel.doj \
./src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel_ASM.doj 

ASM_DEPS += \
./src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel_ASM.d 

C_DEPS += \
./src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel.d 


# Each subdirectory must supply rules for building sources it contributes
src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel.doj: ../src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-0e2f664e1d185cfc49eb9196736881a5.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel_ASM.doj: ../src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel_ASM.asm
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC Assembler'
	easm21k -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -si-revision any -g -DCORE1 -D_DEBUG @includes-6b8e8063bf3f1c78e1c59eee6802bd41.txt -swc -char-size-8 -gnu-style-dependencies -MM -Mo "src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel_ASM.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


