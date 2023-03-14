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
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/adc/src/32b/hercules/champion/adc.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/clarke/src/float32/clarke.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/src/ctrl.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/src/drv.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/ecmp/src/float32/champion/ecmp.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/qep/src/32b/hercules/champion/enc.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/pwm/src/32b/hercules/champion/epwm.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/qep/src/32b/hercules/champion/eqep.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/esm/src/32b/hercules/champion/esm.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion/gio.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/src/gui.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/ipark/src/float32/ipark.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/park/src/float32/park.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/pid/src/float32/hercules/pid.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/pinmux/src/32b/hercules/champion/pinmux.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/rampgen/src/float32/rampgen.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/rmpcntl/src/float32/hercules/rmp_cntl.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/rti/src/32b/hercules/champion/rti.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/rtp/src/32b/hercules/champion/rtp.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/sci/src/32b/hercules/champion/sci.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/smopos/src/float32/smopos.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/speed_est/src/float32/speed_est.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/speed_fr/src/float32/speed_fr.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/spi/src/32b/hercules/champion/spi.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/svgen/src/float32/svgen.c \
../src/sys_phantom.c \
../src/sys_startup.c \
../src/system.c \
C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/voltcalc/src/float32/volt_calc.c 

C_DEPS += \
./src/DLOG.d \
./src/adc.d \
./src/clarke.d \
./src/ctrl.d \
./src/drv.d \
./src/ecmp.d \
./src/enc.d \
./src/epwm.d \
./src/eqep.d \
./src/esm.d \
./src/gio.d \
./src/gui.d \
./src/ipark.d \
./src/park.d \
./src/pid.d \
./src/pinmux.d \
./src/rampgen.d \
./src/rmp_cntl.d \
./src/rti.d \
./src/rtp.d \
./src/sci.d \
./src/smopos.d \
./src/speed_est.d \
./src/speed_fr.d \
./src/spi.d \
./src/svgen.d \
./src/sys_phantom.d \
./src/sys_startup.d \
./src/system.d \
./src/volt_calc.d 

OBJS += \
./src/DLOG.obj \
./src/adc.obj \
./src/clarke.obj \
./src/ctrl.obj \
./src/drv.obj \
./src/ecmp.obj \
./src/enc.obj \
./src/epwm.obj \
./src/eqep.obj \
./src/esm.obj \
./src/gio.obj \
./src/gui.obj \
./src/ipark.obj \
./src/park.obj \
./src/pid.obj \
./src/pinmux.obj \
./src/rampgen.obj \
./src/rmp_cntl.obj \
./src/rti.obj \
./src/rtp.obj \
./src/sci.obj \
./src/smopos.obj \
./src/speed_est.obj \
./src/speed_fr.obj \
./src/spi.obj \
./src/svgen.obj \
./src/sys_core.obj \
./src/sys_intvecs.obj \
./src/sys_memory.obj \
./src/sys_mpu.obj \
./src/sys_phantom.obj \
./src/sys_pmu.obj \
./src/sys_startup.obj \
./src/system.obj \
./src/volt_calc.obj 

ASM_DEPS += \
./src/sys_core.d \
./src/sys_intvecs.d \
./src/sys_memory.d \
./src/sys_mpu.d \
./src/sys_pmu.d 

OBJS__QUOTED += \
"src\DLOG.obj" \
"src\adc.obj" \
"src\clarke.obj" \
"src\ctrl.obj" \
"src\drv.obj" \
"src\ecmp.obj" \
"src\enc.obj" \
"src\epwm.obj" \
"src\eqep.obj" \
"src\esm.obj" \
"src\gio.obj" \
"src\gui.obj" \
"src\ipark.obj" \
"src\park.obj" \
"src\pid.obj" \
"src\pinmux.obj" \
"src\rampgen.obj" \
"src\rmp_cntl.obj" \
"src\rti.obj" \
"src\rtp.obj" \
"src\sci.obj" \
"src\smopos.obj" \
"src\speed_est.obj" \
"src\speed_fr.obj" \
"src\spi.obj" \
"src\svgen.obj" \
"src\sys_core.obj" \
"src\sys_intvecs.obj" \
"src\sys_memory.obj" \
"src\sys_mpu.obj" \
"src\sys_phantom.obj" \
"src\sys_pmu.obj" \
"src\sys_startup.obj" \
"src\system.obj" \
"src\volt_calc.obj" 

C_DEPS__QUOTED += \
"src\DLOG.d" \
"src\adc.d" \
"src\clarke.d" \
"src\ctrl.d" \
"src\drv.d" \
"src\ecmp.d" \
"src\enc.d" \
"src\epwm.d" \
"src\eqep.d" \
"src\esm.d" \
"src\gio.d" \
"src\gui.d" \
"src\ipark.d" \
"src\park.d" \
"src\pid.d" \
"src\pinmux.d" \
"src\rampgen.d" \
"src\rmp_cntl.d" \
"src\rti.d" \
"src\rtp.d" \
"src\sci.d" \
"src\smopos.d" \
"src\speed_est.d" \
"src\speed_fr.d" \
"src\spi.d" \
"src\svgen.d" \
"src\sys_phantom.d" \
"src\sys_startup.d" \
"src\system.d" \
"src\volt_calc.d" 

ASM_DEPS__QUOTED += \
"src\sys_core.d" \
"src\sys_intvecs.d" \
"src\sys_memory.d" \
"src\sys_mpu.d" \
"src\sys_pmu.d" 

C_SRCS__QUOTED += \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/dlog/src/float32/hercules/DLOG.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/adc/src/32b/hercules/champion/adc.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/clarke/src/float32/clarke.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/src/ctrl.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/qep/src/32b/hercules/champion/enc.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/pwm/src/32b/hercules/champion/epwm.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/qep/src/32b/hercules/champion/eqep.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/esm/src/32b/hercules/champion/esm.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/gio/src/32b/hercules/champion/gio.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/solutions/foc_encoder_speed/boards/drv8301kit_revD/hercules/src/gui.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/ipark/src/float32/ipark.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/park/src/float32/park.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/pid/src/float32/hercules/pid.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/pinmux/src/32b/hercules/champion/pinmux.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/rampgen/src/float32/rampgen.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/rmpcntl/src/float32/hercules/rmp_cntl.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/rti/src/32b/hercules/champion/rti.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/rtp/src/32b/hercules/champion/rtp.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/sci/src/32b/hercules/champion/sci.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/smopos/src/float32/smopos.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/speed_est/src/float32/speed_est.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/speed_fr/src/float32/speed_fr.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/drivers/spi/src/32b/hercules/champion/spi.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/svgen/src/float32/svgen.c" \
"../src/sys_phantom.c" \
"../src/sys_startup.c" \
"../src/system.c" \
"C:/ti/Hercules/MotorWare/v1.0.3.03/sw/modules/voltcalc/src/float32/volt_calc.c" 

ASM_SRCS__QUOTED += \
"../src/sys_core.asm" \
"../src/sys_intvecs.asm" \
"../src/sys_memory.asm" \
"../src/sys_mpu.asm" \
"../src/sys_pmu.asm" 


