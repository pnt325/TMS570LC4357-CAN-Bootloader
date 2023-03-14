################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
HALCoGen/RM42/source/adc.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/adc.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/can.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/can.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/dabort.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/dabort.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/dcc.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/dcc.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/errata_SSWF021_45.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/errata_SSWF021_45.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/esm.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/esm.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/gio.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/gio.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/het.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/het.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/lin.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/lin.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/mibspi.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/mibspi.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/notification.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/notification.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/pinmux.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/pinmux.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/rti.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/rti.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/sci.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/sci.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/spi.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/spi.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/sys_core.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/sys_core.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/sys_intvecs.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/sys_intvecs.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/sys_main.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/sys_main.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/sys_mpu.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/sys_mpu.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/sys_pcr.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/sys_pcr.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/sys_phantom.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/sys_phantom.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/sys_pmu.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/sys_pmu.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/sys_selftest.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/sys_selftest.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/sys_startup.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/sys_startup.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/sys_vim.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/sys_vim.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HALCoGen/RM42/source/system.obj: C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM42/source/system.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --preproc_with_compile --preproc_dependency="HALCoGen/RM42/source/$(basename $(<F)).d_raw" --obj_directory="HALCoGen/RM42/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


