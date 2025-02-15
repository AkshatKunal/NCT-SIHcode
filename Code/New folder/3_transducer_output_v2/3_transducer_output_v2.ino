// include the library code:


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD (Address might differ, use 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);
int trigPin = 22;
int signalWave = 23;
int sensPin = 34;
int pressureSensorPin = 35;
float sensVal;
float startTime;
float recieveTime;
float omega;
float time1;
float sineVal;
float voltage;
float waveAmplitude;
float pressure_mbar;
float pressure_mmHg;
float pi = 3.14159;
int rawValue;

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 https://docs.arduino.cc/learn/electronics/lcd-displays

*/



// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(signalWave, OUTPUT);
  pinMode(sensPin, INPUT);  
  Serial.begin(115200);
  omega = (2 * pi * 40000);
  Serial.print("pressure_mmHg, ");
  Serial.print("sensVal, ");
  Serial.print("waveAmplitude, ");
  Serial.println();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.init();             // Initialize the LCD
  lcd.backlight();        // Turn on backlight
  lcd.setCursor(0, 0);
  lcd.print("Waiting Data...");


}

void loop() {
  // put your main code here, to run repeatedly:
  rawValue = analogRead(pressureSensorPin);  
  voltage = rawValue * (5.0 / 1023.0);  // Convert to voltage (assuming a 5V reference)
  // Convert voltage to pressure in mbar
  if (voltage >= 1.88 && voltage <= 9.4) {
    pressure_mbar = map(voltage * 100, 188, 940, 0, 100);  // Map from 1.88V-9.4V to 0-100mbar
    pressure_mmHg = pressure_mbar * 0.75006;  // Convert mbar to mmHg
  } else {
    pressure_mbar = 0;    // Consider out-of-range voltages as zero pressure
    pressure_mmHg = 0;  
    // Serial.println(); 
  } 

  Serial.print(pressure_mmHg);
  Serial.print(",");


  tone(signalWave,50);
  delay(100);
  digitalWrite(signalWave,LOW);

  //tone(trigPin,40000);
  digitalWrite(trigPin,HIGH);
  startTime = millis();
  delay(2);

  // digitalWrite(signalWave,LOW);

  sensVal = analogRead(sensPin);
  Serial.print(sensVal);
  Serial.print(",");
  recieveTime = millis();
  time1 = (recieveTime - startTime);
  // Serial.print(time);
  // Serial.print(",");
  sineVal = sin((omega * time1)/1000);
  waveAmplitude = sensVal/sineVal;

  digitalWrite(trigPin,LOW);

  Serial.print(waveAmplitude);
  Serial.println(",");
  delay(10);

    if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');  // Read data from Python
    lcd.clear();                                // Clear the LCD
    lcd.setCursor(0, 0);
    lcd.print("Avg SensVal x72:");
    lcd.setCursor(0, 1);
    lcd.print(data);  // Display the received value on the second row
    Serial.println("Value Received: " + data);  // Echo back to serial monitor
  }
}


