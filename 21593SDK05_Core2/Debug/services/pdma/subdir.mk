################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/analog/cces/3.0.2/SHARC/lib/src/services/Source/pdma/adi_pdma_2156x.c 

C_DEPS += \
./services/pdma/adi_pdma_2156x.d 

SRC_OBJS += \
./services/pdma/adi_pdma_2156x.doj 


# Each subdirectory must supply rules for building sources it contributes
services/pdma/adi_pdma_2156x.doj: C:/analog/cces/3.0.2/SHARC/lib/src/services/Source/pdma/adi_pdma_2156x.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core2" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE2 -D_DEBUG -DADI_MCAPI @includes-efd3b9430eddd4d39cab6f6e778ac023.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "services/pdma/adi_pdma_2156x.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


