#include "TempSensor.h"

TempSensor::TempSensor(uint8_t analogPin){
  _analogPin = analogPin;
}

float TempSensor::getTempC(void){
  float val = pointer_to_thermistor->read();
  // Serial.print("Val in getTempC : ");
  // Serial.println(val);
  return val / 10;
};

void TempSensor::setup(void){
  THERMISTOR _thermistor(_analogPin,        // Analog pin
                            9500,          // Nominal resistance at 25 ºC
                            3950,           // thermistor's beta coefficient
                            10000);         // Value of the series resistor
  delay(20); // without this slight delay I was getting weird results.
  pointer_to_thermistor = &_thermistor;
};
