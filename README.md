README

This code is written in Arduino IDE and includes control code for an autonomous robot with various sensors and actuators. 
The robot is equipped with three ultrasonic sensors to detect obstacles and two servos to control doors. Additionally, 
the robot can detect and differentiate between colors using a TCS3200 color sensor.

Libraries:
This code utilizes the following libraries:
Wire.h
Arduino.h
SoftwareSerial.h
Servo.h
NewPing.h
Make sure that these libraries are installed in your Arduino IDE before uploading the code to your board.

Sensors and Actuators:
Front sensor: connected to analog pin A0 (ping) and A1 (echo).
Left sensor: connected to digital pin 4 (ping) and 3 (echo).
Right sensor: connected to digital pin 11 (ping) and 12 (echo).
Motors: connected to digital pins 5, 10, 9, 8, 7, 6, and are controlled by PWM signals on pins 5 and 10.
Servos: connected to digital pins 6 and 7.
Color sensor: connected to analog pins A2, A3, A4, and A5.


Functions:
The code includes the following functions:
ileri(): Moves the robot forward.
yileri(): Moves the robot forward slowly.
geri(): Moves the robot backward.
ygeri(): Moves the robot backward slowly.
sag(): Turns the robot to the right.
sol(): Turns the robot to the left.
hafif_sag(): Turns the robot slightly to the right.
hafif_sol(): Turns the robot slightly to the left.
sagkapiac(): Opens the right door.
sagkapikapa(): Closes the right door.
solkapiac(): Opens the left door.
solkapikapa(): Closes the left door.
microsecondsToCentimeters(): Converts the duration of the ultrasonic sensor to the distance in centimeters.

Variables:
The code includes the following variables:
EXE_INTERVAL_1: The interval at which block 1 of the code is executed (in milliseconds).
EXE_INTERVAL_2: The interval at which block 2 of the code is executed (in milliseconds).
frontPingPin: The pin number for the front sensor's ping.
frontEchoPin: The pin number for the front sensor's echo.
leftPingPin: The pin number for the left sensor's ping.
leftEchoPin: The pin number for the left sensor's echo.
rightPingPin: The pin number for the right sensor's ping.
rightEchoPin: The pin number for the right sensor's echo.
enRmotor: The pin number for the right motor's enable.
enLmotor: The pin number for the left motor's enable.
Lmotor1: The pin number for the left motor's input 1.
Lmotor2: The pin number for the left motor's input 2.
Rmotor1: The pin number for the right motor's input 1.
Rmotor2: The pin number for the right motor's input 2.
sayac: A counter variable.
kirmiziyumurta: A counter variable for red eggs.
maviyumurta: A counter variable for blue eggs.
lastExecutedMillis_1: The time at which block 1 of the previous execution was completed (in milliseconds since Unix epoch time).
lastExecutedMillis_2: The time at which block 2 of the previous execution was completed (in milliseconds since Unix epoch time).
lastExecutedMillis_3: The time at which block 3 of the previous execution was completed (in milliseconds since Unix epoch time).

Future Improvements:
This script can be improved in several ways, such as:
Adding support for command-line arguments to make it more user-friendly.
Adding a logging system to track the execution of the script.
Adding more input parameters to make the function more customizable.
Adding error handling for common errors such as network timeouts or database connection errors.
