################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
sys_main.obj: ../sys_main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -O4 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/rm46l852/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CCS -g --no_inlining --diag_warning=225 --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="sys_main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


