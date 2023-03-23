#define s0  A5//Bağladığımız pinlere göre tanımlamalarımızı yapıyoruz
#define s1 A6
#define s2 A3
#define s3 A4
#define sensorOut A2
int K, Y, M = 0; //3 ana renk için değişken tanımlıyoruz
void setup() {
  pinMode(s0, OUTPUT); //S0, S1, S2 ve S3 pinlerini OUTPUT olarak tanımlıyoruz
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sensorOut, INPUT); //OUT pinini INPUT olarak tanımlıyoruz
  digitalWrite(s1, LOW); //Frekans ölçeğimizi %20 olarak tanımlıyoruz
  digitalWrite(s0, HIGH);
  Serial.begin(9600);
}
void loop() {
  digitalWrite(s2, LOW); //Kırmızıyı filtrelemek için
  digitalWrite(s3, LOW);
  K = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Kırmızı= ");
  Serial.print(K); //Kırmızı için aldığımız değeri serial monitöre yazdır
  Serial.print("  ");
  delay(50); //50 milisaniye bekle
  digitalWrite(s2, HIGH); //Yeşili filtrelemek için
  digitalWrite(s3, HIGH);
  Y = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Yeşil= ");
  Serial.print(Y); //Yeşil için aldığımız değeri serial monitöre yazdır
  Serial.print("   ");
  delay(50); //50 milisaniye bekle
  digitalWrite(s2, LOW); //Maviyi filtrelemek için
  digitalWrite(s3, HIGH);
  M = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Mavi= ");
  Serial.print(M); //Mavi için aldığımız değeri serial monitöre yazdır
  Serial.println();
  delay(50); //50 milisaniye bekle
}
