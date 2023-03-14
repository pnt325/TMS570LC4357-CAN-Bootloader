1. Required Software:
CCS9.x (Code Composer Studio) v9.0 or Later
Compiler: TI v18.12.1.LTS or Later
HALCoGen v. 4.07.01
Hercules SafeTI™ Diagnostic Library 2.40

2. Connecting LaunchPad to a Computer and Powering the LaunchPad
The LaunchPad is configured by default to be USB powered (JP6 must be shorted), which can be done by connecting the 
LaunchPad to a computer using a USB cable. 

3. Import the correct project into a CCS9.x Workspace
   a. Launch CCS 9.x
   b. From the Project Menu, select Import CCS Project.
   c. The Import CCS Eclipse Projects wizard opens.
   d. Check the 'Select Search-directory" button and then press "Browse" to find the project file: TMS570LC43x_LaunchPad_Project1

4. Opening a Terminal Program
To see the console output of the demo, open and configure the TERMINAL program of your choice (for example TeraTerm):
   a. Select COM port identified as "XDS Class Application/User UART" 
   b. Configure Baud Rate: 19200, Data Bits: 8, Stop Bits: 2 and Parity: None.
   
5. Linker ECC generation:
To avoid spectulative ECC error, the linker command is used to generate ECC for the whole flash (please refer to the linker 
cmd file). To enable linker to generate ECC, --ecc=on has to be added to the compiler option.
You have to change the CCS loader settings so that the loader doesn't generate ECC.
You can access these settings in your project properties, under the Debug category. Select "Flash Settings" as shown 
below and make sure:
   a. System Reset on Connect is checked
   b. Auto ECC Generation is unchecked
   c. Align program segments to 64-bit memory regions is checked
   d. Flash Verification Settings should be 'None'
   d. Perform Blank Check before Program Load must be unchecked
   e. Remember to Press "APPLY" or your changes will not be saved!
     
6. Running the Demos
This LaunchPad comes pre-programmed with a demo set that highlights several of MCU's safety features. 
When powered the LaunchPad will start blinking USER LEDs.

a. Demo 1: Potentiometer Demo
Potentiometer (U10) is connected to one of the MCU's Analog Inputs. USER LED B (LED3) blinks is controlled by the Potentiometer
settings. Turning the potentiometer will increase/decrease the speed at which USER LED B blinks.

b. Demo 2: CCMR5F Error Forcing Fault 
The push-button USER SWITCH B will inject a CCM core compare error (CPU mismatch). An on-chip monitor will detect 
the fault and trigger an error signal causing the ERR LED to light up.

c. Demo 3: FLASH ECC ERROR PROFILING TEST (1-bit ECC error)
The push-button USER SWITCH A will inject a single bit error in the MCU's flash on every push. ECC logic corrects 
single bit errors in flash and counts them. The USER LED A blinks faster with every error detected.

d. Demo 4: OSCILLATOR FAILURE
Pressing S5 (labeled Kill OSC) will short the Oscillator and cause the MCU to detect an Oscillator Fault. 
The on chip clock monitor will detect this and trigger the ERROR\ pin. The ERR LED in the top right corner of the 
LaunchPad will light up. You must press the PORRST pushbutton to recover from this condition and run the remaining demos.
