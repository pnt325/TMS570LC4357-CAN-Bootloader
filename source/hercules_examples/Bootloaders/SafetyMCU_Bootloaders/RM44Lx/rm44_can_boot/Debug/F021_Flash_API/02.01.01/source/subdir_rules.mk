################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
F021_Flash_API/02.01.01/source/Fapi_UserDefinedFunctions.obj: C:/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/source/Fapi_UserDefinedFunctions.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me --include_path="C:/ti/ccs900/ccs/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --include_path="C:/workspace_v9/SafetyMCU_Bootloaders/RM44Lx/rm44_can_boot" --include_path="C:/workspace_v9/SafetyMCU_Bootloaders/include" --include_path="C:/workspace_v9/SafetyMCU_Bootloaders/F021_Flash_API/02.01.01/include" --include_path="C:/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM44/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="F021_Flash_API/02.01.01/source/$(basename $(<F)).d_raw" --obj_directory="F021_Flash_API/02.01.01/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


