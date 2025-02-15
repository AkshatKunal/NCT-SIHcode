int transmitterPin = 9;
int receiverPin = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(transmitterPin,OUTPUT);
  pinMode(receiverPin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  tone(transmitterPin,40000);
  delay(2000);
  digitalWrite(transmitterPin,LOW);
  delay(2000);
}
