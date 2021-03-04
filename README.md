# COVID-19-Automated-Screening-and-Sanitisation-Machine

This repository is dedicated to an ongoing project which involves developing an **Automated Thermal Screening and Sanitisation Machine** for the **COVID '19** situation around the world.
Regular project reports, new code files and added features would be updated, as any progress is made.

### Aim: 
To automate the *Temperature based Screening* Task for COVID ‘19 Screening.

### Current Features:
1.	Detects and alerts (through the Buzzer) whenever a person comes near the Entry Sensor, within 10cm to 20cm.
The attendance and instruction to stand within 10cm to 20cm will be displayed on the LCD.
2.	Measures his/her temperature using the Temperature Sensor only when it has already detected the person using Entry Sensor as mentioned in functionality point 1.
3.	If the temperature is measured to be above or equal to 37 degree Celsius, the “Buzzer” and the Red LED will turn on to indicate risk. The Buzzer and Red LED will remain active till the person moves away or is moved away to at least 200cm away (or 2 metres).
If the temperature measured is below 37 degrees Celsius, it will turn on the Green LED and continue to further stages of procedure, like sanitisation.
The temperature and further instructions will be displayed on the LCD.
4.	It will spray sanitiser, simulated by the movement of the Servo Motor whenever the hand is detected at less that 10cm from the Sanitization Sensor.
5.	All relevant information will be displayed on the Serial Monitor and LCD.
6.	The entry counting and exit counting will be done independently by sensors Entry Sensor and Exit Sensor respectively to ensure more efficient attendance logging.


