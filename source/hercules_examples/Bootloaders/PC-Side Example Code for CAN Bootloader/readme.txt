This example VC++ project is developed using VC++ 2010 express.  

The example project under RM4x_canBootloader_Test only works for RM57 device.
To use this example for RM57 device, the macro "RM57" should be defined in can_bittest.c.
//#define RM44
//#define RM42
//#define RM46
//#define RM48
#define RM57

The example project under TMS570LS_canBootloader_Test works for TMS570LC4357 device too.
To use this example for TMS570LC43 device, the macro "TMS570LC43" should be defined in can_bittest.c.
//#define TMS470M
//#define TMS570LS04
//#define TMS570LS31
//#define TMS570LS12
#define TMS570LC43

The USB-CAN adaptor used in my test is from NI. Please install the driver for the USB-CAN adaptor you used.
