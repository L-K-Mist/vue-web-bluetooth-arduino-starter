#ifndef _TEMPSENSOR_H
#define _TEMPSENSOR_H

#include "thermistor.h"
#include "Arduino.h"

class TempSensor {
  private:
  uint8_t _analogPin;
  public:
  TempSensor(uint8_t analogPin);
  THERMISTOR* pointer_to_thermistor;
  float getTempC(void);
  void setup(void);
};


#endif