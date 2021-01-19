#include "Heater.h"
#include "TempSensor.h"


Heater::Heater(TempSensor* sensorPointer):_sensorPointer(sensorPointer)
{
}

void Heater::setup(){
    _sensorPointer->setup();
}

// void Heater::loop(){
//     tempC = 
//     Serial.print("Temp in 1/10 ºC FROM HEATER : ");
//     Serial.println(tempC);
// }

float Heater::getTempC(){
    return _sensorPointer->getTempC();
}