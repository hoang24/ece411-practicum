#include <Servo.h>

// Inputs
int openButton = 4;
int closeButton = 5;
int theftButton = 8;

// Outputs
int buzzer = 12;
int redLED = 13;
Servo myservo;
int closePosition = 0; //CHANGE ME
int openPosition = 180; //CHANGE ME

void setup() {
  pinMode(openButton, INPUT_PULLUP);
  pinMode(closeButton, INPUT_PULLUP);
  pinMode(theftButton, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  if (digitalRead(openButton) == LOW) {
    myservo.write(openPosition);
  }
  if (digitalRead(closeButton) == LOW) {
    myservo.write(closePosition);
  }
  if (digitalRead(theftButton) == LOW) {
    unsigned char i;
    while(1){
      for(i=0;i<8;i++){
        digitalWrite(buzzer, HIGH);
        digitalWrite(redLED, HIGH);
        delay(100);
        digitalWrite(buzzer, LOW);
        digitalWrite(redLED, LOW);
        delay(100);
      }
      for(i=0;i<10;i++){
        digitalWrite(buzzer, HIGH);
        digitalWrite(redLED, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        digitalWrite(redLED, LOW);
        delay(200);
      }
    }
  }
}
