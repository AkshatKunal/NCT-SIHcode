#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd; // Initialize the LCD object

const int lcdColumns = 16;
const int lcdRows = 2;

void setup() {
  lcd.begin(lcdColumns, lcdRows); // Initialize the LCD
  
  lcd.print("Hello, ESP32!"); // Print message
  delay(2000); // Wait 2 seconds

  lcd.clear(); // Clear the display
}

void loop() {
  // Set cursor to (0, 0)
  lcd.setCursor(0, 0);
  lcd.print("Top Left!");

  // Set cursor to the second row, column 0
  lcd.setCursor(0, 1);
  lcd.print("Row 2 Start");

  delay(2000);

  lcd.clear(); // Clear the screen again
  delay(1000); // Pause before updating
}
