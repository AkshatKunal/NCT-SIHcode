// #include <Filters.h>
 
// #include <AH/Timing/MillisMicrosTimer.hpp>
// #include <Filters/Butterworth.hpp>

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
  // Serial.println("Void");
  // Serial.println(millis());

  while(1) {
    sensVal = analogRead(receiverPin);
    // Serial.println("SensVal");
    // Serial.println(sensVal);
    // Serial.println("While");
    // Serial.println(millis());
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
  // // put your main code here, to run repeatedly:
  // int rawValue = analogRead(pressureSensorPin);  
  // voltage = rawValue * (5.0 / 1023.0);
  // pressure_mbar = map(voltage * 100, 188, 940, 0, 100);
  // pressure_mmHg = pressure_mbar * 0.75006;
  // Serial.println(" mmHg");
  // Serial.println(pressure_mmHg);
    // Read analog input and convert to voltage
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

  // Print results


  // Serial.print("Voltage: ");
  // Serial.print(voltage, 2);          // Print voltage with 2 decimal places
  // Serial.print(" V | Pressure: ");
  // Serial.print(pressure_mmHg, 2);    // Print pressure in mmHg
  // Serial.println(" mmHg");
  Serial.print(pressure_mmHg);
  Serial.print(",");


  digitalWrite(trigPin,HIGH);
  delay(diffTime);
  // actualPressureVoltage = analogRead(pressureSensorPin); 
  // Z1 = Z0*(1+k)/(1-k);
  // l = 4*Z1*Z0/((Z1+Z0)*(Z1+Z0));
  // a = k/l;
  // Z2 = Z3*(1-a)/(1+a);
  // Serial.println(" actual pressure");
  // Serial.println(actualPressure);
  // Serial.print(" actual input: ");
  // Serial.println(userInput);

  // // Sampling frequency
  // const double f_s = 100000; // Hz
  // // Lower and upper cutoff frequencies (-3 dB)
  // const double f_l = 40000; // Hz
  // const double f_u = 40010; // Hz
  // // Normalized lower and upper cutoff frequencies
  // const double f_n1 = 2 * f_l / f_s;
  // const double f_n2 = 2 * f_u / f_s;

  // // Sample timer
  // Timer<micros> timer = std::round(1e6 / f_s);
  
  // // Second-order bandpass Butterworth filter
  // auto filter = butterworth(f_n1, f_n2, LOWPASS);

  actualPressureVoltage = analogRead(receiverPin); 

  // filterredSignal = filter(analogRead(A0))

 // Serial.println(filterredSignal);

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