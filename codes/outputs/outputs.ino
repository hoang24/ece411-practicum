#include <Servo.h>

// Inputs -- Uncomment the appropriate section depending on which device we are using
int openButton = 4; //for arduino
int closeButton = 5; //for arduino
int theftButton = 8; //for arduino

//int openButton = 6; //for 328p 
//int closeButton = 11; //for 328p
//int theftButton = 14; //for 328p

//int openButton = 25; //for 32u4
//int closeButton = 31; //for 32u4
//int theftButton = 28; //for 32u4


// Outputs -- Uncomment the appropriate section depending on which device we are using

int buzzer = 12; //for arduino
int redLED = 13; //for arduino

//int buzzer = 18; //for 328p
//int redLED = 19; //for 328p

//int buzzer = 26; //for 32u4
//int redLED = 32; //for 32u4

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
