################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/Fapi_UserDefinedFunctions.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/Fapi_UserDefinedFunctions.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/bl_check.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/bl_check.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/bl_copySections2SRAM.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/bl_copySections2SRAM.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/bl_dcan.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/bl_dcan.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/bl_flash.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/bl_flash.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/bl_led_demo.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/bl_led_demo.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/bl_main.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/bl_main.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/bl_spi.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/bl_spi.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/bl_spi_packet.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/bl_spi_packet.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/bl_uart.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/bl_uart.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/bl_ymodem.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/bl_ymodem.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/sci_common.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/sci_common.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/sw_hw_ver.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/sw_hw_ver.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/ymodem_crc16.obj: C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/source/ymodem_crc16.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/TMS570LS04x/ls04_can_boot" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/include" --include_path="C:/ti/Hercules/F021 Flash API/02.01.01/include" --include_path="C:/Users/a0324020/workspace_v9_Bootloaders/SafetyMCU_Bootloaders/HALCoGen/TMS570LS04x/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


