#include <avr/io.h>
#include <avr/interrupt.h>
int trigPin = 9;
int extraTime;
volatile bool state = false;
int ledPin = 6;
int fadeAmount = 5;
int brightness = 0;

void setup() {
  // put your setup code here, to run once:
  // DDRB = 0x01;//Set LED as O/P
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(trigPin, LOW);

  TCCR0A = (1 << WGM01);// Make it to CTC- clear on compare
  OCR0A = 156;//Comparing number - that we want
  TIMSK0 = (1 << OCIE0A);//Sets the interrupt

  sei();//Set External interrupt

  TCCR0B = (1 << CS02)| (1<< CS00);//Prescaler to 1024
}

ISR(TIMER0_COMPA_vect)//Interrupt Service routine - Called when interrupt Occurs
{
  if (state){
    tone(trigPin, 40000);
  }else{
    noTone(trigPin); 
  }
  state = !state;
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(ledPin, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
