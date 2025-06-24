################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../Customer_PP/Customerasm.asm 

C_SRCS += \
../Customer_PP/Customer_PP.c 

SRC_OBJS += \
./Customer_PP/Customer_PP.doj \
./Customer_PP/Customerasm.doj 

ASM_DEPS += \
./Customer_PP/Customerasm.d 

C_DEPS += \
./Customer_PP/Customer_PP.d 


# Each subdirectory must supply rules for building sources it contributes
Customer_PP/Customer_PP.doj: ../Customer_PP/Customer_PP.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-69cc20d3fa6495fa367c04bbc7ade3f1.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "Customer_PP/Customer_PP.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Customer_PP/Customerasm.doj: ../Customer_PP/Customerasm.asm
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC Assembler'
	easm21k -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -si-revision any -g -DCORE1 -D_DEBUG @includes-19ae9b2452fff97d40a72f28b3c26ffa.txt -swc -char-size-8 -gnu-style-dependencies -MM -Mo "Customer_PP/Customerasm.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


