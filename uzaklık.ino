const int pingPin = 12; // Tetikleyici/Trigger Pini Tanımı
const int echoPin = 11; // Yankı/Echo Pini Tanımı

void setup() {
   Serial.begin(9600); // Serial Terminali Başlat
}

void loop() {
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);

   digitalWrite(pingPin, LOW); // pingPin'in Temizlenmesi
   delayMicroseconds(2);

   digitalWrite(pingPin, HIGH); // pingPin'i 10 mikro saniye için YÜKSEK duruma ayarlar
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);

   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH); // echoPin'i okur, ses dalgasının seyahat süresini mikrosaniye cinsinden döndürür

   inches = microsecondsToInches(duration); // Mesafenin Hesaplanması inç cinsinden
   cm = microsecondsToCentimeters(duration); // Mesafenin Hesaplanması cm cinsinden
   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(100);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}