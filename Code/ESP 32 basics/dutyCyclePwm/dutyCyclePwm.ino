const int PWM_CHANNEL = 0;    // ESP32 has 16 channels which can generate 16 independent waveforms
const int PWM_FREQ = 500;     // Recall that Arduino Uno is ~490 Hz. Official ESP32 example uses 5,000Hz
const int PWM_RESOLUTION = 8; // We'll use same resolution as Uno (8 bits, 0-255) but ESP32 can go up to 16 bits 

// The max duty cycle value based on PWM resolution (will be 255 if resolution is 8 bits)
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 

const int LED_OUTPUT_PIN = 2;

const int DELAY_MS = 4;  // delay between fade increments

void setup() {

  // Sets up a channel (0-15), a PWM duty cycle frequency, and a PWM resolution (1 - 16 bits) 
  // ledcSetup(uint8_t channel, double freq, uint8_t resolution_bits);
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);

  // ledcAttachPin(uint8_t pin, uint8_t channel);
  ledcAttachPin(LED_OUTPUT_PIN, PWM_CHANNEL);
}

void loop() {

  // fade up PWM on given channel
  for(int dutyCycle = 0; dutyCycle <= MAX_DUTY_CYCLE; dutyCycle++){   
    ledcWrite(PWM_CHANNEL, dutyCycle);
    delay(DELAY_MS);
  }

  // fade down PWM on given channel
  for(int dutyCycle = MAX_DUTY_CYCLE; dutyCycle >= 0; dutyCycle--){
    ledcWrite(PWM_CHANNEL, dutyCycle);   
    delay(DELAY_MS);
  }
}


/*
 ESP32 DAC Sine Wave Generation
 http:://www.electronicwings.com
*/

int Sin_Array[256];                 // Define array to store sine wave values
float Period = (2*PI)/256;          // Define the sine wave conversion factor
float Rad_Angle;                   

void setup(){
 for(int Angle=0; Angle<256; Angle++) {
   Rad_Angle = Angle*Period;       // calculate the angle in radian
   Sin_Array[Angle] = (sin(Rad_Angle)*127)+128;  // caclulate the anagle and shift by 128
 }
}

void loop(){
 for(int i=0;i<256;i++)
   dacWrite(25,Sin_Array[i]);       // Write the sinewave vale on the DCA pin
}