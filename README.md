# Digital-Tachometer
Contactless Digital Tachometer using STM32F103C8T6 development board
Software used:Keil u Vision
Hardware required:STM32F103C8T6 development board,16x2 lcd display,IR Sensor module,Jumper wires and breadboard.
code workflow and Functinality Overview:
Library Inclusions:
   - Includes STM32 and standard I/O libraries for microcontroller programming.

Function Prototypes:
   - Declares functions for delay, LCD commands, LCD data, LCD string display, and LCD initialization.

Delay Function:
   - Implements a delay function using the SysTick timer for creating delays in the code.

LCD Command and Data Functions:
   - Functions to send commands and data to the LCD display.

LCD String and Initialization Functions:
   - Functions to display strings on the LCD and initialize the LCD.

Main Function:
   - Variable declarations for tachometer readings, flags, and RPM storage.
   - Clock and GPIO initialization for the microcontroller.
   - Timer and GPIO configuration for the tachometer input.
   - Calls `lcd_init()` to initialize the LCD.
   - Enters a continuous loop for tachometer logic and RPM display.

Tachometer Logic:
   - Uses Timer 2 in input capture mode to measure the time between tachometer two consecutive pulses.
   - Calculates the period, frequency, and RPM based on timer readings.
   - Handles timer overflow by adding the number of overflows multiply by Auto reload register value to the second capture value and then subtract first captured value from it.

Notes and Suggestions:
   - Emphasizes the importance of accurate hardware connections.
   - Highlights the need for precise timing requirements and delay accuracy.
   - Encourages consulting the STM32 microcontroller reference manual for register configurations.

Understanding the hardware setup and STM32 peripheral configurations is essential for comprehending the complete functionality of the code. The workflow revolves around reading tachometer values, calculating RPM, and displaying the result on the LCD in a continuous loop.
