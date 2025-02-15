// Define pins for the HC-SR04 sensor
const int trigPin = 9;
const int echoPin = 10;

// Variables to store duration and distance
long duration;
int distance;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Set the trigPin as output and echoPin as input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10µs pulse to trigPin to start measurement
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo signal (in microseconds)
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance (speed of sound is ~34300 cm/s in air)
  distance = duration * 0.034 / 2;

  // Print the distance on Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Delay for readability in the Serial Monitor
  delay(500);
}