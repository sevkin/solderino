/*
 * отображение заданной / измеренной температуры на 3-разрядном 7-сегментном индикаторе 
 */

#include <SevSeg.h>

// пин, к которому подключена точка
// const int dpPin = 5;

// https://github.com/DeanIsMe/SevSeg
SevSeg Display;

// температура в градусах заданная потенциометром
extern unsigned int presetCelsius;

// температура в градусах измеренная термопарой/термистором
extern unsigned int measuredCelsius;

inline static void initDisplay () {
//  byte digitPins[] = {A3, 0, 1};
//  byte segmentPins[] = {8, 2, 4, 7, 9, 6, 3, 5};
  byte digitPins[] = {0, 1, A3};
  byte segmentPins[] = {2, 4, 8, 6, 5, 3, 9, 7};
  Display.begin(COMMON_ANODE, 3, digitPins, segmentPins, true /* resistors on segments */);
//  Display.setBrightness(90);
  Display.blank();  
}

unsigned long lastPreset(0);

inline static void displayPreset() {
  // TODO зажигать все точки при отображении заданной температуры
  Display.setNumber(presetCelsius, 0);
  // грязный хак. Зажечь все точки в обход SevSeg [не работает]
//  digitalWrite(dpPin, LOW);
  // последнее изменение заданной температуры - отложить отображение измеренной на 1 сек
  lastPreset = millis() + 2000;
}

inline static void displayMeasured() {
  if( lastPreset > 0 ) {
    if( lastPreset <= millis() ) {
      lastPreset = 0;
    } else return;
  }
  Display.setNumber(measuredCelsius, 3);
}

bool updateDisplay () {
  // TODO динамическая индикация бегущих точек при нагреве/остывании
  if( lastPreset > 0 ) {
    if( lastPreset <= millis() ) {
      lastPreset = 0;
      Display.setNumber(measuredCelsius, 3);
    }
  }
  Display.refreshDisplay();
  return false;
}



