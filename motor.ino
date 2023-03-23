int Lmotorf = 9 ;
int Lmotorb = 8;
int enRmotor = 5 ;
int Rmotorf =  7;
int Rmotorb =  6;
int enLmotor = 10;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(Lmotorf,LOW);
    digitalWrite(Lmotorb,HIGH);
    digitalWrite(Rmotorf,LOW);
    digitalWrite(Rmotorb,HIGH);
    analogWrite (enRmotor, 0);
    analogWrite (enLmotor, 100);
}
