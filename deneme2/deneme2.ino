#define EXE_INTERVAL_1 2000 //kaç saniye olacağı
#define EXE_INTERVAL_2 500 //kaç saniye olacağı


#include <Wire.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <NewPing.h>

const int frontPingPin = A0; // front sensor
const int frontEchoPin = A1; // front sensor
const int leftPingPin = 4; // left sensor
const int leftEchoPin = 3; // left sensor
const int rightPingPin = 11; // right sensor
const int rightEchoPin = 12; // right sensor 

int enRmotor = 5 ;
int enLmotor = 10;
int Lmotor1 = 9 ;
int Lmotor2 = 8;
int Rmotor1 =  7;
int Rmotor2 =  6;
int sayac=0;
int kirmiziyumurta=0;
int maviyumurta=0;


unsigned long lastExecutedMillis_1 = 0; // vairable to save the last executed time for code block 1
unsigned long lastExecutedMillis_2 = 0;


Servo solservo;  // create servo object to control a servo
Servo sagservo;  // create servo object to control a servo
#define s0  A5//Bağladığımız pinlere göre tanımlamalarımızı yapıyoruz
#define s1 A6
#define s2 A3
#define s3 A4
#define sensorOut A2


int kirmizi, yesil, mavi = 0; //3 ana renk için değişken tanımlıyoruz
double  sure;
int base;
unsigned long myTime;
int bas_lux,bas_ct;
int bas_zem;
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
long frontDuration, frontCm;
long leftDuration, leftCm;
long rightDuration, rightCm;
int sagg=0;
int soll=0;
int kendi_rengin=0;

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void ileri()
{
    digitalWrite(Lmotor1,LOW);
    digitalWrite(Lmotor2,HIGH);
    digitalWrite(Rmotor1,LOW);
    digitalWrite(Rmotor2,HIGH);
    analogWrite (enRmotor, 150);
    analogWrite (enLmotor, 150);
}
void yileri()
{
    digitalWrite(Lmotor1,LOW);
    digitalWrite(Lmotor2,HIGH);
    digitalWrite(Rmotor1,HIGH);
    digitalWrite(Rmotor2,LOW);
    analogWrite (enRmotor, 50);
    analogWrite (enLmotor, 50);
}
void geri()
{
    digitalWrite(Lmotor1,HIGH);
    digitalWrite(Lmotor2,LOW);
    digitalWrite(Rmotor1,LOW);
    digitalWrite(Rmotor2,HIGH);
    analogWrite (enRmotor, 150);
    analogWrite (enLmotor, 150);
}
void ygeri()
{
    digitalWrite(Lmotor1,HIGH);
    digitalWrite(Lmotor2,LOW);
    digitalWrite(Rmotor1,LOW);
    digitalWrite(Rmotor2,HIGH);
    analogWrite (enRmotor, 50);
    analogWrite (enLmotor, 50);
}

void dur()
{
    digitalWrite(Lmotor1,HIGH);
    digitalWrite(Lmotor2,LOW);
    digitalWrite(Rmotor1,HIGH);
    digitalWrite(Rmotor2,LOW);
    analogWrite (enRmotor, 0);
    analogWrite (enLmotor, 0);
  }
void sag()
{
    digitalWrite(Lmotor1,HIGH);
    digitalWrite(Lmotor2,LOW);
    digitalWrite(Rmotor1,HIGH);
    digitalWrite(Rmotor2,LOW);
    analogWrite (enRmotor, 75);
    analogWrite (enLmotor, 75);
  }

void sol()
  {
    digitalWrite(Lmotor1,LOW);
    digitalWrite(Lmotor2,HIGH);
    digitalWrite(Rmotor1,LOW);
    digitalWrite(Rmotor2,HIGH);
    analogWrite (enRmotor, 75);
    analogWrite (enLmotor, 75);
  }

   void hafif_sag()
  {
    digitalWrite(Lmotor1,HIGH);
    digitalWrite(Lmotor2,LOW);
    digitalWrite(Rmotor1,HIGH);
    digitalWrite(Rmotor2,LOW);
    analogWrite (enRmotor, 50);
    analogWrite (enLmotor, 50);
  }

  void hafif_sol()
  {
    digitalWrite(Lmotor1,LOW);
    digitalWrite(Lmotor2,HIGH);
    digitalWrite(Rmotor1,LOW);
    digitalWrite(Rmotor2,HIGH);
    analogWrite (enRmotor, 50);
    analogWrite (enLmotor, 50);
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


    Serial.println(" ");
    if(kirmizi>yesil and kirmizi>mavi)
   {Serial.println("Kırmızı zemin");
   bas_zem=10;
   }

   if(mavi>kirmizi and mavi>yesil)
   {bas_zem=20;
   Serial.println(" Mavi zemin");}
  // Now we're ready to get readings!

renk_belirleme();
  
}
unsigned long currentMillis=0;


void sag_gezinme(){
       if (millis()-currentMillis <2000) 
     
        {
      if (currentMillis - lastExecutedMillis_1 >= EXE_INTERVAL_1) {
     // save the last executed time
     lastExecutedMillis_1 = currentMillis;
      ileri();
      Serial.println("ileri");
    }}
    
   else if(millis()-currentMillis>=2000 and millis()-currentMillis <2350){
    
      sag();
      Serial.println("sag");
    
   }
   if ( millis()-currentMillis>= 2350){
    currentMillis = millis();
   }
        sagcarpma;
  sagg++;
}

void sol_gezinme(){
   if (millis()-currentMillis <2000) 
     
        {
      if (currentMillis - lastExecutedMillis_1 >= EXE_INTERVAL_1) {
     // save the last executed time
      
      ileri();
      Serial.println("ileri");
    }}
    
   else if(millis()-currentMillis>=2000 and millis()-currentMillis <2350){

      sol();
    
    
   }
    if ( millis()-currentMillis>= 2350){
    currentMillis = millis();
   }
   solcarpma();
  soll++;
}

void sagcarpma(){
  if(rightCm<10)
  {
    geri();
    delay(1000);
    sag();
    delay(1000);
    }
}
void solcarpma(){
  
  if(leftCm<10)
  {
    geri();
    delay(1000);
    sol();
    delay(1000);
    }
}


void renk_belirleme(){
  if(kirmizi>yesil and kirmizi>mavi and mavi<1200)
   {Serial.println(" Kırmızı zemin");
   kendi_rengin = 1;   // KIRMIZI
   digitalWrite(12,LOW);
   digitalWrite(13,HIGH);
   }

   if(mavi>kirmizi and mavi>yesil and mavi<2000)
  {Serial.println(" Mavi zemin");
  kendi_rengin=2;   // MAVİ
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  }
}

void baslangic(){
   if(sagg>0){
    sag_gezinme();
  }
  if(soll>0){
    sol_gezinme();
  }
 else if (frontCm<15 && sagg==0){
    sag_gezinme();
  }
  else if (rightCm<15 && soll==0){
    sol_gezinme();
  }
 
}

void geri_donme(){
if ( base == 0){
  while(leftCm>30){
    ileri();

    
    if(kendi_rengin == 1){
    if(kirmizi>yesil and kirmizi>mavi and mavi<1200)
   {Serial.println(" Kırmızı zemin");
   
    digitalWrite(Lmotor1,LOW);
    digitalWrite(Lmotor2,HIGH);
    digitalWrite(Rmotor1,HIGH);
    digitalWrite(Rmotor2,LOW);
    analogWrite (enRmotor, 0);
    analogWrite (enLmotor, 0); 
    base++;  
    break;
   }
  }

  
  if(kendi_rengin == 2){
    if(mavi>kirmizi and mavi>yesil and mavi<2000)
  {Serial.println(" Mavi zemin");
    digitalWrite(Lmotor1,LOW);
    digitalWrite(Lmotor2,HIGH);
    digitalWrite(Rmotor1,HIGH);
    digitalWrite(Rmotor2,LOW);
    analogWrite (enRmotor, 0);
    analogWrite (enLmotor, 0);; // MAVİ
    sayac++;
    break;
  }
  }
  }
}

if(base ==0){  
  while(rightCm>20){

    sag();

    if(kendi_rengin == 1){
    if(kirmizi>yesil and kirmizi>mavi and mavi<1200)
   {Serial.println(" Kırmızı zemin");
   
    digitalWrite(Lmotor1,LOW);
    digitalWrite(Lmotor2,HIGH);
    digitalWrite(Rmotor1,HIGH);
    digitalWrite(Rmotor2,LOW);
    analogWrite (enRmotor, 0);
    analogWrite (enLmotor, 0);
    base++;
    break;   
   }
   }
  

   if(kendi_rengin == 2){
   if(mavi>kirmizi and mavi>yesil and mavi<2000)
  {Serial.println(" Mavi zemin");
    digitalWrite(Lmotor1,LOW);
    digitalWrite(Lmotor2,HIGH);
    digitalWrite(Rmotor1,HIGH);
    digitalWrite(Rmotor2,LOW);
    analogWrite (enRmotor, 0);
    analogWrite (enLmotor, 0);
    sayac++;
    break;// MAVİ
   }
  }  
 }
}


  if(sayac ==1){
  if(kendi_rengin ==1){
    ileri();
    delay(1000);
    solkapiac();
    geri();
    delay(1000);
    kirmiziyumurta = 0;
    sayac = 0;
    }
    
     if(kendi_rengin ==2){
    ileri();
    delay(1000);
    sagkapiac();
    geri();
    delay(1000);
    maviyumurta = 0;
    sayac = 0;
    }
  }
}

int onUltrasonic()
{
    // Front Sensor Reading
  pinMode(frontPingPin, OUTPUT);
  digitalWrite(frontPingPin, LOW);
  delayMicroseconds(1);
  digitalWrite(frontPingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(frontPingPin, LOW);
  pinMode(frontEchoPin, INPUT);
  frontDuration = pulseIn(frontEchoPin, HIGH);
  frontCm = microsecondsToCentimeters(frontDuration);
  return frontCm;
  }
void ult()
{
    // Left Sensor Reading
  pinMode(leftPingPin, OUTPUT);
  digitalWrite(leftPingPin, LOW);
  delayMicroseconds(1);
  digitalWrite(leftPingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(leftPingPin, LOW);
  pinMode(leftEchoPin, INPUT);
  leftDuration = pulseIn(leftEchoPin, HIGH);
  leftCm = microsecondsToCentimeters(leftDuration);
  // Right Sensor Reading
  pinMode(rightPingPin, OUTPUT);
  digitalWrite(rightPingPin, LOW);
  delayMicroseconds(1);
  digitalWrite(rightPingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(rightPingPin, LOW);
  pinMode(rightEchoPin, INPUT);
  rightDuration = pulseIn(rightEchoPin, HIGH);
  rightCm = microsecondsToCentimeters(rightDuration);
  // Printing the distance readings to Serial Monitor
  Serial.print("Front: ");
  Serial.print(frontCm);
  Serial.print("cm    ");
  Serial.print(" Left: ");
  Serial.print(leftCm);
  Serial.print("cm    ");
  Serial.print(" Right: ");
  Serial.print(rightCm);
  Serial.print("cm   ");
  Serial.println();
  delay(5);
   
  }

  void renk()
  {
  
  digitalWrite(s2, LOW); //Kırmızıyı filtrelemek için
  digitalWrite(s3, LOW);
  kirmizi = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Kırmızı= ");
  Serial.print(kirmizi); //Kırmızı için aldığımız değeri serial monitöre yazdır
  Serial.print("  ");
  delay(5); //50 milisaniye bekle
  digitalWrite(s2, HIGH); //Yeşili filtrelemek için
  digitalWrite(s3, HIGH);
  yesil = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Yeşil= ");
  Serial.print(yesil); //Yeşil için aldığımız değeri serial monitöre yazdır
  Serial.print("   ");
  delay(5); //50 milisaniye bekle
  digitalWrite(s2, LOW); //Maviyi filtrelemek için
  digitalWrite(s3, HIGH);
  mavi = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Mavi= ");
  Serial.print(mavi); //Mavi için aldığımız değeri serial monitöre yazdır
  Serial.println();
 // delay(55); //50 milisaniye bekle    
    }
void loop(void) {
if (onUltrasonic()>15)   
  {
    ileri();
    renk();
    Serial.print(onUltrasonic());
  }
else 
{
dur();
delay(1000);

}

/*

  if(maviyumurta>0 || kirmiziyumurta>0){
      geri_donme();
  }
  
  int son_zeminx;


  renk();
  if(kirmizi>yesil and kirmizi>mavi and kirmizi > 3000){
   Serial.println(" Kırmızı yumurta");
   solkapiac();
   hafif_sag();
   delay(500);
   solkapikapa();
   kirmiziyumurta++;
}
 else  if(mavi>kirmizi and mavi>yesil and mavi > 2000)
   {Serial.println(" Mavi yumurta");
   sagkapiac();
   hafif_sol();
   delay(500);
   sagkapikapa();
   maviyumurta++;
   }
   
 else   
    { Serial.println(" Beyaz zemin");
    //son_zemin=30;
    solkapikapa();
    sagkapikapa();}
 Serial.print(" bct ");
  Serial.println(bas_ct);
    Serial.print(" kendi  rengin"); 
  Serial.println(bas_zem);*/
  
}
