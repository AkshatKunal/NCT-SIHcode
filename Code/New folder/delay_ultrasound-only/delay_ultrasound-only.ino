const int trigPin = 9;             // Ultrasound transmitter
const int receiverPin = A0;        // Ultrasound receiver
const int pressureSensorPin = A1;  // Pressure sensor
float actualPressureVoltage;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pimMode(trigPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin,HIGH);
  
  analogRead()
}
