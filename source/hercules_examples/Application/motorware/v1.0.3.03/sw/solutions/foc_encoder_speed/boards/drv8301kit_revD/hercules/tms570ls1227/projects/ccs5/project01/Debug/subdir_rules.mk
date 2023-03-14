################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
sys_main.obj: ../sys_main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="sys_main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


