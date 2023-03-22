#define EXE_INTERVAL_1 2000 //kaç saniye olacağı
#define EXE_INTERVAL_2 500 //kaç saniye olacağı


#include <Wire.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN1 11
#define ECHO_PIN1 10
#define TRIGGER_PIN2 12
#define ECHO_PIN2 13
#define TRIGGER_PIN3 1
#define ECHO_PIN3 1
#define MAX_DISTANCE 400  

int Lmotor1 = 7 ;
int Lmotor2 = 6;
int enRmotor = 10 ;
int Rmotor1 =  8;
int Rmotor2 =  9;
int enLmotor = 5;
int sayac=0;
int kirmiziyumurta=0;
int maviyumurta=0;

 

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE);
float duration, distance;

unsigned long lastExecutedMillis_1 = 0; // vairable to save the last executed time for code block 1
unsigned long lastExecutedMillis_2 = 0;


Servo solservo;  // create servo object to control a servo
Servo sagservo;  // create servo object to control a servo
#define s0 A3 //Bağladığımız pinlere göre tanımlamalarımızı yapıyoruz
#define s1 A4
#define s2 A1
#define s3 A2
#define sensorOut A5


int kirmizi, yesil, mavi = 0; //3 ana renk için değişken tanımlıyoruz
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
int sagg=0;
int soll=0;
int kendi_rengin=0;



void ileri()
{
    digitalWrite(Lmotor1,LOW);
    digitalWrite(Lmotor2,HIGH);
    digitalWrite(Rmotor1,HIGH);
    digitalWrite(Rmotor2,LOW);
    analogWrite (enRmotor, 100);
    analogWrite (enLmotor, 100);
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
    analogWrite (enRmotor, 100);
    analogWrite (enLmotor, 100);
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
  sagservo.attach(A6);
  solservo.attach(A7); 
  pinMode(s0, OUTPUT); //S0, S1, S2 ve S3 pinlerini OUTPUT olarak tanımlıyoruz  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sensorOut, INPUT); //OUT pinini INPUT olarak tanımlıyoruz
  digitalWrite(s1, LOW); //Frekans ölçeğimizi %20 olarak tanımlıyoruz
  digitalWrite(s0, HIGH);
 Serial.begin(9600);
 
// attaches the servo on pin 9 to the servo object
  solservo.write(0); 
  // attaches the servo on pin 9 to the servo object
  sagservo.write(180);
   
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
  if(mesafe3<10)
  {
    geri();
    delay(1000);
    sag();
    delay(1000);
    }
}
void solcarpma(){
  
  if(mesafe3<10)
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
 else if (mesafe8<15 && sagg==0){
    sag_gezinme();
  }
  else if (mesafe4<15 && soll==0){
    sol_gezinme();
  }
 
}

void geri_donme(){
   mesafe3 = sonar1.ping_cm();
   mesafe8 = sonar2.ping_cm();
   mesafe4 = sonar3.ping_cm();
if ( base == 0){
  while(mesafe3>30){
   mesafe3 = sonar1.ping_cm();
   mesafe8 = sonar2.ping_cm();
   mesafe4 = sonar3.ping_cm();
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
  while(mesafe4>20){
 
   mesafe3 = sonar1.ping_cm();
   mesafe8 = sonar2.ping_cm();
   mesafe4 = sonar3.ping_cm();
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



void loop(void) {
  ileri();
  
   mesafe3 = sonar1.ping_cm();
   mesafe8 = sonar2.ping_cm();
   mesafe4 = sonar3.ping_cm();
   
  if(maviyumurta>0 || kirmiziyumurta>0){
      geri_donme();
  }
  
  //baslangic();
  Serial.println(mesafe3);
  int son_zeminx;


  digitalWrite(s2, LOW); //Kırmızıyı filtrelemek için
  digitalWrite(s3, LOW);
  kirmizi = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur

  digitalWrite(s2, HIGH); //Yeşili filtrelemek için
  digitalWrite(s3, HIGH);
  yesil = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur

  digitalWrite(s2, LOW); //Maviyi filtrelemek için
  digitalWrite(s3, HIGH);
  mavi = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur

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
  Serial.println(bas_zem);
  
}