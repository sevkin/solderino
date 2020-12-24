
// https://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/
// https://code.google.com/archive/p/tinkerit/wikis/SecretVoltmeter.wiki
// https://hackingmajenkoblog.wordpress.com/2016/02/01/making-accurate-adc-readings-on-the-arduino/

long readVcc() {
  long result; // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1); // atmega368 or atmega168 only
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while( bit_is_set(ADCSRA, ADSC) );
  result = ADCL;
  result |= ADCH<<8; 
//  return 1125300L / result; // Back-calculate AVcc in mV
  return 1126400L / result; // Back-calculate AVcc in mV
}

