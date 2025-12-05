#include <IRremote.h>


int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;


int leftTurn = 2;
int rightTurn = 3;
int wiperLED = 4;
int windowUpLED = 5;
int windowDownLED = 6;


int parkGreen = 9;
int parkYellow = 10;
int parkRed = 12;


int headlights = 13;
int brakeLeft = A0;
int brakeRight = A1;
int reverseLight = A2;


int buzzer = A3;


int trigPin = 8;
int echoPin = 7;


bool wipersOn = false;
bool leftOn = false;
bool rightOn = false;
bool headlightsOn = false;
bool reverseOn = false;
bool brakeOn = false;

unsigned long previousBlink = 0;
unsigned long previousWiperBlink = 0;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(leftTurn, OUTPUT);
  pinMode(rightTurn, OUTPUT);
  pinMode(wiperLED, OUTPUT);
  pinMode(windowUpLED, OUTPUT);
  pinMode(windowDownLED, OUTPUT);

  pinMode(parkGreen, OUTPUT);
  pinMode(parkYellow, OUTPUT);
  pinMode(parkRed, OUTPUT);

  pinMode(headlights, OUTPUT);
  pinMode(brakeLeft, OUTPUT);
  pinMode(brakeRight, OUTPUT);
  pinMode(reverseLight, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {

 
  if (irrecv.decode(&results)) {
    unsigned long code = results.value;

    if (code == IR_LEFT) {
      leftOn = !leftOn;
      rightOn = false;
      digitalWrite(rightTurn, LOW);
    }

    if (code == IR_RIGHT) {
      rightOn = !rightOn;
      leftOn = false;
      digitalWrite(leftTurn, LOW);
    }

    if (code == IR_WIPERS) {
      wipersOn = !wipersOn;
    }

    if (code == IR_HEAD) {
      headlightsOn = !headlightsOn;
    }

    if (code == IR_REVERSE) {
      reverseOn = !reverseOn;
    }

    if (code == IR_BRAKE) {
      brakeOn = !brakeOn;
    }

    if (code == IR_WINUP) {
      digitalWrite(windowUpLED, HIGH);
      digitalWrite(windowDownLED, LOW);
    }

    if (code == IR_WINDOWN) {
      digitalWrite(windowUpLED, LOW);
      digitalWrite(windowDownLED, HIGH);
    }

  
    if (code == IR_HORN) tone(buzzer, 1000);
    else noTone(buzzer);

    irrecv.resume();
  }

 
  digitalWrite(headlights, headlightsOn);
  digitalWrite(reverseLight, reverseOn);
  digitalWrite(brakeLeft, brakeOn);
  digitalWrite(brakeRight, brakeOn);


  unsigned long currentMillis = millis();

  if (leftOn && currentMillis - previousBlink >= 500) {
    previousBlink = currentMillis;
    digitalWrite(leftTurn, !digitalRead(leftTurn));
  }
  if (!leftOn) digitalWrite(leftTurn, LOW);

  if (rightOn && currentMillis - previousBlink >= 500) {
    previousBlink = currentMillis;
    digitalWrite(rightTurn, !digitalRead(rightTurn));
  }
  if (!rightOn) digitalWrite(rightTurn, LOW);


  
  if (wipersOn && currentMillis - previousWiperBlink >= 150) {
    previousWiperBlink = currentMillis;
    digitalWrite(wiperLED, !digitalRead(wiperLED));
  }
  if (!wipersOn) digitalWrite(wiperLED, LOW);

 
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance > 30) {
    digitalWrite(parkGreen, HIGH);
    digitalWrite(parkYellow, LOW);
    digitalWrite(parkRed, LOW);
  }
  else if (distance > 15) {
    digitalWrite(parkGreen, LOW);
    digitalWrite(parkYellow, HIGH);
    digitalWrite(parkRed, LOW);
  }
  else {
    digitalWrite(parkGreen, LOW);
    digitalWrite(parkYellow, LOW);
    digitalWrite(parkRed, HIGH);
  }
}