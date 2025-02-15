#include <avr/io.h>
#include <avr/interrupt.h>

int trigPin = 9; // Transmitter pin
int receiverPin = A5; // Receiver pin
volatile bool state = false;
int n = 500; // Number of samples for RMS calculation
float outputSumSquares = 0;
float vRms;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(receiverPin, INPUT);
  digitalWrite(trigPin, LOW);

  // Configure Timer1 for amplitude modulation (40kHz carrier with modulated waveform)
  TCCR1A = 0;
  TCCR1B = (1 << WGM12); // CTC mode
  OCR1A = 400; // 40kHz signal (adjust as per your clock speed)
  TIMSK1 = (1 << OCIE1A); // Enable Timer1 compare interrupt

  sei(); // Enable global interrupts

  TCCR1B |= (1 << CS10); // Start Timer1 with no prescaler

  // Begin Serial communication
  Serial.begin(9600); // Ensure Serial Monitor matches this baud rate
}

ISR(TIMER1_COMPA_vect) {
  // Generate a 40kHz square wave on the transmitter pin
  if (state) {
    digitalWrite(trigPin, HIGH);
  } else {
    digitalWrite(trigPin, LOW);
  }
  state = !state;
}

void loop() {
  outputSumSquares = 0;

  // Collect RMS data from the receiver
  for (int i = 0; i < n; i++) {
    float outputVoltage = analogRead(receiverPin) * (5.0 / 1023.0); // Convert ADC value to voltage
    outputSumSquares += outputVoltage * outputVoltage;
  }

  // Calculate RMS voltage
  vRms = sqrt(outputSumSquares / n);

  // Send data to Serial Monitor and Plotter
  Serial.println(vRms);

  delay(100); // Adjust sampling rate
}