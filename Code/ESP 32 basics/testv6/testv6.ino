#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;

// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int receivePin = 2;
int receiverUltrasoundPin = 4;

const float pressureSlope = 11.53;
const float pressureIntercept = 476.88;

// variable for storing the potentiometer value
int receiverValue = 0;

int i = 0;
float pressure_mmHgSum = 0;
float pressure_mmHg1 = 0;

const int pwmPin = 5;   // Pin to output PWM
const int pwmChannel = 0;  // PWM channel (0-15 available)
const int pwmResolution = 8; // Resolution (8-bit)
const int pwmFrequency = 30; // Frequency in Hz (40 kHz)

int a =0;

void setup() {
    // Configure PWM
  ledcSetup(pwmChannel, pwmFrequency, pwmResolution);
  ledcSetup(3, 50, pwmResolution);
  
  // Attach the PWM channel to the pin
  ledcAttachPin(pwmPin, pwmChannel);
  ledcAttachPin(19, 3);

  // Set duty cycle (50% of 8-bit resolution = 128)
  // ledcWrite(pwmChannel, 128);

  Serial.begin(115200);
  delay(1000);
  // Serial.println("Started");
  ledcWriteTone(0, 40000);
  ledcWriteTone(3, 50);
  // Serial.println("Started2");
  lcd.begin(16, 2); // Initialize the LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Start:");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reading....");

  while (true) {
    // voltage = rawValue * (5.0 / 1023.0);  // Convert to voltage (assuming a 5V reference)
  // // Convert voltage to pressure in mbar
  // if (voltage >= 1.88 && voltage <= 9.4) {
  //   pressure_mbar = map(voltage * 100, 1588, 940, 0, 100);  // Map from 1.88V-9.4V to 0-100mbar
  //   pressure_mmHg = pressure_mbar * 0.75006;  // Convert mbar to mmHg
  // } else {
  //   pressure_mbar = 0;    // Consider out-of-range voltages as zero pressure
  //   pressure_mmHg = 0;  
  //   // Serial.println(); 
  // } 

  receiverValue = analogRead(receivePin);
  // Serial.print(receiverValue);
  // Serial.print(": ");
  float actualVoltage = (receiverValue * 3.3 )/4095;
  // Serial.print(actualVoltage);
  // Serial.print(": ");
  float current = 3.9;
  if (actualVoltage > 0.65){
  current = (actualVoltage * 1000)/180;
  // Serial.print(current);
  // Serial.print(": Reciever: ");
  } 
  float receiverUltrasound = analogRead(receiverUltrasoundPin);
  // Serial.print(receiverUltrasound);
  // Serial.print(": ");
  //map(current,4.00,20.00,0.00,100.00);
  //map(current, lowCurrrent, highCurret, lowPressure,highPressure)
  float pressureMbar = ((current - 4)*100)/(16);
  // float pressure_mmHg = pressureMbar * 0.75006;  // Convert mbar to mmHg
  float pressure_mmHg = (receiverUltrasound  - pressureIntercept) / pressureSlope;
  i++;
  pressure_mmHgSum += pressure_mmHg;
  if (i >= 100){
    pressure_mmHg1 = pressure_mmHgSum/i ;
    Serial.print("Avg Pressure: ");
    Serial.println(pressure_mmHg1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pressure in mmHg");
    lcd.setCursor(0, 1);
    lcd.print(pressure_mmHg1);
    i=0;
    pressure_mmHgSum = 0;
    delay(20000);
    // if (a == 0){
    //   a++;
    //   ESP.restart();
    // }
    break;
  }
  // Serial.println(pressure_mmHg);
  // Serial.print(receiverValue);
  // Serial.print(": ");
  // Serial.print(actualVoltage);
  // Serial.print(": ");
  // Serial.print(current);
  // Serial.print(": ");
  // Serial.print(receiverUltrasound);
  // Serial.print(": ");
  Serial.println(pressure_mmHg);
  delay(100);
  }
  Serial.println("Out of setup loop");
}

void loop() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Done Reading");
  
}