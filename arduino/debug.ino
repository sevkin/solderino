/*
 * отладочная информация в последовательный порт (конфликтует с display)
 */

// температура в градусах заданная потенциометром
extern unsigned int presetCelsius;

// температура в градусах измеренная термопарой/термистором
extern unsigned int measuredCelsius;

// значение ШИМ для нагревателя паяльника
extern unsigned char heaterPWM;

inline static void initDebug () {
  Serial.begin(9600);
}

bool updateDebug (/*unsigned long last*/) {
//  Serial.print(last);
//  Serial.print(" ");
  Serial.print(presetCelsius);
  Serial.print(" ");
  Serial.print(measuredCelsius);
  Serial.print(" ");  
  Serial.println(heaterPWM);
  return false;
}


