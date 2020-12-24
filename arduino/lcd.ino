/*
 * отображение заданной / измеренной температуры на дисплее 16х2 подключенном по i2c
 */


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
// показометр на экранчике 16х2 с адаптером I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // A4 - SDA A5 - SCL 16x2

// температура в градусах заданная потенциометром
extern unsigned int presetCelsius;

// температура в градусах измеренная термопарой/термистором
extern unsigned int measuredCelsius;

void initLCD () {
  lcd.init();
  lcd.backlight();

  lcd.home();
}

bool updateLCD () {
  lcd.setCursor(0,0);
  lcd.print(presetCelsius);
  
  lcd.setCursor(0,1);
  lcd.print(measuredCelsius);  

  return false;
}


