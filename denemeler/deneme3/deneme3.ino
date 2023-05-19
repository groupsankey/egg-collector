#include <Servo.h>

int Lmotor1 = 4 ;
int Lmotor2 = 5;
int enRmotor = 10 ;
int Rmotor1 =  8;
int Rmotor2 =  7;
int enLmotor = 3;


Servo solservo;  // create servo object to control a servo
Servo sagservo;  // create servo object to control a servo
void ileri()
{

  digitalWrite(Lmotor1,LOW);
    digitalWrite(Lmotor2,HIGH);
    digitalWrite(Rmotor1,HIGH);
    digitalWrite(Rmotor2,LOW);
    analogWrite (enRmotor, 225);
    analogWrite (enLmotor, 100);
}
void dur()
{

  digitalWrite(Lmotor1,LOW);
    digitalWrite(Lmotor2,HIGH);
    digitalWrite(Rmotor1,HIGH);
    digitalWrite(Rmotor2,LOW);
    analogWrite (enRmotor, 0);
    analogWrite (enLmotor, 0);
}


int pos; //????????????
void sagkapiac()
{
  for (pos = 10; pos <= 60; pos += 1) { 
    // in steps of 1 degree
    sagservo.write(pos);              
    delay(5);                       
  }
  }

void sagkapikapa()
{
  for (pos = 60; pos >= 10; pos -= 1) { 
    sagservo.write(pos);              
    delay(5);                      
  }
  }

  void solkapiac()
{
    for (pos = 110; pos <= 160; pos += 1) { 
    // in steps of 1 degree
    solservo.write(pos);              
    delay(5);                       
  } 
  }
  
void solkapikapa()
{
  for (pos = 160; pos >= 110; pos -= 1) { 
    solservo.write(pos);              
    delay(5);                       
  } 
  }  


void setup(void) {
  sagservo.attach(13);
  solservo.attach(2); 
  pinMode(s0, OUTPUT); //S0, S1, S2 ve S3 pinlerini OUTPUT olarak tanımlıyoruz  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sensorOut, INPUT); //OUT pinini INPUT olarak tanımlıyoruz
  digitalWrite(s1, LOW); //Frekans ölçeğimizi %20 olarak tanımlıyoruz
  digitalWrite(s0, HIGH);
 Serial.begin(9600);
 
// attaches the servo on pin 9 to the servo object
  solservo.write(10); 
  // attaches the servo on pin 9 to the servo object
  sagservo.write(110);
   
  pinMode(13,OUTPUT);  // KIRMIZI
  pinMode(12,OUTPUT);  //MAVİ
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
 sagservo.attach(11);
 solservo.attach(9);
 pinMode(7, OUTPUT);

  pinMode(8, OUTPUT);
  pinMode(6, INPUT);
 pinMode(10, OUTPUT);

 // solservo.attach(A0); 
}

void loop() { 
  // put your main code here, to run repeatedly:
Serial.println(digitalRead(5));
}
 /* dur();
  sagservo.write(0);
  solservo.write(0);
  delay(1000);
  sagservo.write(90);x
  solservo.write(90);
    delay(1000);
ileri();
delay(2000);
 /*
  for(int i  =0 ;i<180;i++){
    solservo.write(i); 
  }
  // attaches the servo on pin 9 to the servo object
  for(int j = 0;j<180;j++){
  sagservo.write(j);
  }
*/
