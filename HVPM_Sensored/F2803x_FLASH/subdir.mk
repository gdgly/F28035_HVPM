################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_UPPER_SRCS += \
../F28035_FLASH_HVPM_Sensored.CMD 

LIB_SRCS += \
../IQmath.lib 

C_SRCS += \
../DSP2803x_GlobalVariableDefs.c \
../HVPM_Sensored-DevInit_F2803x.c \
../HVPM_Sensored.c 

ASM_SRCS += \
../DLOG4CHC.asm \
../DSP2803x_CodeStartBranch.asm \
../DSP2803x_usDelay.asm 

CMD_SRCS += \
../DSP2803x_Headers_nonBIOS.cmd 

ASM_DEPS += \
./DLOG4CHC.pp \
./DSP2803x_CodeStartBranch.pp \
./DSP2803x_usDelay.pp 

OBJS += \
./DLOG4CHC.obj \
./DSP2803x_CodeStartBranch.obj \
./DSP2803x_GlobalVariableDefs.obj \
./HVPM_Sensored-DevInit_F2803x.obj \
./HVPM_Sensored.obj 

C_DEPS += \
./DSP2803x_GlobalVariableDefs.pp \
./HVPM_Sensored-DevInit_F2803x.pp \
./HVPM_Sensored.pp 

OBJS__QTD += \
".\DLOG4CHC.obj" \
".\DSP2803x_CodeStartBranch.obj" \
".\DSP2803x_GlobalVariableDefs.obj" \
".\HVPM_Sensored-DevInit_F2803x.obj" \
".\HVPM_Sensored.obj" 

ASM_DEPS__QTD += \
".\DLOG4CHC.pp" \
".\DSP2803x_CodeStartBranch.pp" \
".\DSP2803x_usDelay.pp" 

C_DEPS__QTD += \
".\DSP2803x_GlobalVariableDefs.pp" \
".\HVPM_Sensored-DevInit_F2803x.pp" \
".\HVPM_Sensored.pp" 

ASM_SRCS_QUOTED += \
"../DLOG4CHC.asm" \
"../DSP2803x_CodeStartBranch.asm" \
"../DSP2803x_usDelay.asm" 

C_SRCS_QUOTED += \
"../DSP2803x_GlobalVariableDefs.c" \
"../HVPM_Sensored-DevInit_F2803x.c" \
"../HVPM_Sensored.c" 


# Each subdirectory must supply rules for building sources it contributes
./DLOG4CHC.obj: ../DLOG4CHC.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v15b/include" --include_path="C:/ti/controlSUITE/device_support/f2803x/v121/DSP2803x_headers/include" --include_path="C:/ti/controlSUITE/device_support/f2803x/v121/DSP2803x_common/include" --include_path="C:/ti/controlSUITE/development_kits/~SupportFiles/F2803x_headers" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/fixed_v1.1" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/drivers/f2803x_v1.2" --quiet --diag_warning=225 --large_memory_model --preproc_with_compile --preproc_dependency="DLOG4CHC.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2803x_CodeStartBranch.obj: ../DSP2803x_CodeStartBranch.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v15b/include" --include_path="C:/ti/controlSUITE/device_support/f2803x/v121/DSP2803x_headers/include" --include_path="C:/ti/controlSUITE/device_support/f2803x/v121/DSP2803x_common/include" --include_path="C:/ti/controlSUITE/development_kits/~SupportFiles/F2803x_headers" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/fixed_v1.1" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/drivers/f2803x_v1.2" --quiet --diag_warning=225 --large_memory_model --preproc_with_compile --preproc_dependency="DSP2803x_CodeStartBranch.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2803x_GlobalVariableDefs.obj: ../DSP2803x_GlobalVariableDefs.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v15b/include" --include_path="C:/ti/controlSUITE/device_support/f2803x/v121/DSP2803x_headers/include" --include_path="C:/ti/controlSUITE/device_support/f2803x/v121/DSP2803x_common/include" --include_path="C:/ti/controlSUITE/development_kits/~SupportFiles/F2803x_headers" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/fixed_v1.1" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/drivers/f2803x_v1.2" --quiet --diag_warning=225 --large_memory_model --preproc_with_compile --preproc_dependency="DSP2803x_GlobalVariableDefs.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2803x_usDelay.obj: ../DSP2803x_usDelay.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v15b/include" --include_path="C:/ti/controlSUITE/device_support/f2803x/v121/DSP2803x_headers/include" --include_path="C:/ti/controlSUITE/device_support/f2803x/v121/DSP2803x_common/include" --include_path="C:/ti/controlSUITE/development_kits/~SupportFiles/F2803x_headers" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/fixed_v1.1" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/drivers/f2803x_v1.2" --quiet --diag_warning=225 --large_memory_model --preproc_with_compile --preproc_dependency="DSP2803x_usDelay.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./HVPM_Sensored-DevInit_F2803x.obj: ../HVPM_Sensored-DevInit_F2803x.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v15b/include" --include_path="C:/ti/controlSUITE/device_support/f2803x/v121/DSP2803x_headers/include" --include_path="C:/ti/controlSUITE/device_support/f2803x/v121/DSP2803x_common/include" --include_path="C:/ti/controlSUITE/development_kits/~SupportFiles/F2803x_headers" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/fixed_v1.1" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/drivers/f2803x_v1.2" --quiet --diag_warning=225 --large_memory_model --preproc_with_compile --preproc_dependency="HVPM_Sensored-DevInit_F2803x.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./HVPM_Sensored.obj: ../HVPM_Sensored.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v15b/include" --include_path="C:/ti/controlSUITE/device_support/f2803x/v121/DSP2803x_headers/include" --include_path="C:/ti/controlSUITE/device_support/f2803x/v121/DSP2803x_common/include" --include_path="C:/ti/controlSUITE/development_kits/~SupportFiles/F2803x_headers" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/math_blocks/fixed_v1.1" --include_path="C:/ti/controlSUITE/libs/app_libs/motor_control/drivers/f2803x_v1.2" --quiet --diag_warning=225 --large_memory_model --preproc_with_compile --preproc_dependency="HVPM_Sensored.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


