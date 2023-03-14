################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../src/sys_core.asm \
../src/sys_intvecs.asm \
../src/sys_memory.asm \
../src/sys_mpu.asm \
../src/sys_pmu.asm 

C_SRCS += \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/dlog/src/float32/hercules/DLOG.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/adc/adc_bldc/src/32b/hercules/champion/adc.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/src/drv.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/ecmp/src/float32/champion/ecmp.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/pwm/pwm_bldc/src/32b/hercules/champion/epwm.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/esm/src/32b/hercules/champion/esm.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion/gio.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/src/gui.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/impulse/src/float32/hercules/impulse.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/mod6/src/float32/hercules/mod6_cnt.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/pid/src/float32/hercules/pid.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/pinmux/src/32b/hercules/champion/pinmux.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/rmp3/src/float32/hercules/rmp3cntl.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/rmpcntl/src/float32/hercules/rmp_cntl.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/rti/src/32b/hercules/champion/rti.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/rtp/src/32b/hercules/champion/rtp.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/sci/src/32b/hercules/champion/sci.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/speed_pr/src/float32/hercules/speed_pr.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/spi/src/32b/hercules/champion/spi.c \
../src/sys_phantom.c \
../src/sys_startup.c \
../src/system.c 

C_DEPS += \
./src/DLOG.d \
./src/adc.d \
./src/drv.d \
./src/ecmp.d \
./src/epwm.d \
./src/esm.d \
./src/gio.d \
./src/gui.d \
./src/impulse.d \
./src/mod6_cnt.d \
./src/pid.d \
./src/pinmux.d \
./src/rmp3cntl.d \
./src/rmp_cntl.d \
./src/rti.d \
./src/rtp.d \
./src/sci.d \
./src/speed_pr.d \
./src/spi.d \
./src/sys_phantom.d \
./src/sys_startup.d \
./src/system.d 

OBJS += \
./src/DLOG.obj \
./src/adc.obj \
./src/drv.obj \
./src/ecmp.obj \
./src/epwm.obj \
./src/esm.obj \
./src/gio.obj \
./src/gui.obj \
./src/impulse.obj \
./src/mod6_cnt.obj \
./src/pid.obj \
./src/pinmux.obj \
./src/rmp3cntl.obj \
./src/rmp_cntl.obj \
./src/rti.obj \
./src/rtp.obj \
./src/sci.obj \
./src/speed_pr.obj \
./src/spi.obj \
./src/sys_core.obj \
./src/sys_intvecs.obj \
./src/sys_memory.obj \
./src/sys_mpu.obj \
./src/sys_phantom.obj \
./src/sys_pmu.obj \
./src/sys_startup.obj \
./src/system.obj 

ASM_DEPS += \
./src/sys_core.d \
./src/sys_intvecs.d \
./src/sys_memory.d \
./src/sys_mpu.d \
./src/sys_pmu.d 

OBJS__QUOTED += \
"src\DLOG.obj" \
"src\adc.obj" \
"src\drv.obj" \
"src\ecmp.obj" \
"src\epwm.obj" \
"src\esm.obj" \
"src\gio.obj" \
"src\gui.obj" \
"src\impulse.obj" \
"src\mod6_cnt.obj" \
"src\pid.obj" \
"src\pinmux.obj" \
"src\rmp3cntl.obj" \
"src\rmp_cntl.obj" \
"src\rti.obj" \
"src\rtp.obj" \
"src\sci.obj" \
"src\speed_pr.obj" \
"src\spi.obj" \
"src\sys_core.obj" \
"src\sys_intvecs.obj" \
"src\sys_memory.obj" \
"src\sys_mpu.obj" \
"src\sys_phantom.obj" \
"src\sys_pmu.obj" \
"src\sys_startup.obj" \
"src\system.obj" 

C_DEPS__QUOTED += \
"src\DLOG.d" \
"src\adc.d" \
"src\drv.d" \
"src\ecmp.d" \
"src\epwm.d" \
"src\esm.d" \
"src\gio.d" \
"src\gui.d" \
"src\impulse.d" \
"src\mod6_cnt.d" \
"src\pid.d" \
"src\pinmux.d" \
"src\rmp3cntl.d" \
"src\rmp_cntl.d" \
"src\rti.d" \
"src\rtp.d" \
"src\sci.d" \
"src\speed_pr.d" \
"src\spi.d" \
"src\sys_phantom.d" \
"src\sys_startup.d" \
"src\system.d" 

ASM_DEPS__QUOTED += \
"src\sys_core.d" \
"src\sys_intvecs.d" \
"src\sys_memory.d" \
"src\sys_mpu.d" \
"src\sys_pmu.d" 

C_SRCS__QUOTED += \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/dlog/src/float32/hercules/DLOG.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/adc/adc_bldc/src/32b/hercules/champion/adc.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/pwm/pwm_bldc/src/32b/hercules/champion/epwm.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/esm/src/32b/hercules/champion/esm.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion/gio.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/instaspin_bldc/boards/drv8301kit_revD/hercules/src/gui.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/impulse/src/float32/hercules/impulse.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/mod6/src/float32/hercules/mod6_cnt.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/pid/src/float32/hercules/pid.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/pinmux/src/32b/hercules/champion/pinmux.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/rmp3/src/float32/hercules/rmp3cntl.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/rmpcntl/src/float32/hercules/rmp_cntl.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/rti/src/32b/hercules/champion/rti.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/rtp/src/32b/hercules/champion/rtp.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/sci/src/32b/hercules/champion/sci.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/speed_pr/src/float32/hercules/speed_pr.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/spi/src/32b/hercules/champion/spi.c" \
"../src/sys_phantom.c" \
"../src/sys_startup.c" \
"../src/system.c" 

ASM_SRCS__QUOTED += \
"../src/sys_core.asm" \
"../src/sys_intvecs.asm" \
"../src/sys_memory.asm" \
"../src/sys_mpu.asm" \
"../src/sys_pmu.asm" 


