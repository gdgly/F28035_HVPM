################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
DLOG4CHC.obj: ../DLOG4CHC.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" --silicon_version=28 -g --define="DRV8301" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/F2803x_headers" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/IQmath" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v124/DSP2803x_common" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v124/DSP2803x_headers" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v3.1" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --diag_warning=225 --large_memory_model --unified_memory --cla_support=cla0 --preproc_with_compile --preproc_dependency="DLOG4CHC.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

DRV8301_SPI.obj: ../DRV8301_SPI.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" --silicon_version=28 -g --define="DRV8301" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/F2803x_headers" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/IQmath" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v124/DSP2803x_common" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v124/DSP2803x_headers" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v3.1" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --diag_warning=225 --large_memory_model --unified_memory --cla_support=cla0 --preproc_with_compile --preproc_dependency="DRV8301_SPI.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

DSP2803x_GlobalVariableDefs.obj: ../DSP2803x_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" --silicon_version=28 -g --define="DRV8301" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/F2803x_headers" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/IQmath" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v124/DSP2803x_common" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v124/DSP2803x_headers" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v3.1" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --diag_warning=225 --large_memory_model --unified_memory --cla_support=cla0 --preproc_with_compile --preproc_dependency="DSP2803x_GlobalVariableDefs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

DSP2803x_usDelay.obj: ../DSP2803x_usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" --silicon_version=28 -g --define="DRV8301" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/F2803x_headers" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/IQmath" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v124/DSP2803x_common" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v124/DSP2803x_headers" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v3.1" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --diag_warning=225 --large_memory_model --unified_memory --cla_support=cla0 --preproc_with_compile --preproc_dependency="DSP2803x_usDelay.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

PM_Sensorless-DevInit_F2803x.obj: ../PM_Sensorless-DevInit_F2803x.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" --silicon_version=28 -g --define="DRV8301" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/F2803x_headers" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/IQmath" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v124/DSP2803x_common" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v124/DSP2803x_headers" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v3.1" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --diag_warning=225 --large_memory_model --unified_memory --cla_support=cla0 --preproc_with_compile --preproc_dependency="PM_Sensorless-DevInit_F2803x.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

PM_Sensorless.obj: ../PM_Sensorless.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" --silicon_version=28 -g --define="DRV8301" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/F2803x_headers" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/IQmath" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v124/DSP2803x_common" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v124/DSP2803x_headers" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2803x/v3.1" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --diag_warning=225 --large_memory_model --unified_memory --cla_support=cla0 --preproc_with_compile --preproc_dependency="PM_Sensorless.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


