#define GPIO_OUTPUT 2       // Pin to output the wave
#define WAVE_FREQ 40000     // Frequency in Hz
#define PWM_RESOLUTION 8    // Resolution in bits (8 bits for simplicity)

void setup() {
  // Configure LEDC channel 0 for 40kHz frequency
  ledcSetup(0, WAVE_FREQ, PWM_RESOLUTION); // Channel 0, 40kHz, 8-bit resolution
  ledcAttachPin(GPIO_OUTPUT, 0);           // Attach GPIO 2 to LEDC Channel 0

  // Start generating the wave
  ledcWrite(0, 128); // 50% duty cycle (128 out of 255 for 8-bit resolution)
}

void loop() {
  // No code needed here
}
