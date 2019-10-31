# This is a brief report for prototype 1 (Practicum HW #4)

### Achievement:
- Program the input side (numpad for unlock/lock logic and theft detection)
- Program the output side (motor for lock/unlock mechanism, buzzer and LED for alarm mechanism)
- Integrate input and output hardware and software

### Current Status;
Our prototype can now lock (turn servo motor one way) and unlock (turn servo motor other way) when the user enters the correct PIN on the numpad. We have program an interactive session on the Arduino serial monitor to visualize the user inputs. Our program also count the number of attempts when the user enter incorrect PINs, and will sound the buzzer while flashing an LED after the third wrong attempt. 

For future work, we will implement a way to reset after the alarm sound. Right now, we are hardcoding the PIN into the program, but we will soon have a way for the users to enter their own passwords. We will also start design the box and lasercut the box and housing for the electronics. We will also start using the Atmel ATMega32U4 chip.

### Gallery:

[[https://github.com/hoang24/ece411-practicum/blob/master/images/ece411_proto1_img0.jpeg|alt=proto1_img]]
[[https://github.com/hoang24/ece411-practicum/blob/master/images/|alt=proto1]]


[[https://github.com/hoang24/ece411-practicum/blob/master/images/idea_generation.jpg|alt=idea_generation]]
