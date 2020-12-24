/*
 * нагрев паяльника, подключенного через полевой транзистор ШИМ`ом 
 */

// порт нагревателя (с ШИМ)
const int heaterPin = 10;

// температура в градусах заданная потенциометром
extern unsigned int presetCelsius;

// температура в градусах измеренная термопарой/термистором
extern unsigned int measuredCelsius;

// значение ШИМ для нагревателя паяльника
unsigned char heaterPWM;

void initHeater () {
  pinMode(heaterPin, OUTPUT);
  analogWrite(heaterPin, 0);  

// транзистор чуть греется, еле слышно шуршит
  setPwmFrequency(heaterPin, 1024); // ~30 Hz
// не шуршит но греется зараза  
//  setPwmFrequency(heaterPin, 1); // ~30 kHz
// по умолчанию назойливо шуршит
//  setPwmFrequency(heaterPin, 256);
}

bool updateHeater () {

unsigned int pwm = 0;
  
  if( measuredCelsius > 0 ) {
    // не перегревать
    if( measuredCelsius > 430 ) { pwm = 0;   } else
    // аккуратно разогреть
    // актуально для керамического нагревателя
    // у него холодный ток 6А, с нагревом растет сопротивление
    // TODO растет ли?
    if( measuredCelsius < 50 )  { pwm = 63;  } else
    if( measuredCelsius < 100 ) { pwm = 127; } else
    if( measuredCelsius < 150 ) { pwm = 255; } else

    if( measuredCelsius < presetCelsius ) {
      // TODO: PID here ! а пока дешевая замена  
      int tempDiff = presetCelsius - measuredCelsius;
      if( tempDiff >= 50 ) { pwm = 255; } else
      if( tempDiff >= 20 ) { pwm = 200; } else
      if( tempDiff >= 10 ) { pwm = 150; } else
      if( tempDiff >= 5 )  { pwm = 60;  } else
      if( tempDiff >= 3 )  { pwm = 20;  } else
      if( tempDiff >= 1 )  { pwm = 5;   } else
      { pwm = 0; }
    }
  // measuredCelsius == 0 если нет ответа от max6675
  } else { pwm = 0; }
  
  if( heaterPWM != pwm ) {
    heaterPWM = pwm;
    
    analogWrite(heaterPin, pwm);

    return true;
  }

  return false;
}


