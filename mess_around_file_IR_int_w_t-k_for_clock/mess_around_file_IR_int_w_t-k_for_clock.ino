// Use Flag variables for executions for IR_Remote
#include <DIYables_IRcontroller.h>  // DIYables_IRcontroller library
#include <LiquidCrystal.h>
#include "pitches.h"
#include <NewTone.h>
#define REST 0
#define BUZZER_PIN 9
#define IR_RECEIVER_PIN 7  // The Arduino pin connected to IR controller

DIYables_IRcontroller_21 irController(IR_RECEIVER_PIN, 200);  // debounce time is 200ms

//Global Variables
int pressed = 0;
String number_pressed;
int mode, mute = 0;
int hours, minutes, seconds;  // Global Variables for Hours, Minutes and seconds
int hours1, minutes1;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
unsigned long previousMillis;
unsigned long snoozeEndTime = 0;
const unsigned long interval = 1000;  // 1 second
String h1, h2, h4, h5, m1, m2, m4, m5, s1, s2;
int h3, h6, m3, m6, s3;
int count, count1 = 0;
bool alarm_off = false;
String cancel;
int snooze = 0;
bool stop_playing = 0;
int note;
int Red, Green, Blue;
int color;

// Rainbow color changing RGB leds example
// I am using common cathode RGB leds
int PIN_RED = 44;
int PIN_GREEN = 46;
int PIN_BLUE = 45;
int counter = 0;

// Number of colors used for animating, higher = smoother and slower animation)
int numColors = 255;

// The combination of numColors and animationDelay determines the
// animation speed, I recommend a higher number of colors if you want
// to slow down the animation. Higher number of colors = smoother color changing.
int animationDelay = 20;  // number milliseconds before RGB LED changes to next color                            (i changed this)

int melody[] = {
  NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5,
  NOTE_G5, REST, NOTE_G4, REST,
  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,
  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,

  REST, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_E5,
  REST, NOTE_GS4, NOTE_A4, NOTE_C4, REST, NOTE_A4, NOTE_C5, NOTE_D5,
  REST, NOTE_DS5, REST, NOTE_D5,
  NOTE_C5, REST,

  REST, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_E5,
  REST, NOTE_GS4, NOTE_A4, NOTE_C4, REST, NOTE_A4, NOTE_C5, NOTE_D5,
  REST, NOTE_DS5, REST, NOTE_D5,
  NOTE_C5, REST,

  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,

  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5, NOTE_E5,
  REST,
  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5,
  NOTE_G5, REST, NOTE_G4, REST,
  NOTE_C5, NOTE_G4, REST, NOTE_E4,

  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,

  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,

  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_D5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,

  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_B4, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5,
  NOTE_C5, NOTE_E4, NOTE_E4, NOTE_C4,

  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_D5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,

  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_B4, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5,
  NOTE_C5, NOTE_E4, NOTE_E4, NOTE_C4,
  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5, NOTE_E5,
  REST,

  NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5,
  NOTE_G5, REST, NOTE_G4, REST,
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_D5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,

  NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
  NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
  NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
  NOTE_B4, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5,
  NOTE_C5, NOTE_E4, NOTE_E4, NOTE_C4,

  // Game over sound
  NOTE_C5, NOTE_G4, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_AS4, NOTE_GS4,
  NOTE_G4, NOTE_D4, NOTE_E4
};

int durations[] = {
  8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4,
  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4, 8, 8, 4,
  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4, 8, 8, 4,


  4, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4,
  2, 2,

  4, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4,
  2, 2,

  8, 4, 8, 8, 8, 4,
  8, 4, 8, 2,

  8, 4, 8, 8, 8, 8, 8,
  1,
  8, 4, 8, 8, 8, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8, 4,
  4, 4, 4, 4,
  4, 8, 4, 4,

  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4, 8, 8, 4,

  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4, 8, 8, 4,

  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8,

  8, 4, 8, 2,
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 4, 8, 8, 8, 8,
  8, 4, 8, 2,

  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8,

  8, 4, 8, 2,
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 4, 8, 8, 8, 8,
  8, 4, 8, 2,
  8, 4, 8, 8, 8, 8, 8,
  1,

  8, 4, 8, 8, 8, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8, 4,
  4, 4, 4, 4,
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 8, 8, 8, 8, 8,

  8, 4, 8, 2,
  8, 4, 8, 4, 4,
  8, 4, 8, 2,
  8, 4, 8, 8, 8, 8,
  8, 4, 8, 2,

  //game over sound
  4, 4, 4,
  8, 8, 8, 8, 8, 8,
  8, 8, 2
};

void IRController() {  //Function for the IR controller used from libary.
  delay(10);           //Stability
  Key21 key = irController.getKey();
  if (key != Key21::NONE) {

    switch (key) {

      case Key21::KEY_CH_MINUS:
        Serial.println("CH-");
        break;

      case Key21::KEY_CH:
        Serial.println("CH");  // This is the mode button
        pressed = 1;
        mode = 1;
        cancel += "1";
        break;

      case Key21::KEY_CH_PLUS:
        // This is the mute button
        mute = 1;
        break;

      case Key21::KEY_PREV:
        //Serial.println(">||"); // this button will snooze for 5 mins! Setting alarm five minutes out!
        snooze = 1;
        break;

      case Key21::KEY_NEXT:
        Serial.println("<<");
        break;

      case Key21::KEY_PLAY_PAUSE:
        Serial.println(">>");
        break;

      case Key21::KEY_VOL_MINUS:
        Serial.println("EQ");
        break;

      case Key21::KEY_EQ:
        Serial.println("+");
        break;

      case Key21::KEY_VOL_PLUS:
        Serial.println("-");
        break;

      case Key21::KEY_100_PLUS:
        Serial.println("100+");
        break;

      case Key21::KEY_200_PLUS:
        Serial.println("200+");
        break;

      case Key21::KEY_0:
        //Serial.println("0");
        pressed = 1;
        number_pressed = "0";
        break;

      case Key21::KEY_1:
        //Serial.println("1");
        pressed = 1;
        number_pressed = "1";
        break;

      case Key21::KEY_2:
        //Serial.println("2");
        pressed = 1;
        number_pressed = "2";
        break;

      case Key21::KEY_3:
        //Serial.println("3");
        pressed = 1;
        number_pressed = "3";
        break;

      case Key21::KEY_4:
        //Serial.println("4");
        pressed = 1;
        number_pressed = "4";
        break;

      case Key21::KEY_5:
        //Serial.println("5");
        pressed = 1;
        number_pressed = "5";
        break;

      case Key21::KEY_6:
        //Serial.println("6");
        pressed = 1;
        number_pressed = "6";
        break;

      case Key21::KEY_7:
        //Serial.println("7");
        pressed = 1;
        number_pressed = "7";
        break;

      case Key21::KEY_8:
        //Serial.println("8");
        pressed = 1;
        number_pressed = "8";
        break;

      case Key21::KEY_9:
        //Serial.println("9");
        pressed = 1;
        number_pressed = "9";
        break;

      default:
        Serial.println("WARNING: undefined key:");
        break;
    }
  }
}

void Time_Increment_AND_LCD_Format() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // When previousMillis would be set to currentMillis,
    // then a delay in the code would delay the clock.
    // When previousMillis is incremented with 1 second,
    // then it stays synchronized.
    previousMillis += interval;  // increment with 1 second

    seconds += 1;         //Adding a second everytime the interval tracks that a second has occured. This is so there is no problems if there is a delay
    if (seconds >= 60) {  //If seconds get to 60 reset seconds to zero and increment minutes by 1.
      seconds = 0;
      minutes += 1;
    }
    if (minutes >= 60) {  //If minutes = 60 reset them to 0. Increase hours by 1.
      minutes = 0;
      hours += 1;
    }
    if (hours >= 24) {  //If hours = 24 reset them to zero.
      hours = 0;
    }

    // Update the time to the serial monitor and lcd!
    // The format is  hh:mm:ss.
    if (hours < 10) {
      //Serial.print("0");
      lcd.setCursor(0, 1);
      lcd.print("0");
      lcd.setCursor(1, 1);
      lcd.print(hours);
      //Serial.print(hours);
    } else {
      lcd.setCursor(0, 1);
      lcd.print(hours);
      //Serial.print(hours);
    }
    lcd.setCursor(0, 1);
    //Serial.print(":");
    lcd.setCursor(2, 1);
    lcd.print(":");
    if (minutes < 10) {
      //Serial.print("0");
      lcd.setCursor(3, 1);
      lcd.print("0");
      lcd.setCursor(4, 1);
      lcd.print(minutes);
      //Serial.print(minutes);
    } else {
      //Serial.print(minutes);
      lcd.setCursor(3, 1);
      lcd.print(minutes);
    }
    //Serial.print(":");
    lcd.setCursor(5, 1);
    lcd.print(":");
    if (seconds < 10) {
      //Serial.print("0");
      lcd.setCursor(6, 1);
      lcd.print("0");
      lcd.setCursor(7, 1);
      lcd.print(seconds);
      //Serial.print(seconds);
    } else {
      //Serial.print(seconds);
      lcd.setCursor(6, 1);
      lcd.print(seconds);
    }
    //Serial.println();
  }
}

void Alarm_Set() {

  while (mode == 1) {  // if mode button is pressed join the while loop.

    IRController();    // So it can work to set alarm
    lcd.setCursor(0, 0);
    lcd.println("Set Alarm hhmm");  // print set alarm in format hhmm
    alarm_off = false;              // make sure alarm can go off again

    if ((cancel >= "11")) {  // this allows canceling out of alarm set mode by pressing mode again
      cancel = "";
      mode = 0;
      lcd.clear();
      count1 = -1;  // nessecary to prevent setting first variable for time
      count = 0;    // I think this is needed to make the alarm not count up and store variables
      alarm_off = true; // so alarm can't go off after pressing the mute button (took so long to find this issue)
      lcd.setCursor(0, 0);
      lcd.print("timeset");
      break;
    }

    else if (pressed == 1) {  // if pressed == 1 (the else if I beleive is nessecary)
      pressed = 0;       // reset pressed = 0
      count += 1;  // increases the count by 1
      Serial.print("alarm count : ");
      Serial.println(count);
      lcd.clear();          // this is to clear the alarm each time a new one is set
      lcd.setCursor(2, 1);  // alarm set formating to inform user to what they entered as the alarm in real-time
      lcd.print(":");
      lcd.setCursor(5, 1);
      lcd.print(":");
      lcd.setCursor(6, 1);
      lcd.print("00");

      if (count == 2) {       // when the count = 2
        h1 = number_pressed;  // h1 = the first digit for the hours = the number pressed
        lcd.setCursor(0, 1);  // printing first digit of alarm set
        lcd.print(h1);
      }

      if (count == 3) {       // when the count = 3
        h2 = number_pressed;  // h2 = the second digit for hours = the number pressed
        lcd.setCursor(0, 1);  // printing first digit of alarm set
        lcd.print(h1);
        lcd.setCursor(1, 1);  // printing second digit of alarm set
        lcd.print(h2);
        h3 = (String(h1) + String(h2)).toInt();  // adds the two number inputed as strings and convert them to an integer.
      }

      if (count == 4) {       // when count = 4
        m1 = number_pressed;  // m1 = the number pressed. Stores as a varible
        lcd.setCursor(0, 1);  // printing first digit of alarm set
        lcd.print(h1);
        lcd.setCursor(1, 1);  // printing second digit of alarm set
        lcd.print(h2);
        lcd.setCursor(3, 1);  // printing thrid digit of alarm set
        lcd.print(m1);
        h1 = "";  // Resets h1 to an empty string.
        h2 = "";  // Resets h2 to an empty string.
      }

      if (count == 5) {       // when count = 5
        m2 = number_pressed;  // m2 = the number pressed. Stores as a varible
        lcd.setCursor(0, 1);  // printing first digit of alarm set
        lcd.print(h1);
        lcd.setCursor(1, 1);  // printing second digit of alarm set
        lcd.print(h2);
        lcd.setCursor(3, 1);  // printing thrid digit of alarm set
        lcd.print(m1);
        lcd.setCursor(4, 1);  // printing fourth digit of alarm set
        lcd.print(m2);
        m3 = (String(m1) + String(m2)).toInt();  // adds the two number inputed as strings and convert them to an integer
        m1 = "";                                 // resets to an empty string
        m2 = "";                                 // resets to an empty string
        hours1 = constrain(h3, 0, 23);           // constrains hours through 0-23. Reformats if out of constraints
        minutes1 = constrain(m3, 0, 59);         // constrains minutes through 0-23. Reformats if out of constraints
        lcd.setCursor(0, 0);
        lcd.print("Alarm Set");
        count = 0;    // reset count changed this from -1
        pressed = 0;  // reset pressed to zero
        mode = 0;     // reset mode to zero
        count1 = -1;  // nessecary to prevent setting time varaible one
        Serial.println();
        Serial.print("alarm hours : ");
        Serial.println(hours1);
        Serial.print("alarm minutes : ");
        Serial.println(minutes1);

        lcd.setCursor(9, 1);  // display set alarm to lcd
        lcd.print("h");
        lcd.setCursor(10, 1);
        lcd.print(hours1);
        lcd.setCursor(13, 1);
        lcd.print("m");
        lcd.setCursor(14, 1);
        lcd.print(minutes1);
        break;  // nessecary to get out of while loop
      }
    }
  }
}

void Time_Set() {
  // setting the clock time
  if (mode != 1) {  // add this in hopes that it will allow you to switch back a forth between modes with out storing variables
    count1 += 1;
    mode = 0;
  }
  Serial.print("set time count : ");
  Serial.println(count1);

  if (count1 == 1) {      // when a number is pressed
    h4 = number_pressed;  // set the hour 4 variable to number pressed
    lcd.setCursor(10, 0);
    lcd.print(":");
    lcd.setCursor(13, 0);
    lcd.print(":");
    lcd.setCursor(8, 0);  // printing first digit of time set
    lcd.print(h4);
  }

  if (count1 == 2) {                         // when a number pressed = 2
    h5 = number_pressed;                     // set the hour 5 variable to number pressed
    lcd.setCursor(8, 0);  // printing first digit of time set
    lcd.print(h4);
    lcd.setCursor(9, 0);  // printing second digit of time set
    lcd.print(h5);
    h6 = (String(h4) + String(h5)).toInt();  // adds the two number inputed as strings and convert them to an integer.
  }

  if (count1 == 3) {      //if count = 3
    m4 = number_pressed;  // minutes 4 = number pressed
    lcd.setCursor(8, 0);  // printing first digit of time set
    lcd.print(h4);
    lcd.setCursor(9, 0);  // printing second digit of time set
    lcd.print(h5);
    lcd.setCursor(11, 0); // printing third digit of time set
    lcd.print(m4);
    h4 = "";                                 // reset h4 to an empty string
    h5 = "";                                 // reset h5 to an empty string
  }

  if (count1 == 4) {                         // if count = 4
    m5 = number_pressed;                     // m5 = numbers pressed
    lcd.setCursor(8, 0);  // printing first digit of time set
    lcd.print(h4);
    lcd.setCursor(9, 0);  // printing second digit of time set
    lcd.print(h5);
    lcd.setCursor(11, 0); // printing third digit of time set
    lcd.print(m4);
    lcd.setCursor(12, 0); // printing third digit of time set
    lcd.print(m5);
    m6 = (String(m4) + String(m5)).toInt();  // adds the two number inputed as strings and convert them to an integer.
    m4 = "";                                 // reset m4 to an empty string
    m5 = "";                                 // reset h5 to an empty string
  }

  if (count1 == 5) {      // if count = 5
    s1 = number_pressed;  // seconds 1 = number pressed.
    lcd.setCursor(8, 0);  // printing first digit of time set
    lcd.print(h4);
    lcd.setCursor(9, 0);  // printing second digit of time set
    lcd.print(h5);
    lcd.setCursor(11, 0); // printing third digit of time set
    lcd.print(m4);
    lcd.setCursor(12, 0); // printing third digit of time set
    lcd.print(m5);
    lcd.setCursor(14, 0); // printing fourth digit of time set
    lcd.print(s1);
  }

  if (count1 == 6) {                         // if count = 6
    s2 = number_pressed;                     // seconds 2 = number pressed
    lcd.setCursor(8, 0);  // printing first digit of time set
    lcd.print(h4);
    lcd.setCursor(9, 0);  // printing second digit of time set
    lcd.print(h5);
    lcd.setCursor(11, 0); // printing third digit of time set
    lcd.print(m4);
    lcd.setCursor(12, 0); // printing third digit of time set
    lcd.print(m5);
    lcd.setCursor(14, 0); // printing fourth digit of time set
    lcd.print(s1);
    lcd.setCursor(15, 0); // printing fifth and last digit of time set
    lcd.print(s2);
    lcd.clear();          // to clear time set from lcd
    s3 = (String(s1) + String(s2)).toInt();  // adds the two number inputed as strings and convert them to an integer.
    s1 = "";                                 // resets seconds to an empty string
    s2 = "";                                 // resets seconds to an empty string
    hours = constrain(h6, 0, 23);            // constrain hours
    minutes = constrain(m6, 0, 59);          // constrain minutes
    seconds = constrain(s3, 0, 59);          // constrain seconds
    count1 = 0;
    Serial.println();
    Serial.print("set time hours : ");
    Serial.println(hours);
    Serial.print("set time minutes : ");
    Serial.println(minutes);
    Serial.print("set time seconds : ");
    Serial.println(seconds);
    lcd.print("timeset");
  }
  number_pressed = "";  // think about this
  pressed = 0;
}

void Alarm_Tone() {
  int size = sizeof(durations) / sizeof(int);
  unsigned long hold = millis() + 60000; // if you want to change how long the alarm plays if nothing is pressed

  for (int note = 0; note < size && (mute != 1); note++) {  // needs for loop for song
    
    // Calculate hue value based on the note index
    int hue = map(note, 30, size, 0, 255);

    // convert notes values to work with case statememts
    int color_segment = hue / 5; // 30/6 gives 5 which gives 6 case statements
    int remainder = (hue - hue) * 6; // *6 to get it in terms of analog values and find its value compared to the range

    switch (color_segment) { // red
      case 0:
        Red = 255;
        Green = remainder; // goes into yellow next so want to add some value to green
        Blue = 0;
        break;
      case 1: // yellow 1:1 ratio
        Red = 255;
        Green = 255;
        Blue = 0;
        break;
      case 2: // green
        Red = 0;
        Green = 255;
        Blue = remainder; // b/c goes to cyan next
        break;
      case 3: // cyan = green:blue = 1:1
        Red = 0;
        Green = 255;
        Blue = 255;
        break;
      case 4: // blue
        Red = remainder;
        Green = 0;
        Blue = 255;
        break;
      default: // magenta
        Red = 255;
        Green = 0;
        Blue = 255;
        break;
    }

    IRController();
    if (millis() >= hold) { // to turn off alarm after default period of time
      alarm_off = true;
      setColor(0, 0, 0);
      break;
    }
    if ((mute == 1) || (snooze == 1)) {  // To break out of song if mute or snooze is pressed
      alarm_off = true;
      setColor(0, 0, 0);
      break;
    }
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    NewTone(BUZZER_PIN, melody[note], duration);
    setColor(Red, Green, Blue);
    //setColor(thing*2, thing*3, thing*4);
    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing:
    noNewTone(BUZZER_PIN);
  }
}

void setColor(uint8_t red, uint8_t green, uint8_t blue) {
  analogWrite(PIN_RED, red);
  analogWrite(PIN_GREEN, green);
  analogWrite(PIN_BLUE, blue);
}

void Snooze() {
  if (snooze == 1) {  // snooze feature!
    Serial.print("SNOOZE");
    analogWrite(BUZZER_PIN, 0);  // for speaker off
    int mins;
    int hrs;
    // if statments just to print to lcd mins and hrs
    if (minutes1 <= 54) {
      mins = minutes1 + 5;
      hrs = hours1;
    }

    else if (minutes1 == 55) {
      mins = 0;
      hrs = hours1 + 1;
    }

    else if (minutes1 == 56) {
      mins = 1;
      hrs = hours1 + 1;
    }

    else if (minutes1 == 57) {
      mins = 2;
      hrs = hours1 + 1;
    }

    else if (minutes1 == 58) {
      mins = 3;
      hrs = hours1 + 1;
    }

    else if (minutes1 == 59) {
      mins = 4;
      hrs = hours1 + 1;
    }
    snooze = 0;
    snoozeEndTime = millis() + 300000; // current time + 5 mins
  
    lcd.clear();
    lcd.setCursor(9, 1);  // display set alarm to lcd
    lcd.print("h");
    lcd.setCursor(10, 1);
    lcd.print(hrs);
    lcd.setCursor(13, 1);
    lcd.print("m");
    lcd.setCursor(14, 1);
    lcd.print(mins);

    Serial.print("Snooze hours : ");
    Serial.print(hrs);
    Serial.print("Snooze minutes : ");
    Serial.print(mins);
  }
}

void Mute() {
  if (mute == 1) {
    analogWrite(BUZZER_PIN, 0);  // for speaker off
    mute = 0;
    alarm_off = true;                // nessecary to ensure the alarm can't keep going off
    lcd.clear();                     // clears the display from the alarm being set
    lcd.print("Morning Sunshine!");  // display fun message for one second
    delay(1000);
    lcd.clear();
    Serial.print("muted");
  }
}

void setup() {
  Serial.begin(9600);
  irController.begin();                           //intializes the IR controller
  Serial.setTimeout(100);                         // 100ms timeout for serial input
  Serial.println("Set Time in hh:mm:ss format");  //prints to the serial monitor
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Set time in");
  lcd.setCursor(0, 1);
  lcd.print("hh:mm:ss format");  // formatting the
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("timeset");
  pinMode(IR_RECEIVER_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PIN_RED, OUTPUT);  // RGB pins defined
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
}

void loop() {
  unsigned long currentMillis1 = millis();  // makes it so condition in second if statement can be evaluated
  IRController();                           // Call the IR control function
  Time_Increment_AND_LCD_Format();
  if (pressed == 1) {  // If a button is pressed on the IR remote pressed == 1.
    Alarm_Set();
    Time_Set();
  }

  if ((hours1 == hours) && (minutes1 == minutes) && (currentMillis1 > 60000) && (alarm_off == false)) {  // change 0 back to 60000 // so alarm does't go off right away (*alarm can never go off in less than a minute)
    Alarm_Tone();
    Snooze();
    Mute();
  }

  if (snoozeEndTime > 0 && millis() >= snoozeEndTime) { // simple idea works however not extremely accurate
    snoozeEndTime = 0;
    alarm_off = false;
    Alarm_Tone();
    Mute();
  }
}
