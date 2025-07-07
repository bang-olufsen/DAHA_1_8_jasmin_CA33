################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := ${ComSpec}

-include ../makefile.init

RM := clean

# All of the sources participating in the build are defined here
-include sources.mk
-include system/startup_ldf/subdir.mk
-include system/mcapi/GeneratedSources/subdir.mk
-include system/subdir.mk
-include src/System/Framework/subdir.mk
-include services/pdma/subdir.mk
-include services/int/subdir.mk
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
DXE += \
21593SDK05_Core2.dxe \

LINKER_LOG_OUTPUTS += \
linker_log.xml \

DEVICE_PROGRAMMER_OUTPUTS += \
program_device \

OBJS := $(SRC_OBJS)
# Quote makefile variable : OBJS 
OBJS := $(subst \ ,@, $(OBJS))
OBJS := $(foreach var, $(OBJS), "$(subst @, ,$(var))")
# Quote makefile variable : C_UPPER_DEPS 
C_UPPER_DEPS := $(subst \ ,@, $(C_UPPER_DEPS))
C_UPPER_DEPS := $(foreach var, $(C_UPPER_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : S_DEPS 
S_DEPS := $(subst \ ,@, $(S_DEPS))
S_DEPS := $(foreach var, $(S_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : C_DEPS 
C_DEPS := $(subst \ ,@, $(C_DEPS))
C_DEPS := $(foreach var, $(C_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : DSP_DEPS 
DSP_DEPS := $(subst \ ,@, $(DSP_DEPS))
DSP_DEPS := $(foreach var, $(DSP_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : CC_DEPS 
CC_DEPS := $(subst \ ,@, $(CC_DEPS))
CC_DEPS := $(foreach var, $(CC_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : C++_DEPS 
C++_DEPS := $(subst \ ,@, $(C++_DEPS))
C++_DEPS := $(foreach var, $(C++_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : CXX_DEPS 
CXX_DEPS := $(subst \ ,@, $(CXX_DEPS))
CXX_DEPS := $(foreach var, $(CXX_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : ASM_DEPS 
ASM_DEPS := $(subst \ ,@, $(ASM_DEPS))
ASM_DEPS := $(foreach var, $(ASM_DEPS), "$(subst @, ,$(var))")
# Quote makefile variable : CPP_DEPS 
CPP_DEPS := $(subst \ ,@, $(CPP_DEPS))
CPP_DEPS := $(foreach var, $(CPP_DEPS), "$(subst @, ,$(var))")
LDR += \
21593SDK05_Core2.ldr \


# All Target
all: 21593SDK05_Core2.ldr

# Tool invocations
21593SDK05_Core2.ldr: $(DXE) $(SRC_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: CrossCore SHARC Loader'
	elfloader -proc ADSP-21593 -si-revision any -bspimaster -fbinary -width 8 -bcode 1 -init "../../MAP_CCES_3_0_2/21593_init_Core1/Release/21593_init_Core1.dxe" -core1="../../21593SDK05_Core1/Debug/21593SDK05_Core1.dxe" -NoFinalTag="21593SDK05_Core1.dxe" -core2="../../21593SDK05_Core2/Debug/21593SDK05_Core2.dxe" -o "21593SDK05_Core2.ldr"
	@echo 'Finished building target: $@'
	@echo ' '

21593SDK05_Core2.dxe: $(LDF_SRCS) $(SRC_OBJS)
	@echo 'Invoking: CrossCore SHARC Linker'
	cc21k -proc ADSP-21593 -si-revision any -T C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core2/system/startup_ldf/21593SDK_Core2.ldf -no-mem -map 21593SDK05_Core2.map.xml -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core2/Debug/system/startup_ldf -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core2/Debug -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core2/Debug/src/System/Framework -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core2/Debug/services/int -L C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core2/Debug/services/pdma C:/Repo/DAHA_1_8_jasmin_CA33/21593SDK05_Core2/src/System/Framework/Init_Struct_Core2.doj -flags-link -MDCORE2,-MDOTHERCORE,-MDDEBUG -flags-link -i,"C:\Repo\DAHA_1_8_jasmin_CA33\21593SDK05_Core2\Customer_PP" -flags-link -i,"C:\Repo\DAHA_1_8_jasmin_CA33\21593SDK05_Core2\Debug\Customer_PP" -add-debug-libpaths -o 21593SDK05_Core2.dxe @input-file.txt
	@echo 'Finished building: $@'
	@echo ' '

linker_log.xml: 21593SDK05_Core2.dxe $(LDF_SRCS) $(SRC_OBJS)

program_device: $(LDR) $(SRC_OBJS)
	@echo 'Invoking: CrossCore SHARC Device Programmer'
	cldp -proc ADSP-21593 -cmd prog -erase affected -emu ice-2000 -format bin -offset 0x0 -core 0  -file "21593SDK05_Core2.ldr"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(LINKER_LOG_OUTPUTS) $(DEVICE_PROGRAMMER_OUTPUTS) $(C_UPPER_DEPS) $(S_DEPS) $(C_DEPS) $(DXE) $(DSP_DEPS) $(CC_DEPS) $(C++_DEPS) $(OBJS) $(CXX_DEPS) $(ASM_DEPS) $(LDR) $(CPP_DEPS)  21593SDK05_Core2.ldr
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
