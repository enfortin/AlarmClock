//1-12-23 Jack McTasney
//Stepper motor controller demo (ULN2003 controller)
// IN1: 7
// IN2: 6
// IN3: 5
// IN4: 4

//Definitions (making our lives easier)

#define VRX A0
#define in1 7
#define in2 6
#define in3 5
#define in4 4  //Nice
//Global Variable(s)
int delayTime;
int x;

void A() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void B() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void C() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void D() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void off() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void Forward() {
  A();
  delay(delayTime);
  B();
  delay(delayTime);
  C();
  delay(delayTime);
  D();
  delay(delayTime);
}
void Reverse() {
  D();
  delay(delayTime);
  C();
  delay(delayTime);
  B();
  delay(delayTime);
  A();
  delay(delayTime);
}
void setup() {
  // Pin initializations
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(VRX, INPUT);
}

void loop() {
  x = analogRead(A0);
  Serial.print(x);
  Serial.print('\t');
  delayTime = map(x, 0, 1023, 2, 20); 
  Serial.println(delayTime);
  // put your main code here, to run repeatedly:
  if ((delayTime >= 3 ) && (delayTime <= 19)) {
    off();
  }
  else if (delayTime == 2) {
    Forward();
  }
  else if (delayTime == 20){
    Reverse(); } // Counter-clockwise rotation
  }
  
  



