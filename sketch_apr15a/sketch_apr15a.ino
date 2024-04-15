#include <LiquidCrystal.h>
// initialize the library by
// associating any needed LCD interface pin
// with the arduino pin number it is connected to

// Global Variables
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long previousMillis;
const unsigned long interval = 1000;  // 1 second

int hours, minutes, seconds;
int hours1, minutes1;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);  // 100ms timeout for serial input
  Serial.println("Set Time in hh:mm:ss format");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Set time in");
  lcd.setCursor(0, 1);
  lcd.print("hh:mm:ss format");
  delay(500);
  lcd.clear();
  pinMode(52, OUTPUT); // defining buzzer signal pins
  pinMode(53, OUTPUT);
  digitalWrite(52, HIGH); // defaulting them to off (*this can change depending on model of buzzer)
  digitalWrite(53, LOW);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // When previousMillis would be set to currentMillis,
    // then a delay in the code would delay the clock.
    // When previousMillis is incremented with 1 second,
    // then it stays synchronized.
    previousMillis += interval;  // increment with 1 second

    seconds += 1;
    if (seconds >= 60) {
      seconds = 0;
      minutes += 1;
    }
    if (minutes >= 60) {
      minutes = 0;
      hours += 1;
    }
    if (hours >= 24) {
      hours = 0;
    }

    // Update the time to the serial monitor and lcd!
    // The format is  hh:mm:ss.
    if (hours < 10) {
      Serial.print("0");
      lcd.setCursor(0, 1);
      lcd.print("0");
      lcd.setCursor(1, 1);
      lcd.print(hours);
      Serial.print(hours);
    } else {
      lcd.setCursor(0, 1);
      lcd.print(hours);
      Serial.print(hours);
    }
    lcd.setCursor(0, 1);
    Serial.print(":");
    lcd.setCursor(2, 1);
    lcd.print(":");
    if (minutes < 10) {
      Serial.print("0");
      lcd.setCursor(3, 1);
      lcd.print("0");
      lcd.setCursor(4, 1);
      lcd.print(minutes);
      Serial.print(minutes);
    } else {
      Serial.print(minutes);
      lcd.setCursor(3, 1);
      lcd.print(minutes);
    }
    Serial.print(":");
    lcd.setCursor(5, 1);
    lcd.print(":");
    if (seconds < 10) {
      Serial.print("0");
      lcd.setCursor(6, 1);
      lcd.print("0");
      lcd.setCursor(7, 1);
      lcd.print(seconds);
      Serial.print(seconds);
    } else {
      Serial.print(seconds);
      lcd.setCursor(6, 1);
      lcd.print(seconds);
    }
    Serial.println();
  }

  // Alarm Function!

  if (Serial.available() > 0) {
    String test = Serial.readString();

    //Serial.print(test);

    while ((test[0] == 'a') && (test[1] == 'l') && (test[2] == 'a') && (test[3] == 'r') && (test[4] == 'm')) { // see if the user is trying to set an alarm
      
      lcd.setCursor(0, 0);
      lcd.print("Set Alarm hh:mm");
      Serial.println("Set Alarm hh:mm");
          
      if (Serial.available() > 0) {
        String test1 = Serial.readString();
        Serial.println(test1);

        int h1 = (String(test1[0]) + String(test1[1])).toInt(); // defining all variables to their correct types
        char colon = test1[2];
        int m1 = (String(test1[3]) + String(test1[4])).toInt();
          
        if (colon == ':') { // makes sure values entered are valid
          hours1 = constrain(h1, 0, 23);
          minutes1 = constrain(m1, 0, 59);
          lcd.setCursor(0, 0);
          lcd.print("Alarm Set");
          break; // nessecary to get out of while loop
        }
      }
    }
    if (test[0] == '0' || '1' || '2') {
      int h = (String(test[0]) + String(test[1])).toInt(); // defining all variables to their correct types
      char colon1 = test[2];
      int m = (String(test[3]) + String(test[4])).toInt();
      char colon2 = test[5];
      int s = (String(test[6]) + String(test[7])).toInt();

      if (colon1 == ':' && colon2 == ':') {  // check for right format
        hours = constrain(h, 0, 23);
        minutes = constrain(m, 0, 59);
        seconds = constrain(s, 0, 59);
      }
    }
  }
  // Alarm goes off for one minute with no way to turn it off!
  if ((hours1 == hours) && (minutes1 == minutes) && (currentMillis > 60000)) { // so alarm does't go off right away (*alarm can never go off in less than a minute)
    digitalWrite(52, LOW);
    delayMicroseconds(500);
    digitalWrite(52, HIGH);
    delayMicroseconds(500);
    digitalWrite(53, HIGH);
    delayMicroseconds(500);
    digitalWrite(53, LOW);
    delayMicroseconds(500);
  }
}