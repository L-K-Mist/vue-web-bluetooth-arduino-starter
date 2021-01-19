#include "TempSensor.h"
#include "Arduino.h"

class Heater {
  private:
  TempSensor *_sensorPointer;
  float tempC;
  public:
  Heater(TempSensor *sensor);
  float getTempC(void);
  void setup(void);
  void loop(void);
};