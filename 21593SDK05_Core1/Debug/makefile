################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := ${ComSpec}

-include ../makefile.init

RM := clean

# All of the sources participating in the build are defined here
-include sources.mk
-include system/startup_ldf/subdir.mk
-include system/sru/subdir.mk
-include system/services/spu/subdir.mk
-include system/services/pwr/subdir.mk
-include system/services/pdma/subdir.mk
-include system/services/pcg/subdir.mk
-include system/services/int/subdir.mk
-include system/services/gpio/subdir.mk
-include system/services/dma/subdir.mk
-include system/services/dai/subdir.mk
-include system/pinmux/GeneratedSources/subdir.mk
-include system/drivers/twi/subdir.mk
-include system/drivers/sport/subdir.mk
-include system/drivers/spdif/subdir.mk
-include system/drivers/asrc/subdir.mk
-include system/subdir.mk
-include src/System/Framework/subdir.mk
-include src/AudioAlgorithms/Decoder/TRUEHD/subdir.mk
-include src/AudioAlgorithms/Decoder/Noisegen/subdir.mk
-include src/AudioAlgorithms/Decoder/MPEGH/source/subdir.mk
-include src/AudioAlgorithms/Decoder/MAT/subdir.mk
-include src/AudioAlgorithms/Decoder/DTSX/Kernel/subdir.mk
-include src/AudioAlgorithms/Decoder/DSD2PCM/Kernel/subdir.mk
-include src/AudioAlgorithms/Decoder/AAC/src/subdir.mk
-include Customer_PP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(DSP_DEPS)),)
-include $(DSP_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LINKER_LOG_OUTPUTS += \
linker_log.xml \

OBJS := $(SRC_OBJS)
# Quote makefile variable : OBJS 
OBJS := $(subst \ ,@, $(OBJS))
OBJS := $(foreach var, $(OBJS), "$(subst @, ,$(var))")
# Quote makefile variable : DSP_DEPS 
DSP_DEPS := $(subst \ ,@, $(DSP_DEPS))
DSP_DEPS := $(foreach var, $(DSP_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : CC_DEPS 
CC_DEPS := $(subst \ ,@, $(CC_DEPS))
CC_DEPS := $(foreach var, $(CC_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : C++_DEPS 
C++_DEPS := $(subst \ ,@, $(C++_DEPS))
C++_DEPS := $(foreach var, $(C++_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : C_UPPER_DEPS 
C_UPPER_DEPS := $(subst \ ,@, $(C_UPPER_DEPS))
C_UPPER_DEPS := $(foreach var, $(C_UPPER_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : CXX_DEPS 
CXX_DEPS := $(subst \ ,@, $(CXX_DEPS))
CXX_DEPS := $(foreach var, $(CXX_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : ASM_DEPS 
ASM_DEPS := $(subst \ ,@, $(ASM_DEPS))
ASM_DEPS := $(foreach var, $(ASM_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : S_DEPS 
S_DEPS := $(subst \ ,@, $(S_DEPS))
S_DEPS := $(foreach var, $(S_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : C_DEPS 
C_DEPS := $(subst \ ,@, $(C_DEPS))
C_DEPS := $(foreach var, $(C_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : CPP_DEPS 
CPP_DEPS := $(subst \ ,@, $(CPP_DEPS))
CPP_DEPS := $(foreach var, $(CPP_DEPS), "$(subst @, ,$(var))")

# All Target
all: 21593SDK05_Core1.dxe

# Tool invocations
21593SDK05_Core1.dxe: $(LDF_SRCS) $(SRC_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: CrossCore SHARC Linker'
	cc21k -proc ADSP-21593 -si-revision any -T C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/system/startup_ldf/21593SDK_Core1.ldf -no-mem -map 21593SDK05_Core1.map.xml -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/Debug/system/startup_ldf -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/Debug/system/drivers/asrc -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/Debug/system/drivers/sport -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/Debug/system/services/dai -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/Debug/system/services/dma -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/Debug/system/services/pcg -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/Debug/system/services/pdma -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/Debug/system/services/spu -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/Debug/system/startup_ldf -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/Debug/src/System/Framework -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/src -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/source -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DDPlus -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MAT -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/TRUEHD -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/DAP -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/DOWN_MIXER -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/OAR -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/AU_ENG/Kernal -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/AU_ENG -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DTSX/Kernel -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/DTSX/TruBass -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/NeuralX -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/DTS_VirtualX -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DSD2PCM/Kernel C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/Decoder_Core1.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/Spdif_Receiver.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/Autdet.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/SPI1_Fun.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/SPIRead.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/SPI1_Optical.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/SPI_Interrupts.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/Downsampling.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/Receiver_ISR.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/Txmitter.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/Init_Struct_Core1.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/Init_Struct_Core1_Source.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/Downmix_norm.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/lib_fdiv_simd.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/System/Framework/lib_fdiv.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libAACdec_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libArithCoding_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libCDK_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libDRCdec_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libFormatConverter_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libgVBAPRenderer_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libHOADec_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libIEC61937_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libIGFdec_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libMpegTPDec_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libPCMutils_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libSYS_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libTBEDec_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libTDlimit_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/Library/libUIManager_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MPEGH/source/MPEGH_Kernel.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/libAACdec_AAC.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/libArithCoding_AAC.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/libCDK_AAC.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/libDRCdec_AAC.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/libFormatConverter_AAC.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/libgVBAPRenderer_AAC.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/libMpegTPDec_AAC.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/libPCMdmx_AAC.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/libPCMutils_AAC.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/libSACdec_AAC.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/libSBRdec_AAC.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/libSYS_AAC.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/libTDlimit_AAC.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/src/AAC_Kernel.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/AAC/src/AAC_Transport_type_detect.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/Noisegen/Pink.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/ChanReOrder/ChanReOrder.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/Deemphasis/Deemphasis.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/DAP/Intrinsics_DDP_OAR_DAP_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DDPlus/DDP_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/Dolby_Decoder_Init.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/DOWN_MIXER/Dolby_Downmixer_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/DAP/DAP_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/OAR/OAR_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/OAR/OARI_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/TRUEHD/Intrinsics_THD_MAT_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MAT/MAT_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/TRUEHD/THD_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MAT/assert.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/MAT/MAT_Kernel.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/TRUEHD/Mat_Pcm.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/TRUEHD/mlpinit.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/TRUEHD/TrueHD_Kernel.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/DAP/DAP_Kernel.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/DOWN_MIXER/Downmixer_Kernel.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/OAR/OARI_Kernel.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/OAR/OARI_MD.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/AU_ENG/Kernal/AU_ENG_Kernal.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DTSX/Kernel/DTSX_Kernel_asm.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DTSX/Kernel/DTSX_Kernel.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DTSX/Kernel/DTSX_VX_Cmmn_asm.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DTSX/Kernel/DTSX_VX_Cmmn.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/DTSX/TruBass/TruBass_Kernel.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/NeuralX/NeuralX.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel_ASM.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/PostProcessing/DTS_VirtualX/DTSVX_Kernel.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DSD2PCM/Kernel/DSD2PCM_dec_lib_Core1.dlb C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DSD2PCM/Kernel/DSD2PCM_Kernel.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DSD2PCM/Kernel/DSD2PCM_KernelC.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DSD2PCM/Kernel/DSD2PCM_Passthrough.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DSD2PCM/Kernel/DSD2PCMKernel.doj C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core1/src/AudioAlgorithms/Decoder/DSD2PCM/Kernel/DSD2PCMKernelInit.doj -flags-link -MDCORE1,-MDDEBUG -add-debug-libpaths -o 21593SDK05_Core1.dxe @input-file.txt
	@echo 'Finished building target: $@'
	@echo ' '

linker_log.xml: 21593SDK05_Core1.dxe $(LDF_SRCS) $(SRC_OBJS)

# Other Targets
clean:
	-$(RM) $(DXE) $(DSP_DEPS) $(CC_DEPS) $(LINKER_LOG_OUTPUTS) $(C++_DEPS) $(OBJS) $(C_UPPER_DEPS) $(CXX_DEPS) $(ASM_DEPS) $(S_DEPS) $(C_DEPS) $(CPP_DEPS)  21593SDK05_Core1.dxe
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
