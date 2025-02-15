// Pin Definitions
const int triggerPin = 9;  // Trigger pin for HC-SR04
const int receiverPin = A0;  // Analog pin for MA40S4R receiver

// Variables to store max signal and timing
int maxSignal = 0;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Set up the trigger pin as output
  pinMode(triggerPin, OUTPUT);

  // Initialize trigger pin to LOW
  digitalWrite(triggerPin, LOW);
}

void loop() {
  // Trigger the HC-SR04 to send a 40kHz ultrasonic pulse
  triggerHCSR04();

  // Sample the signal from the MA40S4R receiver for a short period
  sampleReceiverSignal();

  // Short delay before the next loop iteration
  delay(500);
}

// Function to trigger the HC-SR04
void triggerHCSR04() {
  // Send a 10us HIGH pulse to the trigger pin of HC-SR04
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);  // Wait for 10 microseconds
  digitalWrite(triggerPin, LOW);  // Set trigger pin back to LOW
}

// Function to sample the signal from MA40S4R receiver
void sampleReceiverSignal() {
  // Reset maxSignal for each new sampling period
  maxSignal = 0;

  // Sample for a fixed duration (e.g., 100 ms)
  unsigned long startTime = millis();
  while (millis() - startTime < 100) {
    // Read the analog value from the receiver
    int rawSignal = analogRead(receiverPin);

    // Track the maximum value recorded during this period
    if (rawSignal > maxSignal) {
      maxSignal = rawSignal;
    }
  }

  // Convert the max reading to voltage
  float maxVoltage = maxSignal * (5.0 / 1023.0);  // Assuming 5V reference voltage

  // Output the max signal and corresponding voltage to Serial Monitor
  Serial.print("Max ADC Value: ");
  Serial.print(maxSignal);
  Serial.print("\tMax Voltage: ");
  Serial.print(maxVoltage, 3);  // Display voltage with 3 decimal places
  Serial.println(" V");
}