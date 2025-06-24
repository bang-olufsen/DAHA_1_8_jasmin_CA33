################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
DOJ_SRCS += \
../src/System/Framework/Init_Struct_Core2.doj 

C_SRCS += \
../src/System/Framework/Decoder_Core2.c \
../src/System/Framework/Main_Core2.c \
../src/System/Framework/Word_Addressing_Core2.c 

C_DEPS += \
./src/System/Framework/Decoder_Core2.d \
./src/System/Framework/Main_Core2.d \
./src/System/Framework/Word_Addressing_Core2.d 

SRC_OBJS += \
./src/System/Framework/Decoder_Core2.doj \
./src/System/Framework/Main_Core2.doj \
./src/System/Framework/Word_Addressing_Core2.doj 


# Each subdirectory must supply rules for building sources it contributes
src/System/Framework/Decoder_Core2.doj: ../src/System/Framework/Decoder_Core2.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core2" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE2 -D_DEBUG -DADI_MCAPI @includes-597faf3a7a069a7cc8711af36196c1c6.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "src/System/Framework/Decoder_Core2.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/System/Framework/Main_Core2.doj: ../src/System/Framework/Main_Core2.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core2" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE2 -D_DEBUG -DADI_MCAPI @includes-597faf3a7a069a7cc8711af36196c1c6.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "src/System/Framework/Main_Core2.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/System/Framework/Word_Addressing_Core2.doj: ../src/System/Framework/Word_Addressing_Core2.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core2" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE2 -D_DEBUG -DADI_MCAPI @includes-597faf3a7a069a7cc8711af36196c1c6.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-32 -swc -gnu-style-dependencies -MD -Mo "src/System/Framework/Word_Addressing_Core2.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


