#include <Adafruit_TCS34725.h>


#define EXE_INTERVAL_1 2000 //kaç saniye olacağı
#define EXE_INTERVAL_2 500 //kaç saniye olacağı


#include <Wire.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <MeOrion.h>


//---------------------------

int maviyumurta=0;
int kirmiziyumurta=0;
int sayac = 0;
int kendi_rengin;

unsigned long lastExecutedMillis_1 = 0; // vairable to save the last executed time for code block 1
unsigned long lastExecutedMillis_2 = 0;
//---------------------------
MeDCMotor motor_9(9);
MeDCMotor motor_10(10);
//---------------------------
double  sure;
int base;
unsigned long myTime;
int bas_lux,bas_ct;
int bas_zem;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
//---------------------------


Servo myservo1;
Servo myservo2;

double mesafe3;
double mesafe4;
double mesafe8;

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
double mesafe;
MeUltrasonicSensor ultrasonic_3(3);
MeUltrasonicSensor ultrasonic_4(4);
MeUltrasonicSensor ultrasonic_8(8);

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
   myservo1.write(40);
    delay(1000);     
  }
void sagkapikapa()
{
    myservo1.write(0);

  }


  void solkapiac()
{
  myservo2.write(150);
    delay(1000);     
  }
  
void solkapikapa()
{
    myservo2.write(180);  
  }  




/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */
   
/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */


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
   uint16_t r, g, b, c, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  if(r>g and r>b and colorTemp<bas_ct*2 and b<1200)
   {Serial.println(" Kırmızı zemin");
   kendi_rengin = 1;   // KIRMIZI
   digitalWrite(12,LOW);
   digitalWrite(13,HIGH);
   }

   if(b>r and b>g and b<2000)
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
   mesafe3 = ultrasonic_3.distanceCm();
   mesafe8 = ultrasonic_8.distanceCm();
   mesafe4 = ultrasonic_4.distanceCm();
   uint16_t r, g, b, c, colorTemp, lux;
if ( base == 0){
  while(mesafe3>30){
   tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
    mesafe3 = ultrasonic_3.distanceCm();
   mesafe8 = ultrasonic_4.distanceCm();
   mesafe4 = ultrasonic_8.distanceCm();
    ileri();

    
    if(kendi_rengin == 1){
    if(r>g and r>b and colorTemp<bas_ct*2 and b<1200)
   {Serial.println(" Kırmızı zemin");
   
    motor_9.run(0);
    motor_10.run(0); 
    base++;  
    break;
   }
  }

  
  if(kendi_rengin == 2){
    if(b>r and b>g and b<2000)
  {Serial.println(" Mavi zemin");
    motor_9.run(0);
    motor_10.run(0); // MAVİ
    sayac++;
    break;
  }
  }
  }
}

if(base ==0){  
  while(mesafe4>20){
     tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
    mesafe3 = ultrasonic_3.distanceCm();
   mesafe8 = ultrasonic_8.distanceCm();
   mesafe4 = ultrasonic_4.distanceCm();
    sag();

    if(kendi_rengin == 1){
    if(r>g and r>b and colorTemp<bas_ct*2 and b<1200)
   {Serial.println(" Kırmızı zemin");
   
    motor_9.run(0);
    motor_10.run(0);
    base++;
    break;   
   }
   }
  

   if(kendi_rengin == 2){
   if(b>r and b>g and b<2000)
  {Serial.println(" Mavi zemin");
    motor_9.run(0);
    motor_10.run(0);
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

  Serial.println(kendi_rengin);
   mesafe3 = ultrasonic_3.distanceCm();
   mesafe8 = ultrasonic_8.distanceCm();
   mesafe4 = ultrasonic_4.distanceCm();
   
  if(maviyumurta>0 || kirmiziyumurta>0){
      geri_donme();
  }

  if(kendi_rengin ==1){
     
  }
  
  baslangic();
    
  Serial.println(mesafe);
  uint16_t r, g, b, c, colorTemp, lux;
  int son_zemin;
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
if(r>g and r>b and colorTemp>bas_ct*2 and r > 3000){
   Serial.println(" Kırmızı yumurta");
   solkapiac();
   hafif_sag();
   delay(500);
   solkapikapa();
   kirmiziyumurta++;
}
 else  if(b>r and b>g and colorTemp>bas_ct*2 and b > 2000)
   {Serial.println(" Mavi yumurta");
   sagkapiac();
   hafif_sol();
   delay(500);
   sagkapikapa();
   maviyumurta++;
   }
   
 else   
    { Serial.println(" Beyaz zemin");
    son_zemin=30;
    solkapikapa();
    sagkapikapa();}
 Serial.print(" bct ");
  Serial.println(bas_ct);
    Serial.print(" kendi  rengin"); 
  Serial.println(bas_zem);
  
}