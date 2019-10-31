// ECE 411 Practicum
// Team 4: Hoang Nguyen, Ngan Ho, Jonathan Christian, Karla Barraza
// Script to control the input (numpad) and outputs (LEDs, buzzers, motors) using the Atmel ATMega32U4 microprocessor

#include <Adafruit_Keypad.h>
#include <EventBuffer.h>
#include <Servo.h>

#define MAXINPUT 20

// INPUTS
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; 
byte colPins[COLS] = {9, 8, 7, 6}; 
Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
char password[] = "1234"; 
int pswdSize = 0;
char inputpswd[MAXINPUT] = {}; //initiate input to empty 
int inputIndex = 0;
bool lock = false;
bool theft = false;
int trial = 0;

// OUTPUTS
int buzzer = 5;
int redLED = 4;
Servo myservo;
int closePosition = 180; //CHANGE ME
int openPosition = 90; //CHANGE ME

void setup(){
  // INPUTS
  Serial.begin(9600);
  customKeypad.begin();
  pswdSize = sizeof(password)-1;
  Serial.print("Enter a ");
  Serial.print(pswdSize);
  Serial.print("-ditgit PIN to lock/unlock: ");

  // OUTPUTS
  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
  myservo.write(openPosition);
}
  
void loop() {
  // INPUTS
  customKeypad.tick();
  char keyPress;

  if(customKeypad.available()){
    keypadEvent e = customKeypad.read();
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      keyPress = (char)e.bit.KEY; 
      //Save it in input array
      inputpswd[inputIndex] = keyPress;
      inputIndex++; 
      Serial.print(keyPress);
    }

    if (inputIndex == pswdSize) {
      Serial.println();
      inputpswd[inputIndex] = '\0'; // Add in null character for conversion to string
      String stringpswd = String(inputpswd); // Convert to stirng

      if (stringpswd == password) {
        Serial.println("PIN IS CORRECT!");
        Serial.print("Enter a ");
        Serial.print(pswdSize);
        Serial.print("-ditgit PIN to lock/unlock: ");
        lock = !(lock);
        trial = 0;
      }
      else{
        Serial.print("PIN IS INCORRECT. ATTEMPTS LEFT: ");
        Serial.println(3 - trial);
        if (trial < 3) {
          Serial.print("Enter a ");
          Serial.print(pswdSize);
          Serial.print("-ditgit PIN to lock/unlock: ");
        }
        else {
          theft = true;    
        }
        trial += 1;
      }
      memset(inputpswd, 0, sizeof(inputpswd)); // clear the inputData array
      inputIndex = 0; // reset inputIndex
    }
  }
  delay(10);

  // OUTPUTS
  if (lock == false) {
    myservo.write(openPosition);
  }
  if (lock == true) {
    myservo.write(closePosition);
  }
  if (theft == true) {
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
