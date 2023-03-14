################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/dabort.asm \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_core.asm \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_intvecs.asm \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_mpu.asm \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_pmu.asm 

C_SRCS += \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/can.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/emac.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/errata_SSWF021_45.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/esm.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/gio.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/mdio.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/notification.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/phy_dp83640.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/pinmux.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/rti.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sci.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/spi.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_dma.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_pcr.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_phantom.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_pmm.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_selftest.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_startup.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_vim.c \
C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/system.c 

C_DEPS += \
./HALCoGen/source/can.d \
./HALCoGen/source/emac.d \
./HALCoGen/source/errata_SSWF021_45.d \
./HALCoGen/source/esm.d \
./HALCoGen/source/gio.d \
./HALCoGen/source/mdio.d \
./HALCoGen/source/notification.d \
./HALCoGen/source/phy_dp83640.d \
./HALCoGen/source/pinmux.d \
./HALCoGen/source/rti.d \
./HALCoGen/source/sci.d \
./HALCoGen/source/spi.d \
./HALCoGen/source/sys_dma.d \
./HALCoGen/source/sys_pcr.d \
./HALCoGen/source/sys_phantom.d \
./HALCoGen/source/sys_pmm.d \
./HALCoGen/source/sys_selftest.d \
./HALCoGen/source/sys_startup.d \
./HALCoGen/source/sys_vim.d \
./HALCoGen/source/system.d 

OBJS += \
./HALCoGen/source/can.obj \
./HALCoGen/source/dabort.obj \
./HALCoGen/source/emac.obj \
./HALCoGen/source/errata_SSWF021_45.obj \
./HALCoGen/source/esm.obj \
./HALCoGen/source/gio.obj \
./HALCoGen/source/mdio.obj \
./HALCoGen/source/notification.obj \
./HALCoGen/source/phy_dp83640.obj \
./HALCoGen/source/pinmux.obj \
./HALCoGen/source/rti.obj \
./HALCoGen/source/sci.obj \
./HALCoGen/source/spi.obj \
./HALCoGen/source/sys_core.obj \
./HALCoGen/source/sys_dma.obj \
./HALCoGen/source/sys_intvecs.obj \
./HALCoGen/source/sys_mpu.obj \
./HALCoGen/source/sys_pcr.obj \
./HALCoGen/source/sys_phantom.obj \
./HALCoGen/source/sys_pmm.obj \
./HALCoGen/source/sys_pmu.obj \
./HALCoGen/source/sys_selftest.obj \
./HALCoGen/source/sys_startup.obj \
./HALCoGen/source/sys_vim.obj \
./HALCoGen/source/system.obj 

ASM_DEPS += \
./HALCoGen/source/dabort.d \
./HALCoGen/source/sys_core.d \
./HALCoGen/source/sys_intvecs.d \
./HALCoGen/source/sys_mpu.d \
./HALCoGen/source/sys_pmu.d 

OBJS__QUOTED += \
"HALCoGen\source\can.obj" \
"HALCoGen\source\dabort.obj" \
"HALCoGen\source\emac.obj" \
"HALCoGen\source\errata_SSWF021_45.obj" \
"HALCoGen\source\esm.obj" \
"HALCoGen\source\gio.obj" \
"HALCoGen\source\mdio.obj" \
"HALCoGen\source\notification.obj" \
"HALCoGen\source\phy_dp83640.obj" \
"HALCoGen\source\pinmux.obj" \
"HALCoGen\source\rti.obj" \
"HALCoGen\source\sci.obj" \
"HALCoGen\source\spi.obj" \
"HALCoGen\source\sys_core.obj" \
"HALCoGen\source\sys_dma.obj" \
"HALCoGen\source\sys_intvecs.obj" \
"HALCoGen\source\sys_mpu.obj" \
"HALCoGen\source\sys_pcr.obj" \
"HALCoGen\source\sys_phantom.obj" \
"HALCoGen\source\sys_pmm.obj" \
"HALCoGen\source\sys_pmu.obj" \
"HALCoGen\source\sys_selftest.obj" \
"HALCoGen\source\sys_startup.obj" \
"HALCoGen\source\sys_vim.obj" \
"HALCoGen\source\system.obj" 

C_DEPS__QUOTED += \
"HALCoGen\source\can.d" \
"HALCoGen\source\emac.d" \
"HALCoGen\source\errata_SSWF021_45.d" \
"HALCoGen\source\esm.d" \
"HALCoGen\source\gio.d" \
"HALCoGen\source\mdio.d" \
"HALCoGen\source\notification.d" \
"HALCoGen\source\phy_dp83640.d" \
"HALCoGen\source\pinmux.d" \
"HALCoGen\source\rti.d" \
"HALCoGen\source\sci.d" \
"HALCoGen\source\spi.d" \
"HALCoGen\source\sys_dma.d" \
"HALCoGen\source\sys_pcr.d" \
"HALCoGen\source\sys_phantom.d" \
"HALCoGen\source\sys_pmm.d" \
"HALCoGen\source\sys_selftest.d" \
"HALCoGen\source\sys_startup.d" \
"HALCoGen\source\sys_vim.d" \
"HALCoGen\source\system.d" 

ASM_DEPS__QUOTED += \
"HALCoGen\source\dabort.d" \
"HALCoGen\source\sys_core.d" \
"HALCoGen\source\sys_intvecs.d" \
"HALCoGen\source\sys_mpu.d" \
"HALCoGen\source\sys_pmu.d" 

C_SRCS__QUOTED += \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/can.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/emac.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/errata_SSWF021_45.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/esm.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/gio.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/mdio.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/notification.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/phy_dp83640.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/pinmux.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/rti.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sci.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/spi.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_dma.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_pcr.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_phantom.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_pmm.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_selftest.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_startup.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_vim.c" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/system.c" 

ASM_SRCS__QUOTED += \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/dabort.asm" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_core.asm" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_intvecs.asm" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_mpu.asm" \
"C:/Users/a0324020/workspace_v9/SafetyMCU_Bootloaders/HALCoGen/RM48/source/sys_pmu.asm" 


