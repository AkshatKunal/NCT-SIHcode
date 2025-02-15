// Define pins
#define TRIG_PIN D1  // Trigger pin of HC-SR04
#define ECHO_PIN D2  // Echo pin of HC-SR04

// Variables to track time and distance
long duration;
float distance;
unsigned long startTime;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  // Set pins as input/output
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  // Record the start time
  startTime = millis();
  Serial.print("Time(s), ");
  Serial.print("Distance(s), ");
  //Serial.println();
}

void loop() {
  // Clear the TRIG_PIN
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pulse
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance (speed of sound = 34300 cm/s)
  distance = (duration * 0.0343) / 2;

  // Calculate elapsed time
  float elapsedTime = (millis() - startTime) / 1000.0;

  // Print results to Serial Monitor
    Serial.print(elapsedTime);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(",");
    //Serial.println();
  // if (distance >= 2 && distance <= 400) {
  //   Serial.print(elapsedTime);
  //   Serial.print(" s, ");
  //   Serial.print(distance);
  //   Serial.println(" cm");
  // } else {
  //   Serial.println("Out of range");
  // }

  // Wait before the next measurement
  delay(1000);
}