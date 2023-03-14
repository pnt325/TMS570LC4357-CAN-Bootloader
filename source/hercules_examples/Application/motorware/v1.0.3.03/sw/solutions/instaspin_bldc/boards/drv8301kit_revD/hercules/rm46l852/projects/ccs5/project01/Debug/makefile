################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./sys_main.obj" \
"./src/DLOG.obj" \
"./src/adc.obj" \
"./src/drv.obj" \
"./src/ecmp.obj" \
"./src/epwm.obj" \
"./src/esm.obj" \
"./src/gio.obj" \
"./src/gui.obj" \
"./src/impulse.obj" \
"./src/mod6_cnt.obj" \
"./src/pid.obj" \
"./src/pinmux.obj" \
"./src/rmp3cntl.obj" \
"./src/rmp_cntl.obj" \
"./src/rti.obj" \
"./src/rtp.obj" \
"./src/sci.obj" \
"./src/speed_pr.obj" \
"./src/spi.obj" \
"./src/sys_core.obj" \
"./src/sys_intvecs.obj" \
"./src/sys_memory.obj" \
"./src/sys_mpu.obj" \
"./src/sys_phantom.obj" \
"./src/sys_pmu.obj" \
"./src/sys_startup.obj" \
"./src/system.obj" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/instaspin_bldc/lib/float32/hercules/rm46l852/InstaSPIN_BLDC.lib" \
"../sys_link.cmd" \
$(GEN_CMDS__FLAG) \
-lrtsv7R4_T_le_v3D16_eabi.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/subdir_vars.mk
-include subdir_rules.mk
-include src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
RM46L852_instaspin_bldc.out \

EXE_OUTPUTS__QUOTED += \
"RM46L852_instaspin_bldc.out" \

BIN_OUTPUTS += \
RM46L852_instaspin_bldc.hex \

BIN_OUTPUTS__QUOTED += \
"RM46L852_instaspin_bldc.hex" \


# All Target
all: RM46L852_instaspin_bldc.out

# Tool invocations
RM46L852_instaspin_bldc.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 -me -O4 --opt_for_speed=5 --fp_mode=relaxed --define=CHAMPION --define=CCS -g --no_inlining --diag_warning=225 --display_error_number --enum_type=packed --abi=eabi -z -m"RM46L852_instaspin_bldc.map" --heap_size=0x800 --stack_size=0x1500 -i"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --reread_libs --warn_sections --xml_link_info="RM46L852_instaspin_bldc_linkInfo.xml" --rom_model -o "RM46L852_instaspin_bldc.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

RM46L852_instaspin_bldc.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armhex"  -o "RM46L852_instaspin_bldc.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "sys_main.obj" "src\DLOG.obj" "src\adc.obj" "src\drv.obj" "src\ecmp.obj" "src\epwm.obj" "src\esm.obj" "src\gio.obj" "src\gui.obj" "src\impulse.obj" "src\mod6_cnt.obj" "src\pid.obj" "src\pinmux.obj" "src\rmp3cntl.obj" "src\rmp_cntl.obj" "src\rti.obj" "src\rtp.obj" "src\sci.obj" "src\speed_pr.obj" "src\spi.obj" "src\sys_core.obj" "src\sys_intvecs.obj" "src\sys_memory.obj" "src\sys_mpu.obj" "src\sys_phantom.obj" "src\sys_pmu.obj" "src\sys_startup.obj" "src\system.obj" 
	-$(RM) "sys_main.d" "src\DLOG.d" "src\adc.d" "src\drv.d" "src\ecmp.d" "src\epwm.d" "src\esm.d" "src\gio.d" "src\gui.d" "src\impulse.d" "src\mod6_cnt.d" "src\pid.d" "src\pinmux.d" "src\rmp3cntl.d" "src\rmp_cntl.d" "src\rti.d" "src\rtp.d" "src\sci.d" "src\speed_pr.d" "src\spi.d" "src\sys_phantom.d" "src\sys_startup.d" "src\system.d" 
	-$(RM) "src\sys_core.d" "src\sys_intvecs.d" "src\sys_memory.d" "src\sys_mpu.d" "src\sys_pmu.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

