################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/analog/cces/3.0.2/SHARC/lib/src/services/Source/dma/adi_dma.c 

SRC_OBJS += \
./system/services/dma/adi_dma.doj 

C_DEPS += \
./system/services/dma/adi_dma.d 


# Each subdirectory must supply rules for building sources it contributes
system/services/dma/adi_dma.doj: C:/analog/cces/3.0.2/SHARC/lib/src/services/Source/dma/adi_dma.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-69cc20d3fa6495fa367c04bbc7ade3f1.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "system/services/dma/adi_dma.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


