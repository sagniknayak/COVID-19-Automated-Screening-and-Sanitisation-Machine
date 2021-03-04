#include <Servo.h>
#include <LiquidCrystal.h>

// initializing the library of LCD with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// initializing the library of servo
Servo servo;

// initializing sensor pins
int entry_sensor = A4;
int temp_Vin = 7;
int temp_Vout = A5;
int sanit_sensor = A3;
int servo_pin = A2;
int exit_sensor = A1;
int green_led = 9;
int red_led = 10;
int buzzer = 13;

// initializing maximum capacity
int max_cap = 10;

// initializing some variables used within the program
String mode = "step closer";
boolean flagPrint = true;
boolean left = false;
int skip = 0;
int attend = 0;
double val;
long long timer = 0;

void setup()
{
  servo.attach(servo_pin);      // attaching servo object to pin
  servo.write(0);
  lcd.begin(16, 2);         // starting functioning of LCD
  Serial.begin(9600);         // starting Serial
}

void loop()
{

  // segment for exiting attendance count
  if (attend > 0)
  {
    double exit = 0.01723 * readUltrasonicDistance(exit_sensor, exit_sensor);
    if (exit < 20)
    {
      attend--;         // decreasing attendance
      Serial.println("Attendance decreased");
      delay(2000);
    }
  }

  // segment when attendance is less than maximum capacity
  if (attend < max_cap)
  {

    // mode “step closer”
    if (mode == "step closer")
    {
      digitalWrite(green_led, LOW);
      digitalWrite(red_led, LOW);
      char c[] = "WELCOME! PLEASE STAND WITHIN 10 TO 20cm ";
      String s = "";
      for (int i = 0; i < 40; i++)
        s = s + c[(skip + i) % 40];
      lcd.setCursor(0, 0);
      lcd.print(s);
      lcd.setCursor(0, 1);
      lcd.print("Attendance: ");
      lcd.print(attend);
      lcd.print("  ");
      skip++;
      val = 0.01723 * readUltrasonicDistance(entry_sensor, entry_sensor);

      // if person is within 10cm to 20cm
      if (val > 10 && val < 20)
      {
        Serial.println("Person detected near entrance");
        timer = millis();
        left = true;
        tone(buzzer, 200);
        delay(50);
        tone(buzzer, 300);
        delay(50);
        noTone(buzzer);
        mode = "temp_check";    // changing mode to “temp check”
      }
    }

    // mode “temp check”
    else if (mode == "temp_check")
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CHECKING TEMP.");
      lcd.setCursor(0, 1);
      lcd.print("PLEASE WAIT ");
      Serial.println("Checking Temperature");
      digitalWrite(temp_Vin, HIGH);
      delay(2000);
      int reading = analogRead(temp_Vout);
      float voltage = reading * 5.0;
      voltage /= 1024.0;
      float temperatureC = (voltage - 0.5) * 100 ;
      lcd.clear();
      lcd.print("TEMPERATURE: ");
      lcd.print(temperatureC);
      lcd.print(" C");

      // when temperature is normal
      if (temperatureC < 37.0)
      {
        Serial.println("Temperature within limit");
        digitalWrite(green_led, HIGH);      // turning on Green LED
        lcd.setCursor(0, 1);
        lcd.print("PLEASE SANITISE YOUR HANDS");
        for (int i = 1; i <= 40; i++)
        {
          delay(200);
          lcd.scrollDisplayLeft();
        }
        mode = "sanitise";
        lcd.clear();
      }


      // when temperature is high
      else
      {
        Serial.println("Temperature above limit");
        digitalWrite(red_led, HIGH);        // turning on Red LED
        lcd.setCursor(0, 1);
        lcd.print("PLEASE CONSULT A DOCTOR!");
        double sens_val = 0.0;
        while (sens_val < 200)              // using buzzer to alert
        {
          tone(buzzer, 500);
          delay(200);
          tone(buzzer, 250);
          delay(200);
          lcd.scrollDisplayLeft();
          sens_val = 0.01723 * readUltrasonicDistance(entry_sensor, entry_sensor);
        }
        noTone(buzzer);
        mode = "step closer";        // changing mode to “step closer”
        lcd.clear();
      }
    }

    // mode “sanitise”
    else if (mode == "sanitise")
    {
      lcd.setCursor(0, 0);
      lcd.print("BRING YOUR HANDS");
      lcd.setCursor(0, 1);
      lcd.print("NEAR TO SANITISE");
      double sanit = 0.01723 * readUltrasonicDistance(sanit_sensor, sanit_sensor);

      // when hand is close to the sanitiser/sensor
      if (sanit < 10)
      {
        Serial.println("Hand detected near Sanitiser");
        mode = "pour sanit";      // changing mode to “pour sanit”
        lcd.clear();
      }
    }

    // mode “pour sanit”
    else if (mode == "pour sanit")
    {
      Serial.println("Pouring Sanitiser");
      lcd.setCursor(0, 0);
      lcd.print("   SANITISING   ");
      servo.write(120);
      delay(2000);
      servo.write(0);
      delay(1000);
      lcd.clear();
      mode = "enter";     // changing mode to “enter”
    }

    // mode “enter”
    else if (mode == "enter")
    {
      lcd.setCursor(0, 0);
      lcd.print("  PLEASE ENTER  ");
      lcd.setCursor(0, 1);
      lcd.print("    THE GATE    ");
      double entry = 0.01723 * readUltrasonicDistance(entry_sensor, entry_sensor);
      if (entry > 200)
      {
        Serial.println("Person entered the gate");
        Serial.println("Attendance increased");
        lcd.clear();
        attend++;       // increasing attendance
        mode = "step closer";   // changing mode to “step closer”
      }
    }

    // segment to handle timeout
    int tim_req = (millis() - timer) / 1000;
    Serial.println(tim_req);
    if (tim_req > 20 && left)
    {
      lcd.clear();
      Serial.println(tim_req);
      left = false;
      mode = "step closer";
    }
  }

  // segment when maximum capacity has reached
  else
  {
    Serial.println("Maximum Capacity reached");
    char c[] = "MAXIMUM CAPACITY REACHED    ";
    String s = "";
    for (int i = 0; i < 28; i++)
      s = s + c[(skip + i) % 28];
    skip++;
    lcd.setCursor(0, 0);
    lcd.print(s);
  }
  skip = skip % 50;
}

// function to use Ultrasonic Distance Sensor
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}
