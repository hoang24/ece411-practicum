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

// //////////////////////////////////////////////////////////
//ROW & PIN COLUMNS -- UNCOMMENT THE SECTION APPROPRIATE FOR THE DEVICE WE ARE USING AT THE TIME
byte rowPins[ROWS] = {13, 12, 11, 10}; //for arduino
byte colPins[COLS] = {9, 8, 7, 6}; //for arduino

//byte rowPins[ROWS] = {19, 18, 17, 16}; //for 328P
//byte colPins[COLS] = {15, 14, 13, 12}; //for 328P
//
//byte rowPins[ROWS] = {32, 26, 12, 30}; //for 32U4
//byte colPins[COLS] = {29, 28, 1, 27}; //for 32U4
/////////////////////////////////////////////////////////////


Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
char password[] = "1234"; 
char changePSWDKey[] = "****";
int pswdSize = 0;
char inputpswd[MAXINPUT] = {}; //initiate input to empty 
int inputIndex = 0;
bool lock = false;
bool theft = false;
int trial = 0;

/////////////////////////////////////////// 
//Outputs -- Uncomment the appropriate section depending on which device we are using

int buzzer = 12; //for arduino
int redLED = 13; //for arduino

//int buzzer = 18; //for 328p
//int redLED = 19; //for 328p

//int buzzer = 26; //for 32u4
//int redLED = 32; //for 32u4

///////////////////////////////////////////
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
  int status = 0; 
/////////////////////////////////////
  //if the door is open
  if(myservo.read() == openPosition)
  {
    //check if keys have been pressed
    if(customKeypad.available())
    {
      char * destination = inputpswd;
      int * index = &inputIndex;
      
      //Read in key-presses
      status = readKeyPresses(destination, index); 
      
      if(inputIndex = sizeof(changePSWDKey))
      {
        Serial.println("Enter a new 4-digit password");

        memset(inputpswd, 0, sizeof(inputpswd)); // clear the inputData array
        inputIndex = 0; // reset inputIndex

        //loop until keyPress is availalbe
        //read the key
        //do this until 4 keys are done 
        for (int i = 0; i < 4; i++)
        {
          int loopDiLoop = 0;
          do
          {
            loopDiLoop++; //delay loop
          }while (!customKeypad.available()); //Loop until key press is available

         if(customKeypad.available())
         {
            char * destination = password;
            int * index = &inputIndex;    
            status = readKeyPresses(destination, index);        
         }
        }

        Serial.print("The new password is: "); 
        Serial.print(password);
        Serial.println();
      }
    }
  }
/////////////////////////////////

  if(customKeypad.available()){
    char * destination = inputpswd;
    int * index = &inputIndex;
      
    //Read in key-presses
    status = readKeyPresses(destination, index); 

    //Is the number of keys pressed equal to the size of the password? 
    if (inputIndex == pswdSize) {
      Serial.println();

      //Convert keypresses from user input into a string for comparison
      inputpswd[inputIndex] = '\0'; // Add in null character for conversion to string
      String stringpswd = String(inputpswd); // Convert to stirng

      //Does the input password match the stored password? 
      if (stringpswd == password) {
        Serial.println("PIN IS CORRECT!");
        Serial.print("Enter a ");
        Serial.print(pswdSize);
        Serial.print("-ditgit PIN to lock/unlock: ");
        lock = !(lock);
        trial = 0;
      }
      else
        {
        Serial.print("PIN IS INCORRECT. ATTEMPTS LEFT: ");
        Serial.println(3 - trial);
         
        if (trial < 3) 
          {
            Serial.print("Enter a ");
            Serial.print(pswdSize);
            Serial.print("-ditgit PIN to lock/unlock: ");
          }
        else 
          {
          theft = true;    
          }
            
          trial += 1;
        }//end of else
      memset(inputpswd, 0, sizeof(inputpswd)); // clear the inputData array
      inputIndex = 0; // reset inputIndex
    }//end of if
    
  }//end of if
  
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
      }//end of for loop
    }//end of while
  } //end of if
  
}//End of Loop


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
    int status = 0; 
    char keyPress;
    int I = *index; //save the value of index into a variable we can manipulate
    if(destination == NULL)
    {
      return status; //error
    }

    if(index == NULL)
    {
      return status; //error
    }
    
    //Read in key-presses
    keypadEvent e = customKeypad.read();
    
    if (e.bit.EVENT == KEY_JUST_PRESSED) 
    {
      keyPress = (char)e.bit.KEY; 
      //Save it in input array
      *(destination + *index) = keyPress; //save the key press back into the appropriate location in the desination array
      *index = I++; //increment the index and save it back into the global variable
      Serial.print(keyPress);

      return index; // successful keyPress 
    }

    return status; //Error, status = 0
}
