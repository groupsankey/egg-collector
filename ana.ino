#define EXE_INTERVAL_1 2000 //kaç saniye olacağı
#define EXE_INTERVAL_2 500 //kaç saniye olacağı


#include <Wire.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>


unsigned long lastExecutedMillis_1 = 0; // vairable to save the last executed time for code block 1
unsigned long lastExecutedMillis_2 = 0;


Servo solservo;  // create servo object to control a servo
Servo sagservo;  // create servo object to control a servo
MeUltrasonicSensor ultrasonic_3(3);
MeUltrasonicSensor ultrasonic_4(4);
MeUltrasonicSensor ultrasonic_8(8);
#define s0 A3 //Bağladığımız pinlere göre tanımlamalarımızı yapıyoruz
#define s1 A4
#define s2 A1
#define s3 A2
#define sensorOut A5


int K, Y, M = 0; //3 ana renk için değişken tanımlıyoruz
double  sure;
int base;
unsigned long myTime;
int bas_lux,bas_ct;
int bas_zem;
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
double mesafe;
double mesafe3;
double mesafe4;
double mesafe8;
const int pingPin = 12; // Tetikleyici/Trigger Pini Tanımı
const int echoPin = 11; // Yankı/Echo Pini Tanımı
const int pingPin = 12; // Tetikleyici/Trigger Pini Tanımı
const int echoPin = 11; // Yankı/Echo Pini Tanımı
const int pingPin = 12; // Tetikleyici/Trigger Pini Tanımı
const int echoPin = 11; // Yankı/Echo Pini Tanımı
int sagg=0;
int soll=0;




void ileri()
{
    motor_9.run(-200);
    motor_10.run(-200);
}
void yileri()
{
    motor_9.run(-50);
    motor_10.run(-50);
}
void geri()
{
    motor_9.run(100);
    motor_10.run(100);
}
void ygeri()
{
    motor_9.run(50);
    motor_10.run(50);
}

void sag()
{
    motor_9.run(-100);
    motor_10.run(100);
  }

void sol()
  {
     motor_9.run(100);
    motor_10.run(-100);
  }

   void hafif_sag()
  {
    motor_9.run(-150);
    motor_10.run(-50);
  }

  void hafif_sol()
  {
    motor_9.run(-50);
    motor_10.run(-150);
  }


void sagkapiac()
{
  for (pos = 0; pos <= 150; pos += 5) { // goes from 0 degrees to 150 degrees
    // in steps of 5 degree
    sagservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1000);                       // waits 15ms for the servo to reach the position
  }      
  }
void sagkapikapa()
{
      for (pos = 150; pos >= 0; pos -= 5) { // goes from 0 degrees to 150 degrees
    // in steps of 5 degree
    sagservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1000);                       // waits 15ms for the servo to reach the position
  }     
  }


  void solkapiac()
{
  for (pos = 0; pos <= 150; pos += 5) { // goes from 0 degrees to 150 degrees
    // in steps of 5 degree
    solservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1000);                       // waits 15ms for the servo to reach the position
  }   
  }
  
void solkapikapa()
{
      for (pos = 150; pos >= 0; pos -= 5) { // goes from 0 degrees to 150 degrees
    // in steps of 5 degree
    solservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1000);                       // waits 15ms for the servo to reach the position
  }     
  }  

void setup(void) {
 Serial.begin(9600);
 
  myservo1.attach(A2);  // attaches the servo on pin 9 to the servo object
  myservo1.write(0); 
  myservo2.attach(A3);  // attaches the servo on pin 9 to the servo object
  myservo2.write(180);
   
  pinMode(13,OUTPUT);  // KIRMIZI
  pinMode(12,OUTPUT);  //MAVİ


 
  
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

   uint16_t r, g, b, c, colorTemp, lux;
  
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
bas_ct=colorTemp;
    Serial.println(" ");
    if(r>g and r>b)
   {Serial.println("Kırmızı zemin");
   bas_zem=10;
   }

   if(b>r and b>g)
   {bas_zem=20;
   Serial.println(" Mavi zemin");}
  // Now we're ready to get readings!

renk_belirleme();
  
}
unsigned long currentMillis=0;