const int pressureSensorPin = 15;  // Pressure sensor pin
float voltage;                    // Measured voltage
float pressure_mbar;              // Pressure in mbar
float pressure_mmHg;              // Pressure in mmHg
float current;                    // Current through the circuit

void setup() {
  Serial.begin(115200);             // Start serial communication
  pinMode(pressureSensorPin, INPUT);
}

void loop() {
  // Read raw analog value
  int rawValue = analogRead(pressureSensorPin);
  
  // Convert raw value to voltage (assuming a 5V reference)
  voltage = rawValue * (3.3 / 4095);

  // Map voltage to pressure in mbar, assuming sensor range 1.88V to 9.4V maps to 0-100mbar
  if (voltage >= 0.5 && voltage <= 3.5) {
    pressure_mbar = (voltage - 0.66) * (100.0 / (3.3 - 0.66));
    pressure_mmHg = pressure_mbar * 0.75006;  // Convert mbar to mmHg
  }
  // if (voltage >= 1.88 && voltage <= 9.4) {
  //   pressure_mbar = (voltage - 1.88) * (100.0 / (9.4 - 1.88));
  //   pressure_mmHg = pressure_mbar * 0.75006;  // Convert mbar to mmHg
  // } 
  else {
    pressure_mbar = 0;  // Out-of-range voltages result in zero pressure
    pressure_mmHg = 0;
  }

  Calculate current (assuming 470-ohm resistance)
  current = voltage / 470.0;

  // Print results
  Serial.print("Raw Value: ");
  Serial.println(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V | Current: ");
  Serial.print(current * 1000, 6);  // Print current with higher precision
  Serial.print(" mA | Pressure: ");
  Serial.print(pressure_mmHg, 2);
  Serial.println(" mmHg");

  delay(500);  // Delay for readability
}