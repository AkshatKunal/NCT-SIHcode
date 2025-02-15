int trigPin = 9;
int signalWave = 6;
int sensPin = A0;
int pressureSensorPin = A1 ;
float sensVal;
float startTime;
float recieveTime;
float omega;
float time;
float sineVal;
float voltage;
float waveAmplitude;
float pressure_mbar;
float pressure_mmHg;
float pi = 3.14159;
int rawValue;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(signalWave, OUTPUT);
  pinMode(sensPin, INPUT);  
  Serial.begin(9600);
  omega = (2 * pi * 40000);
  Serial.print("pressure_mmHg, ");
  Serial.print("sensVal, ");
  Serial.print("waveAmplitude, ");
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  rawValue = analogRead(pressureSensorPin);  
  voltage = rawValue * (5.0 / 1023.0);  // Convert to voltage (assuming a 5V reference)
  // Convert voltage to pressure in mbar
  if (voltage >= 1.88 && voltage <= 9.4) {
    pressure_mbar = map(voltage * 100, 188, 940, 0, 100);  // Map from 1.88V-9.4V to 0-100mbar
    pressure_mmHg = pressure_mbar * 0.75006;  // Convert mbar to mmHg
  } else {
    pressure_mbar = 0;    // Consider out-of-range voltages as zero pressure
    pressure_mmHg = 0;  
    // Serial.println(); 
  } 

  Serial.print(pressure_mmHg);
  Serial.print(",");


  tone(signalWave,50);
  delay(100);
  digitalWrite(signalWave,LOW);

  // tone(trigPin,40000);
  digitalWrite(trigPin,HIGH);
  startTime = millis();
  delay(200);

  // digitalWrite(signalWave,LOW);

  sensVal = analogRead(sensPin);
  Serial.print(sensVal);
  Serial.print(",");
  recieveTime = millis();
  time = (recieveTime - startTime);
  // Serial.print(time);
  // Serial.print(",");
  sineVal = sin((omega * time)/1000);
  waveAmplitude = sensVal/sineVal;

  digitalWrite(trigPin,LOW);

  Serial.print(waveAmplitude);
  Serial.println(",");
  delay(1);
}
