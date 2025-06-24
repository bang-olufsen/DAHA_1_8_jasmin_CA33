################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/analog/cces/3.0.2/SHARC/lib/src/services/Source/int/adi_int.c \
C:/analog/cces/3.0.2/SHARC/lib/src/services/Source/int/adi_sec.c 

SRC_OBJS += \
./system/services/int/adi_int.doj \
./system/services/int/adi_sec.doj 

C_DEPS += \
./system/services/int/adi_int.d \
./system/services/int/adi_sec.d 


# Each subdirectory must supply rules for building sources it contributes
system/services/int/adi_int.doj: C:/analog/cces/3.0.2/SHARC/lib/src/services/Source/int/adi_int.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-69cc20d3fa6495fa367c04bbc7ade3f1.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "system/services/int/adi_int.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/services/int/adi_sec.doj: C:/analog/cces/3.0.2/SHARC/lib/src/services/Source/int/adi_sec.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-69cc20d3fa6495fa367c04bbc7ade3f1.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "system/services/int/adi_sec.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


