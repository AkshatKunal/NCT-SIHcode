float A0 = ;
float A1;
float Z0 = ;
float Z1;
float Z2;
float Z3 = ;
float IOP;
float m = ;
float c = ;
float k;

#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop() {
  // put your main code here, to run repeatedly:
  Z1 = (Z0 *(A0 + A1))/(A0 - A1);
  k = (A0*(Z1 + Z0)*(Z1 + Z0))/(A2*4*Z1*Z0);
  Z2 = (Z3*(1 - K))/(1 + K);
  IOP = m*Z2 - c;

  lcd.print("hello, world!");
  lcd.print(IOP);
}

// https://docs.arduino.cc/learn/electronics/lcd-displays/
