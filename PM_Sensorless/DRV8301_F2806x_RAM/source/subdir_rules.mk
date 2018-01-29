################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
F2806x_CpuTimers.obj: ../source/F2806x_CpuTimers.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/bin/cl2000" -v28 -ml --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Program Files (x86)/Texas Instruments/ccsv7/tools/compiler/ti-cgt-c2000_16.9.6.LTS/include" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2806x/F2806x_headers" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2806x/IQmath" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2806x/v3.1" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2806x/v110/F2806x_common" --include_path="C:/Users/win10/workspace_v7/PM_Sensorless/include/F2806x/v110/F2806x_headers" --define="_DEBUG" --define="DRV8301" --define="LARGE_MODEL" --define="FLOATING_MATH" -g --printf_support=full --diag_warning=225 --quiet --preproc_with_compile --preproc_dependency="source/F2806x_CpuTimers.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


