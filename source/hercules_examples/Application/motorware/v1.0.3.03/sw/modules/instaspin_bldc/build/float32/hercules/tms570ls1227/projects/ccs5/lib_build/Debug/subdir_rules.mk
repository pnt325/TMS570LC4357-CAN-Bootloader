################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
InstaSPIN_BLDC.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/instaspin_bldc/src/float32/hercules/champion/InstaSPIN_BLDC.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -O4 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CCS -g --diag_warning=225 --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="InstaSPIN_BLDC.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


