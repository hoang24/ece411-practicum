// References: http://www.circuitbasics.com/how-to-set-up-a-keypad-on-an-arduino/ 
//
//
//**********

#include <Adafruit_Keypad.h>
#include <EventBuffer.h>

#define MAXINPUT 20

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13,12,11,10}; 
byte colPins[COLS] = {9, 8, 7, 6}; 

Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

char password[] = "1234"; 
int pswdSize = 0;
char inputpswd[MAXINPUT] = {}; //initiate input to empty 
int inputIndex = 0;
bool openDoor = false;

void setup(){
  Serial.begin(9600);
  customKeypad.begin();
  Serial.print(sizeof(password)-1);
  pswdSize = sizeof(password)-1;
}
  
void loop() {
  // put your main code here, to run repeatedly:
  #include <Servo.h>

// Inputs
int openButton = 3;
int closeButton = 4;
int theftButton = 5;

// Outputs
int buzzer = 2;
int redLED = 1;
Servo myservo;
int closePosition = 0; //CHANGE ME
int openPosition = 180; //CHANGE ME

void setup() {
  pinMode(openButton, INPUT_PULLUP);
  pinMode(closeButton, INPUT_PULLUP);
  pinMode(theftButton, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  myservo.attach(A5);  // attaches the servo on pin 9 to the servo object
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
  customKeypad.tick();
  char keyPress;
  
//  while(customKeypad.available()){ // note, the available() keypad seems to count one button press as 2 events
//    keypadEvent e = customKeypad.read();
//    Serial.print((char)e.bit.KEY);
//    if(e.bit.EVENT == KEY_JUST_PRESSED) Serial.println(" pressed");
//    else if(e.bit.EVENT == KEY_JUST_RELEASED) Serial.println(" released");
//  }

//Get Key
  if(customKeypad.available()){ //If#1
    keypadEvent e = customKeypad.read();
    if(e.bit.EVENT == KEY_JUST_PRESSED)
    {
      keyPress = (char)e.bit.KEY; 
       //Save it in input array
      inputpswd[inputIndex] = keyPress;
      inputIndex++; 
      Serial.print("This is what you've entered:");
      Serial.println(inputpswd);
    }
    else if(inputIndex == pswdSize) //IF#2  //Check if it's as big as size of password, this else condition also keeps this code from running twice
    {
      Serial.println("it's the right size!");
 
      inputpswd[inputIndex] = '\0';           //Add in null character for conversion to string
      String stringpswd = String(inputpswd);  //Convert to stirng
      
      //If yes, check if it's the same password
      if(stringpswd == password) //IF#3
      {
        Serial.println("It's the same password!");
        
        //If yes, send signal to motor
        openDoor = true;
      } //end IF#3
      else{
        Serial.println("It's not the same password!");
        Serial.print("This is the password: ");
        Serial.println(password);
        Serial.print("This is what you entered: ");
        Serial.println(inputpswd);
        openDoor = false;
      }
       //clear the inputData array
       memset(inputpswd, 0, sizeof(inputpswd));
        
       //reset inputIndex
       inputIndex = 0;
    }//end IF#2
   }//end IF#1
  delay(10);
} //end loop
