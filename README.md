# COVID-19-Automated-Screening-and-Sanitisation-Machine

This repository is dedicated to an ongoing project which involves developing an **Automated Thermal Screening and Sanitisation Machine** for the **COVID '19** situation around the world.
Regular project reports, new code files and added features would be updated, as any progress is made.

## Aim: 
To automate the *Temperature based Screening* Task for COVID ‘19 Screening.

## Current Features:
1.	Detects and alerts (through the Buzzer) whenever a person comes near the Entry Sensor, within 10cm to 20cm.
The attendance and instruction to stand within 10cm to 20cm will be displayed on the LCD.
2.	Measures his/her temperature using the Temperature Sensor only when it has already detected the person using Entry Sensor as mentioned in functionality point 1.
3.	If the temperature is measured to be above or equal to 37 degree Celsius, the “Buzzer” and the Red LED will turn on to indicate risk. The Buzzer and Red LED will remain active till the person moves away or is moved away to at least 200cm away (or 2 metres).
If the temperature measured is below 37 degrees Celsius, it will turn on the Green LED and continue to further stages of procedure, like sanitisation.
The temperature and further instructions will be displayed on the LCD.
4.	It will spray sanitiser, simulated by the movement of the Servo Motor whenever the hand is detected at less that 10cm from the Sanitization Sensor.
5.	All relevant information will be displayed on the Serial Monitor and LCD.
6.	The entry counting and exit counting will be done independently by sensors Entry Sensor and Exit Sensor respectively to ensure more efficient attendance logging.

## Links:
- [TinkerCAD Project Link](https://www.tinkercad.com/things/fSV1rkQ0w65)
- [Simulation Video Link](https://drive.google.com/file/d/1ZoDRI-b_58xn7UNqeSQ-Vc3ylz5riV_m/view?usp=sharing)

## Innovative points about the project:
-	The sensor to count the people exiting is independent to the thermal screening and sanitisation process and can thus be placed on a different exit door, so it can count people exiting even if a person if going through the screening and sanitisation process at the entry point.
-	Going through the sanitisation stage is compulsory if a person wants to enter through the entry point, which should be the only path to enter.
-	A person must stand at least 200cm away (2m away, which is the norm) from the person currently going through the screening or sanitisation process, or else he won’t be checked and thus not given entry.
-	The project has a timeout feature. If the person leaves, after standing and measuring their temperature, or does not sanitise within 10 more second, then he/she must go through the entire process again or the next person will be checked after at least 10 seconds after the previous person’s temperature was measured. So, if a person leaves in the middle of the entire screening and sanitisation process, the system will go back to normal activity after sometime time automatically, hence, timeout.
-	LCD displays instructions clearly, so a person should understand what to do if the person feels confused.

## Scopes for improvement:
- [ ]	There is always a scope of improvement for sensors and thus, making a more efficient code could be possible. However, as the code is segmented properly, due to increased readability, improving the code will not be an issue.
- [ ]	A mechanism attached to the door can be integrated that will order the door to open and close accordingly and will also help counting attendance more effectively.
-	[ ] The temperature sensor available on TinkerCAD [TMP36] only measures its ambient temperature and thus body temperature of a person cannot be measured properly. So, a different sensor should be used which can measure temperature over a distance.
-	[ ] A camera and a pre-trained Machine Learning model can be implemented to detect if the person is wearing a mask or not and thus act accordingly. However, handling a camera and sending/receiving data to/from a Machine Learning model requires more computational power and connection to the internet and thus Arduino Uno R3 can’t be used. For such purposes, development boards like Raspberry Pi or Orange Pi, integrated with Pi Camera might be used, that would increase the cost of device but will provide significant performance boost and many more features could be integrated.
