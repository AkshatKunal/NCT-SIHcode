// Include necessary libraries
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;

#define BLYNK_TEMPLATE_ID "TMPL3zkcfEQ5v"
#define BLYNK_TEMPLATE_NAME "Tonometer"
#define BLYNK_AUTH_TOKEN "TwYAh3EG-Z7_V-vPO7nsVupEmuYnkAxU"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

const char ssid[] = "AkLava";       // Wi-Fi SSID
const char pass[] = "12345678";  // Wi-Fi Password

const int pwmPin = 2;               // Pin to output PWM
const int pwmChannel = 0;           // PWM channel (0-15 available)
const int pwmResolution = 8;        // Resolution (8-bit)
const int pwmFrequency = 40000;     // Frequency in Hz (40 kHz)

unsigned long numberMillis = 0;     // Timer for sending numbers
int start = 1;                      // Start of the range
int end = 10;                       // End of the range
int current = 0;                    // Current number
bool processing = false;            // Flag to indicate the process is running
float sumPressure = 0;              // Sum of pressure values
int receiverUltrasoundPin = 4;      // Ultrasound receiver pin
const float pressureSlope = 11.53;
const float pressureIntercept = 476.88;

bool alarmActive = false;           // Flag to indicate alarm is active
unsigned long alarmStartMillis = 0; // Timer for alarm duration (10 seconds)

// Switch to control alarm manually
BLYNK_WRITE(V7) {
  int switchState = param.asInt();
  if (switchState == 0 && alarmActive) {
    // Turn OFF alarm if switch is toggled OFF
    stopAlarm();
  }
}

BLYNK_WRITE(V4) { // Button on virtual pin V4
  int pinValue = param.asInt();
  if (pinValue == 1 && !processing) {
    // Start processing when button is turned ON
    processing = true;
    current = start;
    sumPressure = 0;
  }
}

void setup() {
  Serial.begin(115200);                           // Start Serial communication
  pinMode(receiverUltrasoundPin, INPUT);          // Set ultrasound receiver pin as input
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);      // Connect to Wi-Fi and Blynk

  ledcSetup(pwmChannel, pwmFrequency, pwmResolution);
  ledcSetup(3, 50, pwmResolution);
  
  // Attach the PWM channel to the pin
  ledcAttachPin(pwmPin, pwmChannel);
  ledcAttachPin(19, 3);

  ledcWriteTone(0, 40000);
  ledcWriteTone(3, 50);

  lcd.begin(16, 2); // Initialize the LCD
  lcd.clear(); // Clear the display
}

void loop() {
  Blynk.run(); // Run Blynk

  // If processing, handle timing for counting numbers
  if (processing && millis() - numberMillis >= 1000) {
    numberMillis = millis();
    processNumbers();
  }
      
  // Handle alarm duration
  if (alarmActive && millis() - alarmStartMillis >= 10000) {
    stopAlarm(); // Stop alarm after 10 seconds
  }
}

void processNumbers() {
  if (current <= end) {
    // Read the ultrasound receiver value
    int receiverValue = analogRead(4);

    // Calculate the ratio and pressure
    float ratio = receiverValue; // Normalize to 0-1 range
    Serial.print("Value: ");
    Serial.println(receiverValue);
    float pressure = (ratio  - pressureIntercept) / pressureSlope;

    // Add the current pressure value to the sum
    sumPressure += pressure;

    // Print the value to Serial Monitor
    Serial.print("Number: ");
    Serial.print(current);
    Serial.print(" - Pressure: ");
    Serial.println(pressure);

    // Increment the current number
    current++;
  } else if (processing) {
    // Process is complete
    processing = false;

    // Calculate the average pressure
    float averagePressure = sumPressure / float(end - start + 1);

    // Print the average to Serial Monitor
    Serial.print("Average Pressure: ");
    Serial.println(averagePressure);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pressure in mmHg");
    lcd.setCursor(0, 1);
    lcd.print(averagePressure);

    // Send results to Blynk Terminal
    Blynk.virtualWrite(V5, "Process Complete!\n");
    Blynk.virtualWrite(V5, "Average Pressure: " + String(averagePressure) + "\n");

    // Turn OFF the button widget (V4)
    Blynk.virtualWrite(V4, 0);

    // Activate alarm: send a notification and toggle the LED widget
    startAlarm();
  }
}

void startAlarm() {
  alarmActive = true;
  alarmStartMillis = millis();
  Blynk.virtualWrite(V6, 1); // Turn ON alarm widget (e.g., LED on virtual pin V6)
  Blynk.virtualWrite(V7, 1); // Set the switch to ON state
  Serial.println("Alarm Activated!");
}

void stopAlarm() {
  alarmActive = false;
  Blynk.virtualWrite(V6, 0); // Turn OFF alarm widget
  Blynk.virtualWrite(V7, 0); // Set the switch to OFF state
  Serial.println("Alarm Stopped!");
}
