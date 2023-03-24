const int frontPingPin = A0; // front sensor
const int frontEchoPin = A1; // front sensor
const int leftPingPin = 4; // left sensor
const int leftEchoPin = 3; // left sensor
const int rightPingPin = 11; // right sensor
const int rightEchoPin = 12; // right sensor

void setup() {
  Serial.begin(9600); // Serial Terminali Başlat
}

void loop() {
  long frontDuration, frontCm;
  long leftDuration, leftCm;
  long rightDuration, rightCm;
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

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
