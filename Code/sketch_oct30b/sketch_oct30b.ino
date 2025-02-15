#include <avr/io.h>
#include <avr/interrupt.h>

int trigPin = 9;
volatile bool state = false;
int ledPin = 6;
int fadeAmount = 5;
int brightness = 0;
int receiverPin = A5;
float outputVoltage;
float highVolt;
float Z0;
float Z1;
float Z2;
float Z3;
float a0;
float a1;
float K;
float IOP;
float m;
float c;
int list1[500] = {};
float outputSumSquares = 0;
int n = 1000; //Number of samples taken for rms 
int vRms;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(trigPin, LOW);

  // Configure Timer1 for CTC mode - Creates the input signal/ wave - do not touch 
  TCCR1A = 0;               // Clear Timer1 control register A
  TCCR1B = (1 << WGM12);    // Set CTC mode (Clear Timer on Compare Match)
  OCR1A = 625;              // Set compare value for 1ms intervals (assuming 16MHz clock with 1024 prescaler)
  TIMSK1 = (1 << OCIE1A);   // Enable Timer1 compare interrupt

  sei();                    // Enable global interrupts

  // Start Timer1 with a 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  Serial.begin(9600);
}

ISR(TIMER1_COMPA_vect) {// Sets the wave - do not touch 
  // Toggle state and produce 40kHz signal
  if (state) {
    tone(trigPin, 40000);
  } else {
    noTone(trigPin);
    digitalWrite(trigPin, LOW);
  }
  state = !state;
}

void loop() {// the calculation thingy - u can do stuff
  for (int i=0;i<n;i++){
    delay(1);
    outputVoltage = analogRead(receiverPin);
    // if(outputVoltage > highVolt){ //- for maximum val of the peak
    //   highVolt = outputVoltage;
    // }
    outputSumSquares = outputSumSquares + (pow(outputVoltage,2));// to calculate the Vrms
  }
  vRms = sqrt(outputSumSquares/n) ;

  // Serial.println(vRms); //if u want, u can change the vRms here to highVolt to get the maxvoltage printed
  Serial.println(outputVoltage);
  outputSumSquares = 0;
  vRms = 0;
  delay(100);
  //Serial.println(vRms);
  // outputVoltage = analogRead(receiverPin); //to print out the direct wave form as it is
  // Serial.println(outputVoltage);
  Z1 = (Z0 *(A0 + A1))/(A0 - A1);//Unnecessary for now - the mathematical eqns
  K = (A0*(Z1 + Z0)*(Z1 + Z0))/(Z2*4*Z1*Z0);
  Z2 = (Z3*(1 - K))/(1 + K);
  IOP = m*Z2 - c;
}
