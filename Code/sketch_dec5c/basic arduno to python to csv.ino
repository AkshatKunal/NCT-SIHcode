int inpu = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL, Time, Started Time, Date, Analog Value, POT%");
  Serial.println("RESETTIMER");
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensVal = analogRead(inpu);
  int sensPercent = map(sensVal, 0, 1023, 0, 100);
  Serial.print("DATA, TIME, TIMER, DATE,");
  Serial.print(sensVal);
  Serial.print(" ,");
  Serial.print(sensPercent);
  Serial.println(" ,");
  delay(1000);
}
