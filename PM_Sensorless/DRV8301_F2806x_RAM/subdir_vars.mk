################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../F28069.cmd \
../F2806x_Headers_nonBIOS.cmd 

LIB_SRCS += \
../IQmath.lib \
../IQmath_fpu32.lib \
../rts2800_fpu32_fast_supplement.lib 

ASM_SRCS += \
../DLOG4CHC.asm \
../F2806x_CodeStartBranch.asm \
../F2806x_usDelay.asm 

C_SRCS += \
../DRV8301_SPI.c \
../F2806x_GlobalVariableDefs.c \
../PM_Sensorless-DevInit_F2806x.c \
../PM_Sensorless.c 

C_DEPS += \
./DRV8301_SPI.d \
./F2806x_GlobalVariableDefs.d \
./PM_Sensorless-DevInit_F2806x.d \
./PM_Sensorless.d 

OBJS += \
./DLOG4CHC.obj \
./DRV8301_SPI.obj \
./F2806x_CodeStartBranch.obj \
./F2806x_GlobalVariableDefs.obj \
./F2806x_usDelay.obj \
./PM_Sensorless-DevInit_F2806x.obj \
./PM_Sensorless.obj 

ASM_DEPS += \
./DLOG4CHC.d \
./F2806x_CodeStartBranch.d \
./F2806x_usDelay.d 

OBJS__QUOTED += \
"DLOG4CHC.obj" \
"DRV8301_SPI.obj" \
"F2806x_CodeStartBranch.obj" \
"F2806x_GlobalVariableDefs.obj" \
"F2806x_usDelay.obj" \
"PM_Sensorless-DevInit_F2806x.obj" \
"PM_Sensorless.obj" 

C_DEPS__QUOTED += \
"DRV8301_SPI.d" \
"F2806x_GlobalVariableDefs.d" \
"PM_Sensorless-DevInit_F2806x.d" \
"PM_Sensorless.d" 

ASM_DEPS__QUOTED += \
"DLOG4CHC.d" \
"F2806x_CodeStartBranch.d" \
"F2806x_usDelay.d" 

ASM_SRCS__QUOTED += \
"../DLOG4CHC.asm" \
"../F2806x_CodeStartBranch.asm" \
"../F2806x_usDelay.asm" 

C_SRCS__QUOTED += \
"../DRV8301_SPI.c" \
"../F2806x_GlobalVariableDefs.c" \
"../PM_Sensorless-DevInit_F2806x.c" \
"../PM_Sensorless.c" 


