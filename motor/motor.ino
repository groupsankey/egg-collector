#include <Servo.h>
int enRmotor = 2;
int enLmotor = 7;
int Lmotorb = 6 ;
int Lmotorf = 5;
int Rmotorb =  3;
int Rmotorf =  4;

Servo solservo;  // create servo object to control a servo
Servo sagservo;  // create servo object to control a servo
/*
#define s0 A0//Bağladığımız pinlere göre tanımlamalarımızı yapıyoruz
#define s1 A1
#define s2 A3
#define s3 A4
#define sensorOut A2
*/

void setup() {
  // put your setup code here, to run once:
  /*
sagservo.attach(13);
  solservo.attach(3); 
  
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
   */
 
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(Lmotorf,LOW);
    digitalWrite(Lmotorb,HIGH);
    digitalWrite(Rmotorf,HIGH);
    digitalWrite(Rmotorb,LOW);
    analogWrite (enRmotor, 100);
    analogWrite (enLmotor, 100);
}
