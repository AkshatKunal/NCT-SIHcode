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
float IOP;
float m = 1 * pow(10,-5);
float Z0 = 1.73 * pow(10,6);
float Z1;
float Z2;
float Z3 = 1.59 * pow(10,7);
int inputVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
  int userInput = Serial.read() - 48;
  Serial.print(" actual input: ");
  Serial.println(userInput);
  actualPressureVoltage = analogRead(pressureSensorPin); 
  k = userInput * 0.1;
  Z1 = Z0*(1+k)/(1-k);
  Serial.print("Z1: ");
  Serial.println(Z1);
  Serial.print("Z0: ");
  Serial.println(Z0);
  l = 4*Z1*Z0/((Z1+Z0)*(Z1+Z0));
  Serial.print("l: ");
  Serial.println(l);
  a = k/l;
  Serial.print("a: ");
  Serial.println(a);
  Z2 = Z3*(1-a)/(1+a);
  Serial.print("Z2: ");
  Serial.println(Z2);
  IOP = m * Z2;
  Serial.print(" actual pressure: ");
  Serial.println(IOP);
  }
  // Serial.println(" actual input");
  // Serial.println(inputVal);
  // actualPressureVoltage = analogRead(pressureSensorPin); 
  // k = inputVal * 0.1;
  // Z1 = Z0*(1+k)/(1-k);
  // l = 4*Z1*Z0/((Z1+Z0)*(Z1+Z0));
  // a = k/l;
  // Z2 = Z3*(1-a)/(1+a);
  // IOP = m * Z2;
  // Serial.println(" actual pressure");
  // Serial.println(actualPressure);
  // delay(1000);
}
