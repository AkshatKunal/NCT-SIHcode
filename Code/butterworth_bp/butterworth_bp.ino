#include <Filters.h>
 
#include <AH/Timing/MillisMicrosTimer.hpp>
#include <Filters/Butterworth.hpp>
 
void setup() {
  Serial.begin(115200);
}
 
// Sampling frequency
const double f_s = 100000; // Hz
// Lower and upper cutoff frequencies (-3 dB)
const double f_l = 40000; // Hz
const double f_u = 40010; // Hz
// Normalized lower and upper cutoff frequencies
const double f_n1 = 2 * f_l / f_s;
const double f_n2 = 2 * f_u / f_s;
 
// Sample timer
Timer<micros> timer = std::round(1e6 / f_s);
 
// Second-order bandpass Butterworth filter
auto filter = butterworth(f_n1, f_n2, LOWPASS);
 
void loop() {
  if (timer)
    Serial.println(filter(analogRead(A0)));
}