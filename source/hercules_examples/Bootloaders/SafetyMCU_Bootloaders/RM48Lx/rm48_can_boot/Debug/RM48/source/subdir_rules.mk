################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
RM48/source/can.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/can.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/dabort.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/dabort.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/dcc.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/dcc.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/emac.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/emac.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/errata_SSWF021_45.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/errata_SSWF021_45.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/esm.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/esm.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/gio.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/gio.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/mdio.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/mdio.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/notification.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/notification.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/phy_dp83640.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/phy_dp83640.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/pinmux.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/pinmux.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/rti.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/rti.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/sci.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sci.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/spi.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/spi.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/sys_core.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_core.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/sys_dma.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_dma.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/sys_intvecs.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_intvecs.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/sys_mpu.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_mpu.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/sys_pcr.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_pcr.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/sys_phantom.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_phantom.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/sys_pmm.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_pmm.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/sys_pmu.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_pmu.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/sys_selftest.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_selftest.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/sys_startup.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_startup.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/sys_vim.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_vim.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RM48/source/system.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/source/system.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -Ooff --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/rm48_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/RM48Lx/" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/RM48/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="RM48/source/$(basename $(<F)).d_raw" --obj_directory="RM48/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


