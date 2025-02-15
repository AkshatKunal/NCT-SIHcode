int pinIn = A1;
float valIn;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinIn, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  valIn = analogRead(pinIn);
  valIn = map(valIn,0,1023.0,0,5.0);
  Serial.println(valIn);
}
