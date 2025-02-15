// const int pressureSensorPin = A1;  // Pressure sensor
// float voltage;          // Measured voltage
// float pressure_mbar;    // Pressure in mbar
// float pressure_mmHg;    // Pressure in mmHg
// float actualPressure;
// float actualPressureVoltage;

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   pinMode(pressureSensorPin, INPUT);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   int rawValue = analogRead(pressureSensorPin);  
//   voltage = rawValue * (5.0 / 1023.0);  // Convert to voltage (assuming a 5V reference)

//   // Convert voltage to pressure in mbar
//   if (voltage >= 1.70 && voltage <= 15) {
//     pressure_mbar = map(voltage * 100, 188, 940, 0, 100);  // Map from 1.88V-9.4V to 0-100mbar
//     pressure_mmHg = pressure_mbar * 0.75006;  // Convert mbar to mmHg
//   } else {
//     pressure_mbar = 0;    // Consider out-of-range voltages as zero pressure
//     pressure_mmHg = 0;    
//   }

//   float current = voltage / 470 ;

//   // Print results
//   Serial.print(rawValue, 2); 
//   Serial.print("Current: ");
//   Serial.print(current, 2);  
//   Serial.print("A | Voltage: ");
//   Serial.print(voltage, 2);          // Print voltage with 2 decimal places
//   Serial.print(" V | Pressure: ");
//   Serial.print(pressure_mmHg, 2);    // Print pressure in mmHg
//   Serial.println(" mmHg");
// }


const int pressureSensorPin = A1;  // Pressure sensor pin
float voltage;                    // Measured voltage
float pressure_mbar;              // Pressure in mbar
float pressure_mmHg;              // Pressure in mmHg
float current;                    // Current through the circuit

void setup() {
  Serial.begin(9600);             // Start serial communication
  pinMode(pressureSensorPin, INPUT);
}

void loop() {
  // Read raw analog value
  int rawValue = analogRead(pressureSensorPin);
  
  // Convert raw value to voltage (assuming a 5V reference)
  voltage = rawValue * (5.0 / 1023.0);

  // Map voltage to pressure in mbar, assuming sensor range 1.88V to 9.4V maps to 0-100mbar
  if (voltage >= 1.88 && voltage <= 9.4) {
    pressure_mbar = (voltage - 1.88) * (100.0 / (9.4 - 1.88));
    pressure_mmHg = pressure_mbar * 0.75006;  // Convert mbar to mmHg
  } else {
    pressure_mbar = 0;  // Out-of-range voltages result in zero pressure
    pressure_mmHg = 0;
  }

  // Calculate current (assuming 470-ohm resistance)
  current = voltage / 470.0;

  // Print results
  Serial.print("Raw Value: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V | Current: ");
  Serial.print(current * 1000, 6);  // Print current with higher precision
  Serial.print(" mA | Pressure: ");
  Serial.print(pressure_mmHg, 2);
  Serial.println(" mmHg");

  delay(500);  // Delay for readability
}

