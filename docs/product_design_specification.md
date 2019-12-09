# Product Design Specification (PDS) - Revision #3

## SeLo SECURITY LOCKER

#### Executive Summary / Concept of Operation**

The SeLo security locker is an affordable, wall-mounted option that allows for protected storage of sensitive documents, keys or valuable personal items. SeLo helps occupy less space than traditional lockboxes, provide sufficient security and ease of access for people of all generations. This security locker can be mounted on the wall, and its owner can setup and open the box using a PIN. SeLo will sound an alarm if thieves try wrong passwords or steal the box.

#### Brief Market Analysis
- **Intended customers**: SeLo is suitable for people of all ages, those who need a secure place to store important items with more security and not occupy too much space in their house. 
- **Competition**: Our unit competes in the same market as entry level safes and lockable cabinets manufactued by companies like SentrySafe, Master Lock and Barska. However, the SeLo securiy Locker is compact, affordable and packed with extra features like an electronic keypad and has theft deterent measures built in. SeLo is also more accessible, as it is available for purchase in common local stores.
- **Expected price**: The price for SeLo is around $50. Most off-the-shelves lockers are above $100 and are both heavy and take up lots of space with unnecessary storage. We believe that $50 is a reasonable price that can cover the cost of parts while also generating profits. In addition, this price point specifically targets a niche market that is currently underserved.

#### Requirements

-  MUST weigh less than 20 lbs
-  MUST be able to access contents within 5 seconds of entering passcode.
-  MUST cost less than $40 to produce
-  MUST be securable to a fixed surface (wall or floor)
-  MUST be safe to manufacture
-  SHOULD be smaller than 12" x 12" x 12"
-  SHOULD be of rugged construction
-  SHOULD have an backup/alternative method to open
-  SHOULD be able to store at least 4 different passcodes
-  SHOULD be able to easily change or alter PIN
-  SHOULD sound an alarm after 3 wrong PIN attempts 
-  MAY be weather resistant

**System Architecture**

![level 1 block diagram](images/LockBox.JPG)


**Design Specification**
- **Sensor:** Alphanumeric Keypad consisting of four letters A,B,C & D.
- **Proccessor:**  Atmel ATMega32U4 8-bit Microcontroller.
- **Actuator:** Motor, Lock, LEDs, LCD/Display; included in SHOULD category: accelerometer, surveilance camera & speaker.
- **Power:** 5V power supply and current limiting resistors.
- **Mechanical design:** SparkFun Motor Driver - Dual TB6612FNG (1A) to control door locking mechanism.
- **Firmware:** Unlikely, but may need software to verify the Pin.
- **Arduino:** Will use Arduino to communicate with the microcontroller.
- **Development environment:** Arduino IDE run on Windows OS.

