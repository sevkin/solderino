/*
 * измерение температуры термопарой через драйвер max6675
 */
 
#include <SPI.h>

// порты термодатчика
const int measurePinCS =  A1;
//const int measurePinDO =  12;
//const int measurePinCLK = 13;

// температура в градусах измеренная термопарой/термистором
unsigned int measuredCelsius;

void initMeasured () {
  SPI.begin();  
  pinMode(measurePinCS, OUTPUT);
}

bool updateMeasured () {
  digitalWrite(measurePinCS, LOW);
  unsigned int T = SPI.transfer(0x00);
  T <<= 8;
  T |= SPI.transfer(0x00);
  digitalWrite(measurePinCS, HIGH);
  
  if( T & 0x4 ) {
  // uh oh, no thermocouple attached!
    measuredCelsius = 999;
    return true; // TODO true == changed
  }

  const unsigned int deltaTemp = 2;
  
  unsigned int temp = round((T >> 3) * 0.25);
  if( abs(measuredCelsius - temp) >= deltaTemp ) {
    measuredCelsius = temp;
    return true;
  }
  
  return false;
}


