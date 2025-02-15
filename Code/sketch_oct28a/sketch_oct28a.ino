#define TRIG_PIN 9 // Pin for triggering the ultrasonic transmitter
const int TIME_ON = 10; // Time interval in milliseconds
unsigned long timer; // Variable to store the last time the pulse was toggled
volatile bool state = true; // Track the state of the pulse (ON/OFF)

void setup() {
  pinMode(TRIG_PIN, OUTPUT); // Set the pin as output
  timer = millis();
  Serial.begin(9600); // Initialize the timer
}

void tog() {
  if (state) {
    tone(TRIG_PIN, 40000); // Start 40 kHz tone
  } else {
    noTone(TRIG_PIN); // Stop the tone
    digitalWrite(TRIG_PIN, LOW);
  }
  state = !state; // Toggle the state
  timer = millis(); // Reset the timer after toggling
}

void loop() {
  if (millis() - timer >= TIME_ON) {
    tog();
    Serial.println(state); // Call the toggle function if the time has elapsed
  }

  // Other code can run here without affecting the pulse generation
}