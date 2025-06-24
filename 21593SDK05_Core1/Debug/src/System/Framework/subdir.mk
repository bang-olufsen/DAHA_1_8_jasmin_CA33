################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../src/System/Framework/SPI_ISR.asm 

DOJ_SRCS += \
../src/System/Framework/Autdet.doj \
../src/System/Framework/Decoder_Core1.doj \
../src/System/Framework/Downmix_norm.doj \
../src/System/Framework/Downsampling.doj \
../src/System/Framework/Init_Struct_Core1.doj \
../src/System/Framework/Init_Struct_Core1_Source.doj \
../src/System/Framework/Receiver_ISR.doj \
../src/System/Framework/SPI0_Func.doj \
../src/System/Framework/SPI1_Fun.doj \
../src/System/Framework/SPI1_Optical.doj \
../src/System/Framework/SPIRead.doj \
../src/System/Framework/SPI_Interrupts.doj \
../src/System/Framework/Spdif_Receiver.doj \
../src/System/Framework/Txmitter.doj \
../src/System/Framework/lib_fdiv.doj \
../src/System/Framework/lib_fdiv_simd.doj 

C_SRCS += \
../src/System/Framework/ConfigSoftSwitches_EV_21593_SOM.c \
../src/System/Framework/GPIO.c \
../src/System/Framework/Main_Core1.c \
../src/System/Framework/PostProcessing.c \
../src/System/Framework/System_Init.c \
../src/System/Framework/System_Modules.c \
../src/System/Framework/Tx_Rx_Handler.c \
../src/System/Framework/Word_Addressing_Core1.c 

SRC_OBJS += \
./src/System/Framework/ConfigSoftSwitches_EV_21593_SOM.doj \
./src/System/Framework/GPIO.doj \
./src/System/Framework/Main_Core1.doj \
./src/System/Framework/PostProcessing.doj \
./src/System/Framework/SPI_ISR.doj \
./src/System/Framework/System_Init.doj \
./src/System/Framework/System_Modules.doj \
./src/System/Framework/Tx_Rx_Handler.doj \
./src/System/Framework/Word_Addressing_Core1.doj 

ASM_DEPS += \
./src/System/Framework/SPI_ISR.d 

C_DEPS += \
./src/System/Framework/ConfigSoftSwitches_EV_21593_SOM.d \
./src/System/Framework/GPIO.d \
./src/System/Framework/Main_Core1.d \
./src/System/Framework/PostProcessing.d \
./src/System/Framework/System_Init.d \
./src/System/Framework/System_Modules.d \
./src/System/Framework/Tx_Rx_Handler.d \
./src/System/Framework/Word_Addressing_Core1.d 


# Each subdirectory must supply rules for building sources it contributes
src/System/Framework/ConfigSoftSwitches_EV_21593_SOM.doj: ../src/System/Framework/ConfigSoftSwitches_EV_21593_SOM.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-69cc20d3fa6495fa367c04bbc7ade3f1.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "src/System/Framework/ConfigSoftSwitches_EV_21593_SOM.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/System/Framework/GPIO.doj: ../src/System/Framework/GPIO.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-69cc20d3fa6495fa367c04bbc7ade3f1.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "src/System/Framework/GPIO.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/System/Framework/Main_Core1.doj: ../src/System/Framework/Main_Core1.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-69cc20d3fa6495fa367c04bbc7ade3f1.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "src/System/Framework/Main_Core1.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/System/Framework/PostProcessing.doj: ../src/System/Framework/PostProcessing.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-69cc20d3fa6495fa367c04bbc7ade3f1.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "src/System/Framework/PostProcessing.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/System/Framework/SPI_ISR.doj: ../src/System/Framework/SPI_ISR.asm
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC Assembler'
	easm21k -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -si-revision any -g -DCORE1 -D_DEBUG @includes-19ae9b2452fff97d40a72f28b3c26ffa.txt -swc -char-size-8 -gnu-style-dependencies -MM -Mo "src/System/Framework/SPI_ISR.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/System/Framework/System_Init.doj: ../src/System/Framework/System_Init.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-69cc20d3fa6495fa367c04bbc7ade3f1.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "src/System/Framework/System_Init.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/System/Framework/System_Modules.doj: ../src/System/Framework/System_Modules.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-69cc20d3fa6495fa367c04bbc7ade3f1.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "src/System/Framework/System_Modules.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/System/Framework/Tx_Rx_Handler.doj: ../src/System/Framework/Tx_Rx_Handler.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-69cc20d3fa6495fa367c04bbc7ade3f1.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -gnu-style-dependencies -MD -Mo "src/System/Framework/Tx_Rx_Handler.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/System/Framework/Word_Addressing_Core1.doj: ../src/System/Framework/Word_Addressing_Core1.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k -c -file-attr ProjectName="21593SDK05_Core1" -proc ADSP-21593 -flags-compiler --no_wrap_diagnostics -si-revision any -O -Ov100 -g -DCORE1 -D_DEBUG -DADI_DEBUG @includes-69cc20d3fa6495fa367c04bbc7ade3f1.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-32 -swc -gnu-style-dependencies -MD -Mo "src/System/Framework/Word_Addressing_Core1.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


