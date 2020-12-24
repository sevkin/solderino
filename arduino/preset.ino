/*
 * установка температуры потенциометром 10K
 */

// порт потенциометра задающего температуру
const int presetPin = A0;

// температура в градусах заданная потенциометром
unsigned int presetCelsius;

inline static void initPreset() {
     pinMode(presetPin, INPUT);
     presetCelsius = 0;
}

bool updatePreset () {
  // шаг задания температуры для защиты от дребезга
  // TODO не помогает - просадка напряжения при нагреве, нужен Калман?
  const unsigned int deltaTemp = 5;

  // диапазон регулирования температуры
  const unsigned int minTemp = 190;
  const unsigned int maxTemp = 430;

  // диапазон значений потенциометра задающего температуру
  const unsigned int minPot = 10;
  const unsigned int maxPot = 1020;

  unsigned int newTemp = map(analogRead(presetPin), minPot, maxPot, minTemp, maxTemp);
  if(abs(newTemp - presetCelsius) >= deltaTemp) {
    presetCelsius = newTemp;
    return true;
  }
  
  return false;
}


