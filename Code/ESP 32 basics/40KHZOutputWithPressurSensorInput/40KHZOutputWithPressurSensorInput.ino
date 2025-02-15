// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int potPin = 2;

// variable for storing the potentiometer value
int potValue = 0;

const int pwmPin = 5;   // Pin to output PWM
const int pwmChannel = 0;  // PWM channel (0-15 available)
const int pwmResolution = 8; // Resolution (8-bit)
const int pwmFrequency = 30; // Frequency in Hz (40 kHz)

void setup() {
    // Configure PWM
  ledcSetup(pwmChannel, pwmFrequency, pwmResolution);
  
  // Attach the PWM channel to the pin
  ledcAttachPin(pwmPin, pwmChannel);

  // Set duty cycle (50% of 8-bit resolution = 128)
  // ledcWrite(pwmChannel, 128);

  Serial.begin(115200);
  delay(1000);
  Serial.println("Started");
  ledcWriteTone(0, 40000);
  Serial.println("Started2");
}

void loop() {
  // ledcWriteTone(0, 40000);
  // delay(5000);
  // Reading potentiometer value
  potValue = analogRead(potPin);
  Serial.println(potValue);
  delay(500);
}