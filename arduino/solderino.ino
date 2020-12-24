/*
 * solderino (ардуяльник) soldering iron + arduino
 * 
 * наикрутейшая паяльная станция из *овна и ватных палок
 * 
 * с ШИМ`ом, ПИД`ом и фильтром Калмана (скоро)
 */

void setup() {
  initPreset();
  initMeasured();
  initHeater();
  initDisplay(); // 7 segment
  // семисегментный индикатор мешает отладке
//  initDebug();
//  initLCD(); // 16x2 + i2c
}

// количество миллисекунд c начала предыдущего вызова loop
unsigned long loopMillis;

// вызывать функцию func не чаще чем step миллисекунд (не всякий ардуинщик долетит до середины...)
bool debounce(unsigned long step, unsigned long *last, bool (*func) () ) {
  *last += loopMillis;
  if( *last >= step ) {
    bool result = func();
    *last = 0;
    return result;
  } 
  return false;
}

// суперцикл - вызывать все задачи по очереди с требуемой периодичностью
void loop() {
  // это-же С++ статики инициализировать типа конструктором
  static unsigned long pm(0);
  unsigned long m = millis();
  // количество миллисекунд с предыдущего вызова loop
  loopMillis = m - pm;
  pm = m;

  static unsigned long lastPreset(0);
  // обновлять значение заданной температуры не чаще чем раз в 200 миллисекунд
  if( debounce(200, &lastPreset, &updatePreset) ) {
    displayPreset();
  }

  static unsigned long lastMeasured(0);
  // обновлять значение измеренной температуры не чаще чем раз в 200 миллисекунд
  if( debounce(200, &lastMeasured, &updateMeasured) ) {
    displayMeasured();
  }

  static unsigned long lastHeater(0);
  // обновлять значение PWM нагревателя не чаще чем раз в 200 миллисекунд
  debounce(200, &lastHeater, &updateHeater);
  
  static unsigned long lastDisplay(0);
  // обновлять показания дисплея не чаще чем раз в 5 миллисекунд
  debounce(5, &lastDisplay, &updateDisplay);

//  static unsigned long lastDebug(0);
//  debounce(1000, &lastDebug, &updateDebug);

//  static unsigned long lastLCD(0);
//  debounce(1000, &lastLCD, &updateLCD);
}

