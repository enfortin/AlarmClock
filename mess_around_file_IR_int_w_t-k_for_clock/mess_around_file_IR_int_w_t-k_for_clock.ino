// Use Flag variables for executions for IR_Remote

#include <DIYables_IRcontroller.h> // DIYables_IRcontroller library
#include <LiquidCrystal.h>
#define IR_RECEIVER_PIN 7 // The Arduino pin connected to IR controller

DIYables_IRcontroller_21 irController(IR_RECEIVER_PIN, 200); // debounce time is 200ms

//Global Variables
int pressed = 0;
String number_pressed;
int mode = 0;
int hours, minutes, seconds;
int hours1, minutes1;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
unsigned long previousMillis;
const unsigned long interval = 1000;  // 1 second
String h1, h2, h4, h5, m1, m2, m4, m5, s1, s2;
int h3, h6, m3, m6, s3;
int count, count1 = 0;


void IRController() {
  Key21 key = irController.getKey();
  if (key != Key21::NONE) {

    switch (key) {

      case Key21::KEY_CH_MINUS:
        Serial.println("CH-");
        pressed = 1;
        break;

      case Key21::KEY_CH:
        //Serial.println("CH"); // This is the mode button
        pressed = 1;
        mode = 1;
        break;

      case Key21::KEY_CH_PLUS:
        //Serial.println("CH+"); // This is the mute button
        pressed = 1;
        break;

      case Key21::KEY_PREV:
        Serial.println(">||");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_NEXT:
        Serial.println("<<");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_PLAY_PAUSE:
        Serial.println(">>");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_VOL_MINUS:
        Serial.println("EQ");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_EQ:
        Serial.println("+");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_VOL_PLUS:
        Serial.println("-");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_100_PLUS:
        Serial.println("100+");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_200_PLUS:
        Serial.println("200+");
        // TODO: YOUR CONTROL
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
void setup() {
  Serial.begin(9600);
  irController.begin();
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

  IRController();

  if (pressed == 1) {

    while (mode == 1) {
      lcd.setCursor(0, 0);
      lcd.println("Set Alarm hhmm");
      IRController();
      if (pressed == 1) {
        pressed = 0;
        count += 1;
        Serial.print("alarm count : ");
        Serial.println(count);

        if (count == 2) {
          h1 = number_pressed;
        }

        if (count == 3) {
          h2 = number_pressed;
          h3 = (String(h1) + String(h2)).toInt();
          h1 = "";
          h2 = "";
        }

        if (count == 4) {
          m1 = number_pressed;
        }

        if (count == 5) {
          m2 = number_pressed;
          m3 = (String(m1) + String(m2)).toInt();
          m1 = "";
          m2 = "";
          hours1 = constrain(h3, 0, 23);
          minutes1 = constrain(m3, 0, 59);
          lcd.setCursor(0, 0);
          lcd.print("Alarm Set");
          count = 0;
          pressed = 0;
          Serial.println();
          Serial.print("alarm hours : ");
          Serial.println(hours1);
          Serial.print("alarm minutes : ");
          Serial.println(minutes1);
          break; // nessecary to get out of while loop
        }
      }
    }
    // Solve the issue with the following code after the above issue.
    count1 += 1;
    h4 = number_pressed;
    Serial.print("set time count : ");
    Serial.println(count1);
    if (count1 == 2) {
      h5 = number_pressed;
      h6 = (String(h4) + String(h5)).toInt();
      h4 = "";
      h5 = "";
    }

    if (count1 == 3) {
      m4 = number_pressed;
    }

    if (count1 == 4) {
      m5 = number_pressed;
      m6 = (String(m4) + String(m5)).toInt();
      m4 = "";
      m5 = "";
    }

    if (count1 == 5) {
      s1 = number_pressed;
    }

    if (count1 == 6) {
      s2 = number_pressed;
      s3 = (String(s1) + String(s2)).toInt();
      s1 = "";
      s2 = "";
      hours = constrain(h6, 0, 23);
      minutes = constrain(m6, 0, 59);
      seconds = constrain(s3, 0, 59);
      count1 = 0;
      Serial.println();
      Serial.print("set time hours : ");
      Serial.println(hours);
      Serial.print("set time minutes : ");
      Serial.println(minutes);
      Serial.print("set time seconds : ");
      Serial.println(seconds);
    }
    number_pressed = ""; // think about this
    pressed = 0;
  }
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
