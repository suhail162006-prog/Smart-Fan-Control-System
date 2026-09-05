# Smart-Fan-Control-System
Top-ranked coursework project (82/100),Embedded C++ climate control system using Arduino UNO, L293D motor driver, TMP36 temp sensor, and PIR motion detector. Integrates PWM fan speed modulation, non-blocking millis() state timing, and diode circuit protection.

Circuit simulation was carried out using TinkerCAD. The Arduino UNO acts as the central controller, where the PIR sensor is connected to pin 5 and the TMP36 sensor is connected to analogue pin A0. 
The L293D motor driver is supplied through the 12V battery through its VSS pin and from the 5V Arduino logic through the logic power pin. The enable pins 3&4EN is connected to the Arduino pin 6. The input pins IN3 and IN4 are connected to pins 3 & 4 respectively to control the motor direction. The DC motor is connected to the L293D output pins. T
The red LED is connected to Arduino pin 2 while the green LED to pin 8, both having a 220Ω resistors. 


All functional requirements were tested using simulation. The 12V power source was checked using a multimeter. The reverse polarity 1N4007 diode drops the power supply to 11.7V and did not affect the performance of the motor and logic during testing. 

The temperatures that trigger transitions between different motor speeds are sharply defined and correct. The motor speeds at PWM = 64, 128 and 255 can be easily distinguished and related to the temperatures 10-25°C,25-30°C and >30°C. Below 10°C the fan correctly remained off despite the motion being detected. The green LED worked perfectly in all fan-on states and the red LED in all the fan-off states. The millis() timeout function consistently delays the ON state of the fan after motion is lost during its 15-second countdown. Whenever motion is detected again, the timer gets reset and the motor (fan) switches back on if the temperature is within the ON range.  

In summary, the system performed as expected under all test conditions and all control logic, power supply design and circuit behaviour matched the specification outlined in the brief  
