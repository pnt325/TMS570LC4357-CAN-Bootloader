################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/DLOG.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/dlog/src/float32/hercules/DLOG.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/DLOG.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/adc.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/adc/src/32b/hercules/champion/adc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/adc.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/clarke.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/clarke/src/float32/clarke.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/clarke.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/ctrl.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/src/ctrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/ctrl.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/drv.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/src/drv.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/drv.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/ecmp.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/ecmp/src/float32/champion/ecmp.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/ecmp.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/enc.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/qep/src/32b/hercules/champion/enc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/enc.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/epwm.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/pwm/src/32b/hercules/champion/epwm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/epwm.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/eqep.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/qep/src/32b/hercules/champion/eqep.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/eqep.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/esm.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/esm/src/32b/hercules/champion/esm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/esm.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/gio.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion/gio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/gio.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/gui.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/src/gui.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/gui.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/ipark.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/ipark/src/float32/ipark.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/ipark.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/park.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/park/src/float32/park.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/park.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/pid.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/pid/src/float32/hercules/pid.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/pid.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/pinmux.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/pinmux/src/32b/hercules/champion/pinmux.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/pinmux.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/rampgen.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/rampgen/src/float32/rampgen.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/rampgen.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/rmp_cntl.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/rmpcntl/src/float32/hercules/rmp_cntl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/rmp_cntl.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/rti.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/rti/src/32b/hercules/champion/rti.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/rti.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/rtp.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/rtp/src/32b/hercules/champion/rtp.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/rtp.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/sci.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/sci/src/32b/hercules/champion/sci.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/sci.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/smopos.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/smopos/src/float32/smopos.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/smopos.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/speed_est.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/speed_est/src/float32/speed_est.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/speed_est.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/speed_fr.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/speed_fr/src/float32/speed_fr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/speed_fr.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/spi.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/spi/src/32b/hercules/champion/spi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/spi.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/svgen.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/svgen/src/float32/svgen.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/svgen.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/sys_core.obj: ../src/sys_core.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/sys_core.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/sys_intvecs.obj: ../src/sys_intvecs.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/sys_intvecs.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/sys_memory.obj: ../src/sys_memory.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/sys_memory.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/sys_mpu.obj: ../src/sys_mpu.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/sys_mpu.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/sys_phantom.obj: ../src/sys_phantom.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/sys_phantom.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/sys_pmu.obj: ../src/sys_pmu.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/sys_pmu.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/sys_startup.obj: ../src/sys_startup.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/sys_startup.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/system.obj: ../src/system.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/system.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

src/volt_calc.obj: C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/voltcalc/src/float32/volt_calc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -O4 --opt_for_speed=5 --fp_mode=relaxed -g --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/tms570ls1227/projects/ccs5/project01/src" --include_path="C:/ti/Hercules/MotorWare/v1.0.3.03/sw/" --define=CHAMPION --define=CIMSIS --define=CCS --diag_warning=225 --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="src/volt_calc.d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


