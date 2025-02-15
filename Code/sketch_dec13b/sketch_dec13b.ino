
const int trigPin = 9;             // Ultrasound transmitter
const int receiverPin = A0;        // Ultrasound receiver
const int pressureSensorPin = A1;  // Pressure sensor
float voltage;          // Measured voltage
float pressure_mbar;    // Pressure in mbar
float pressure_mmHg;    // Pressure in mmHg
float actualPressure;
float actualPressureVoltage;
float k;
float l;
float a;
float Z0 = 1.73 * pow(10,6);
float Z1;
float Z2;
float Z3 = 1.59 * pow(10,7);
float IOP;
float m = 1 * pow(10,-5);
int highVoltage;
float sensVal;
float tresh;
float endTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(receiverPin, INPUT);
  pinMode(pressureSensorPin, INPUT);
  digitalWrite(trigPin, LOW);

  digitalWrite(trigPin, HIGH);
  unsigned long startTime = millis();

  while(1) {
    sensVal = analogRead(receiverPin);
    if (sensVal > tresh) {
      endTime = millis();
      digitalWrite(trigPin, LOW);
      break;
    }
  }
  unsigned long diffTime = endTime - startTime;
  // Serial.println(diffTime);
  digitalWrite(trigPin, LOW);
  Serial.print("pressure_mmHg, ");
  Serial.print("Ratio, ");
  Serial.print("IOP, ");
}

void loop() {

  int rawValue = analogRead(pressureSensorPin);  
  voltage = rawValue * (5.0 / 1023.0);  // Convert to voltage (assuming a 5V reference)

  // Convert voltage to pressure in mbar
  if (voltage >= 1.88 && voltage <= 9.4) {
    pressure_mbar = map(voltage * 100, 188, 940, 0, 100);  // Map from 1.88V-9.4V to 0-100mbar
    pressure_mmHg = pressure_mbar * 0.75006;  // Convert mbar to mmHg
  } else {
    pressure_mbar = 0;    // Consider out-of-range voltages as zero pressure
    pressure_mmHg = 0;  
    Serial.println();  
  }

  Serial.print(pressure_mmHg);
  Serial.print(",");


  digitalWrite(trigPin,HIGH);
  delay(diffTime);

  actualPressureVoltage = analogRead(receiverPin); 

  k = actualPressureVoltage;//highVoltage;
  Z1 = Z0*(1+k)/(1-k);
  Serial.print(k);
  Serial.print(",");
  // Serial.print("Z1: ");
  // Serial.println(Z1);
  // Serial.print("Z0: ");
  // Serial.println(Z0);
  l = 4*Z1*Z0/((Z1+Z0)*(Z1+Z0));
  // Serial.print("l: ");
  // Serial.println(l);
  a = k/l;
  // Serial.print("a: ");
  // Serial.println(a);
  Z2 = Z3*(1-a)/(1+a);
  // Serial.print("Z2: ");
  // Serial.println(Z2);
  IOP = m * Z2;
  // Serial.print(" actual pressure: ");
  // Serial.println(IOP);
  Serial.print(IOP);
  Serial.print(",");
  delay(1000);
}