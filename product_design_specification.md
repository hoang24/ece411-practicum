# Product Design Specification (PDS) - Practicum Homework #3

### SeLo SECURITY LOCKER


#### Executive Summary / Concepts of Operations**

SeLo is a wall-mounted security locker to store important documents, keys or other personal items. SeLo helps occupy less space than traditional lockboxes, provide sufficient security and ease of access for people of all generations. This security locker can be mounted on the wall, and its owner can setup and open the box using PIN/password/finger print. SeLo will sound an alarm if thieves try wrong passwords or steal the box.

#### Brief Market Analysis
- **Intended customers**: Suitable for people of all ages, those who need a secure place to store important items with more security and not occupy too much space in their house. 
- **Competition**: Compete with all off-the-shelves lockers in the market. What make our SeLo security locker stands out is (1) ease of use, (2) theft detection, (3) use efficient space. 
- **Expected price**: The price for SeLo is around $50. Most off-the-selves lockers are above $100 and they are heavy/use lots of space with unnecessary storage. We believe that $50 is a reasonable price that can cover the part costs while generating profits.

#### Requirements

A wall-mounted lockbox SHOULD hold about 10 kilograms. When people enter a correct PIN/passcode, the door MUST open/close
within 5 seconds. Also, people SHOULD easily change PIN/passcode using their old PIN/passcode. When the PIN/passcode is entered wrong more than 3 times, or when the lockbox is moved without correct PIN/passcode, the alarm MUST sound immediately. 

**System Architecture**

![level 1 block diagram](images/level1_block_diagram.jpg)


**Design Specification**
- **Sensor:** Pin/Password/FingerPrint/RFID, etc.
- **Proccessor:**  Atmel ATMegaXXX 8 bit microcontroller.
- **Actuator:** Lock, Speaker, LEDs, LCD screens, SHOULD: motor and accelerometer.
- **Power:** 5V, may need some resistors.
- **Mechanical design:** SparkFun Motor Driver - Dual TB6612FNG (1A) as a motor to open and close the door.
- **Firmware:** may need software to check whether the Pin/Password or FingerPrint is correct or not.
- **Arduino:** may need to write code in Arduino software.
- **Development environment:** environment safe.

