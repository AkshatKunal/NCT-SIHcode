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
void loop() {
  // put your main code here, to run repeatedly:

}
