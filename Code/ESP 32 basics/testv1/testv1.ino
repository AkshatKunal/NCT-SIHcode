#include <AsyncUDP.h>

#include <Arduino.h>
#include "esp32-hal.h"
// It's all part of the SFM (Sheer Fu**ing Magic) 

const int PWM_CHANNEL = 0;    // ESP32 has 16 channels which can generate 16 independent waveforms
const int PWM_FREQ = 40000;     // Recall that Arduino Uno is ~490 Hz. Official ESP32 example uses 5,000Hz
const int PWM_RESOLUTION = 8; // We'll use same resolution as Uno (8 bits, 0-255) but ESP32 can go up to 16 bits 
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 

const int transmitterPin = 2;
const int recieverPin = 4;

int recieveValue = 5000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);

  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(transmitterPin, PWM_CHANNEL);

}

void loop() {
  // put your main code here, to run repeatedly:
  ledcWrite(PWM_CHANNEL, MAX_DUTY_CYCLE);
  digitalWrite(2,HIGH);
  delay(100);
  recieveValue = analogRead(recieverPin);
  Serial.println(recieveValue);
  digitalWrite(transmitterPin,LOW);
  digitalWrite(2,LOW);
  delay(400);
}
