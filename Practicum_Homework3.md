# Practicum Homework #3: Product Design Specification (PDS)

### Security Locker for Keys/Important Documents


**Executive Summary / Concepts of Operations**

A wall-mounted lockbox that can be used to store important documents, keys or other personal effects to provide 
extra security and ease of access. With this product, people can have more space to store important things, but it is
not occupy a lot of spaces. Everyone can easily use the wall-mounted clock to store documents, keys inside the box by entering 
Pin/Password or FingerPrint to open or close the door.

**Brief Market Analysis**

Our intended customers are people who need more space to store important things with more security and they also do not want to take 
the place for the box.
The competition is all security boxes in the market. Two reasons make our security locker different from other security boxes
in the market are: people can mount our lockbox to the wall so it does not take the place and accelerometer for theft detection.
The price for wall mounted lockbox is around $50 because it is a reasonable price and we can make a profit at that price.

**Requirements**

A wall-mounted lockbox should hold about 5 kilograms. When people enter Pin/Password or FingerPrint the door should open/close
within 10 seconds. Also, people can easily change Pin/Password by just entering old Pin/Password, press reset and enter new Pin/Password.

**System Architecture**




**Design Specification**
- **Sensor:** Pin/Password/FingerPrint/RFID, etc.
- **Proccessor:**  Atmel ATMegaXXX 8 bit microcontroller.
- **Actuator:** Lock, Speaker, LEDs, LCD screens, SHOULD: motor and accelerometer.
- **Power:** 5V, may need some resistors.
- **Mechanical design:** SparkFun Motor Driver - Dual TB6612FNG (1A) as a motor to open and close the door.
- **Firmware:** may need software to check whether the Pin/Password or FingerPrint is correct or not.
- **Arduino:** may need to write code in Arduino software.
- **Development environment:** environment safe.

