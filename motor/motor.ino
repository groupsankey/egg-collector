int enRmotor = 5 ;
int enLmotor = 10;
int Lmotorb = 9 ;
int Lmotorf = 8;
int Rmotorb =  7;
int Rmotorf =  6;




void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(Lmotorf,HIGH);
    digitalWrite(Lmotorb,LOW);
    digitalWrite(Rmotorf,HIGH);
    digitalWrite(Rmotorb,LOW);
    analogWrite (enRmotor, 100);
    analogWrite (enLmotor, 100);
}
