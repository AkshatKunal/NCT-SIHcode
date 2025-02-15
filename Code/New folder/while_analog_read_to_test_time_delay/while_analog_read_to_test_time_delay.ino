int trigPin = 9;
int thresh;
int sensPin = A0;
int sensVal;
unsigned long endTime;
int tresh = 100;

#include <avr/io.h>
#include <avr/interrupt.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(sensPin, INPUT);  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, HIGH);
  unsigned long startTime = millis();
  Serial.println("Void");
  Serial.println(millis());

  while(1) {
    sensVal = analogRead(sensPin);
    Serial.println("SensVal");
    Serial.println(sensVal);
    Serial.println("While");
    Serial.println(millis());
    if (sensVal > tresh) {
      endTime = millis();
      digitalWrite(trigPin, LOW);
      break;
    }
  }
  unsigned long diffTime = endTime - startTime;
  Serial.println(diffTime);
  digitalWrite(trigPin, HIGH);
}
