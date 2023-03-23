#include <Servo.h>

Servo sagservo;
Servo solservo;

int pos = 0;    // variable to store the servo position

void setup() {
  sagservo.attach(13);
  solservo.attach(2);
}

void loop() {
  for (pos = 10; pos <= 60; pos += 1) { 
    // in steps of 1 degree
    sagservo.write(pos);              
    delay(5);                       
  }
  for (pos = 60; pos >= 10; pos -= 1) { 
    sagservo.write(pos);              
    delay(5);                      
  }
    for (pos = 110; pos <= 160; pos += 1) { 
    // in steps of 1 degree
    solservo.write(pos);              
    delay(5);                       
  }
  for (pos = 160; pos >= 110; pos -= 1) { 
    solservo.write(pos);              
    delay(5);                       
  }
}
