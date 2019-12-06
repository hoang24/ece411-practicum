// ECE 411 Practicum
// Team 4: Hoang Nguyen, Ngan Ho, Jonathan Christian, Karla Barraza
// Script to control the input (numpad) and outputs (LEDs, buzzers, motors) using the Atmel ATMega32U4 microprocessor

#include <Adafruit_Keypad.h>
//#include <Adafruit_Keypad_Ringbuffer.h>
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
byte rowPins[ROWS] = {12, 11, 10, 9};
byte colPins[COLS] = {8, 7, 6, 5};
Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
char password[] = "1234"; 
char changePSWDKey[] = "****";//Command to change the password
int pswdSize = 0;
char inputpswd[MAXINPUT] = {}; //initiate input to empty 
int inputIndex = 0;
bool lock = true;
bool theft = false;
int trial = 0;
int timer = 0; 
// OUTPUTS
int buzzer = 2;
int redLED = 4;
int servo = 3;
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
  myservo.attach(servo);  // attaches the servo on pin 9 to the servo object
  myservo.write(openPosition);
  Serial.print("The servo is at position: ");
  int i = myservo.read();
  Serial.println(i);
}

void loop() {
  // INPUTS
  customKeypad.tick();
  char keyPress;
 int ErrorMarker = 0; 

  //if the door is open you can change the password
  if(myservo.read() == openPosition)
  {
    //Serial.println("door is going through open door code");
    if(customKeypad.available())
    {
      char * destination = inputpswd;
      int * index = &inputIndex; 
      ErrorMarker = readKeyPresses(destination, index);

      if(inputIndex == sizeof(changePSWDKey) - 1)// -1 to account for null character at end of string
      {
        String stringpswd = String(inputpswd); // Convert to stirng
        
        if(stringpswd == changePSWDKey)//now check if the password matches
        {
          Serial.println("Ready to recivee new password! Enter a 4-digit password");
          memset(inputpswd, 0, sizeof(inputpswd)); // clear the inputData array
          inputIndex = 0; // reset inputIndex
  
          //loop until keyPress is availalbe
          //read the key
          //do this until 4 keys are done 
          while((*index) < 4)
          {
            customKeypad.tick(); //check for a key press
            char * destination = password;
            int * index = &inputIndex; 
            if(customKeypad.available()) // read the key press when it's available
            {
              ErrorMarker = readKeyPresses(destination, index);        
            }
          }

          //At this point, the new four digit password has been entered
          Serial.println("This is the new password: ");
          Serial.print(password);
        }
        else if (stringpswd == password) //if the password is entered while the door is open, it re-locks the door 
        {
          Serial.println("Lock is set to true 2");
          lock = true; //Lock that door! 
          memset(inputpswd, 0, sizeof(inputpswd)); // clear the inputData array
          inputIndex = 0; // reset inputIndex 
        }
        else 
        {
           memset(inputpswd, 0, sizeof(inputpswd)); // clear the inputData array
          inputIndex = 0; // reset inputIndex
        }
      }
    }
  }//Just generally read key presses 
  else
  {
    if(customKeypad.available()){
      char * destination = inputpswd;
      int * index = &inputIndex; 
      ErrorMarker = readKeyPresses(destination, index);

    if (inputIndex == pswdSize) {
      Serial.println();
      inputpswd[inputIndex] = '\0'; // Add in null character for conversion to string
      String stringpswd = String(inputpswd); // Convert to stirng

      if (stringpswd == password) {
        Serial.println("Lock is set to false 1");
        lock = false;
        Serial.println("PIN IS CORRECT!");
        Serial.print("Enter a ");
        Serial.print(pswdSize);
        Serial.print("-ditgit PIN to lock/unlock: ");
        trial = 0;
      }
      else{
        Serial.println("Lock is set to true 1");
        lock = true;
        Serial.print("PIN IS INCORRECT. ATTEMPTS LEFT: ");
        Serial.println(2 - trial);
        if (trial < 2) {
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
  }
  delay(10);

  // OUTPUTS
  if (lock == false) {
    //Serial.println("Door is now open!");
    myservo.write(openPosition);
  }
  if (lock == true) {
   // Serial.println("Door is now closed!");
    myservo.write(closePosition);
  }
  if (theft == true) {
    unsigned char i;

    while(timer < 10){
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
      timer++;
    }
    theft = false;
    timer = 0;
  }
}



/*
 * INPUTS: 
 * char * destination     a pointer to the array we want to read keypresses into
 * int * index            pointer to the index of the array that is to be read into
 * 
 * OUTPUTS: 
 * 0 if error
 * non-zero if success
 */
int readKeyPresses(char * destination, int *index)
{
    int ErrorMarker = 0; 
    char keyPress;
    if(destination == NULL)
    {
      Serial.println("Destination is null!");
      return ErrorMarker; //error status = 0
    }

    if(index == NULL)
    {
      Serial.println("Index is null");
      return ErrorMarker; //error status = 0
    }
    if(((*index) >= 20) || ((*index) < 0)){
      Serial.println("index is too large");
      return ErrorMarker; //error status = 0
    }

    keypadEvent e = customKeypad.read();
    
    if (e.bit.EVENT == KEY_JUST_PRESSED) 
    {
      keyPress = (char)e.bit.KEY; 
      Serial.println("You entered: ");
      Serial.println(keyPress);
      //Save it in input array
      destination[*index] = keyPress; //save the key press back into the appropriate location in the desination array
      (*index) = (*index) + 1; //increment the index and save it back into the global variable
      Serial.println(destination);

      for(int i = 0; i < 2; i++)//Beepity beep
      {
        digitalWrite(buzzer, HIGH);
        digitalWrite(redLED, HIGH);
        delay(10); // high chirpy noise, use longer delay for lower tone
        digitalWrite(buzzer, LOW);
        digitalWrite(redLED, LOW);
        delay(10);
      }
      ErrorMarker = 1;
      return ErrorMarker; // successful keyPress, status is nonzero
    }
    return ErrorMarker; //Error, status = 0
}
