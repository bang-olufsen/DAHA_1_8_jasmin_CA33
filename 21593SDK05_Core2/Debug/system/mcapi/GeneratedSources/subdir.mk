################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/mcapi/GeneratedSources/mcapi_config.c 

C_DEPS += \
./system/mcapi/GeneratedSources/mcapi_config.d 

SRC_OBJS += \
./system/mcapi/GeneratedSources/mcapi_config.doj 


# Each subdirectory must supply rules for building sources it contributes
system/mcapi/GeneratedSources/mcapi_config.doj: ../system/mcapi/GeneratedSources/mcapi_config.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core2" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE2 -D_DEBUG -DADI_MCAPI @includes-efd3b9430eddd4d39cab6f6e778ac023.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "system/mcapi/GeneratedSources/mcapi_config.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


