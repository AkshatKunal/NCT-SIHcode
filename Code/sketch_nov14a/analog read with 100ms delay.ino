int trigPin = 9;
int rec = A5;
int rec2;
void setup() {
  // put your setup code here, to run once:
pinMode(trigPin, OUTPUT);
pinMode(rec, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigPin, HIGH);
rec2 = analogRead(rec);
Serial.println(rec2);
delay(100);
}
