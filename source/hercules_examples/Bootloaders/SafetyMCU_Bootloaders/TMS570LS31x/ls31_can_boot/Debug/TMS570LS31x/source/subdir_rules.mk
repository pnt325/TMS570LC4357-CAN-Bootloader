################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
TMS570LS31x/source/can.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/can.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/dabort.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/dabort.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/dcc.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/dcc.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/emac.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/emac.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/errata_SSWF021_45.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/errata_SSWF021_45.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/esm.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/esm.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/gio.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/gio.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/mdio.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/mdio.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/notification.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/notification.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/phy_dp83640.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/phy_dp83640.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/pinmux.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/pinmux.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/rti.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/rti.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/sci.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/sci.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/spi.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/spi.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/sys_core.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/sys_core.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/sys_dma.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/sys_dma.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/sys_intvecs.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/sys_intvecs.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/sys_mpu.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/sys_mpu.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/sys_pcr.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/sys_pcr.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/sys_phantom.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/sys_phantom.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/sys_pmm.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/sys_pmm.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/sys_pmu.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/sys_pmu.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/sys_selftest.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/sys_selftest.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/sys_startup.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/sys_startup.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/sys_vim.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/sys_vim.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMS570LS31x/source/system.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/source/system.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS31x/ls31_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS31x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="TMS570LS31x/source/$(basename $(<F)).d_raw" --obj_directory="TMS570LS31x/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


