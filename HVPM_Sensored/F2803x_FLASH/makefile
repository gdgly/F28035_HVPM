################################################################################
# Automatically-generated file. Do not edit!
################################################################################

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"../DSP2803x_Headers_nonBIOS.cmd" \
"./HVPM_Sensored.obj" \
"./HVPM_Sensored-DevInit_F2803x.obj" \
"./DSP2803x_GlobalVariableDefs.obj" \
"./DSP2803x_CodeStartBranch.obj" \
"./DLOG4CHC.obj" \
"./DSP2803x_usDelay.obj" \
"./DSP2803x_TempSensorConv.obj" \
"./DSP2803x_Spi.obj" \
"./DSP2803x_Sci.obj" \
"./DSP2803x_SWPrioritizedDefaultIsr.obj" \
"./DSP2803x_PieCtrl.obj" \
"./DSP2803x_OscComp.obj" \
"./DSP2803x_Lin.obj" \
"./DSP2803x_I2C.obj" \
"./DSP2803x_Gpio.obj" \
"./DSP2803x_EQep.obj" \
"./DSP2803x_EPwm.obj" \
"./DSP2803x_ECap.obj" \
"./DSP2803x_ECan.obj" \
"./DSP2803x_DisInt.obj" \
"./DSP2803x_DBGIER.obj" \
"./DSP2803x_CpuTimers.obj" \
"./DSP2803x_Comp.obj" \
"./DSP2803x_CSMPasswords.obj" \
"./DSP2803x_Adc.obj" \
-l"rts2800_ml.lib" \
"../F28035_FLASH_HVPM_Sensored.CMD" \
"../IQmath.lib" \

-include ../makefile.init

RM := DEL /F

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include source/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: HVPM_Sensored.out

# Tool invocations
HVPM_Sensored.out: $(GEN_CMDS) $(CMD_SRCS) $(CMD_UPPER_SRCS) $(LIB_SRCS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	$(shell echo --silicon_version=28 > ccsLinker.opt)
	$(shell echo -g >> ccsLinker.opt)
	$(shell echo --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" >> ccsLinker.opt)
	$(shell echo --quiet >> ccsLinker.opt)
	$(shell echo --diag_warning=225 >> ccsLinker.opt)
	$(shell echo --large_memory_model >> ccsLinker.opt)
	$(shell echo -z >> ccsLinker.opt)
	$(shell echo -m"HVPM_Sensored.map" >> ccsLinker.opt)
	$(shell echo --stack_size=0x380 >> ccsLinker.opt)
	$(shell echo --warn_sections >> ccsLinker.opt)
	$(shell echo -i"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" -i"C:/Users/win10/Documents/workspace4/HVPM_Sensored" >> ccsLinker.opt)
	$(shell echo --reread_libs >> ccsLinker.opt)
	$(shell echo --rom_model >> ccsLinker.opt)
	$(shell type ccsObjs.opt >> ccsLinker.opt)
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsLinker.opt -o "HVPM_Sensored.out"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C2000_EXECUTABLE_OUTPUTS__QTD) "HVPM_Sensored.out"
	-$(RM) ".\DSP2803x_Adc.obj" ".\DSP2803x_CSMPasswords.obj" ".\DSP2803x_Comp.obj" ".\DSP2803x_CpuTimers.obj" ".\DSP2803x_DBGIER.obj" ".\DSP2803x_DisInt.obj" ".\DSP2803x_ECan.obj" ".\DSP2803x_ECap.obj" ".\DSP2803x_EPwm.obj" ".\DSP2803x_EQep.obj" ".\DSP2803x_Gpio.obj" ".\DSP2803x_I2C.obj" ".\DSP2803x_Lin.obj" ".\DSP2803x_OscComp.obj" ".\DSP2803x_PieCtrl.obj" ".\DSP2803x_SWPrioritizedDefaultIsr.obj" ".\DSP2803x_Sci.obj" ".\DSP2803x_Spi.obj" ".\DSP2803x_TempSensorConv.obj" ".\DSP2803x_usDelay.obj" ".\DLOG4CHC.obj" ".\DSP2803x_CodeStartBranch.obj" ".\DSP2803x_GlobalVariableDefs.obj" ".\HVPM_Sensored-DevInit_F2803x.obj" ".\HVPM_Sensored.obj" 
	-$(RM) ".\source\DSP2803x_CSMPasswords.pp" ".\source\DSP2803x_DBGIER.pp" ".\source\DSP2803x_DisInt.pp" ".\source\DSP2803x_usDelay.pp" ".\DLOG4CHC.pp" ".\DSP2803x_CodeStartBranch.pp" ".\DSP2803x_usDelay.pp" 
	-$(RM) ".\source\DSP2803x_Adc.pp" ".\source\DSP2803x_Comp.pp" ".\source\DSP2803x_CpuTimers.pp" ".\source\DSP2803x_ECan.pp" ".\source\DSP2803x_ECap.pp" ".\source\DSP2803x_EPwm.pp" ".\source\DSP2803x_EQep.pp" ".\source\DSP2803x_Gpio.pp" ".\source\DSP2803x_I2C.pp" ".\source\DSP2803x_Lin.pp" ".\source\DSP2803x_OscComp.pp" ".\source\DSP2803x_PieCtrl.pp" ".\source\DSP2803x_SWPrioritizedDefaultIsr.pp" ".\source\DSP2803x_Sci.pp" ".\source\DSP2803x_Spi.pp" ".\source\DSP2803x_TempSensorConv.pp" ".\DSP2803x_GlobalVariableDefs.pp" ".\HVPM_Sensored-DevInit_F2803x.pp" ".\HVPM_Sensored.pp" 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
