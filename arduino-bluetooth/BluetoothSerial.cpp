#include "BluetoothSerial.h"
#include <SoftwareSerial.h>
#include <Arduino.h>

Bluetooth::Bluetooth(SoftwareSerial* hardwareModule, UseNewDataFunction callback)
:_device(hardwareModule), handleMessage(callback)
{
    newData = false;
    
}

void Bluetooth::initialize(){
    _device->begin(115200);
    Serial.println("initialized");
}

void Bluetooth::receive(){
    static boolean receiveInProgress = false;
    static byte index = 0;
    char startMarker = '<';
    char endMarker = '>';
    char incomingCharacter;

    while (_device->available() > 0 && newData == false) {
         Serial.print("reading");
        incomingCharacter = _device->read();
        Serial.print(incomingCharacter);
        if (incomingCharacter == startMarker) {
            receiveInProgress = true;
            Serial.print("receive in progress ");
            break;
        }
        if (receiveInProgress == true) {
            if (incomingCharacter != endMarker) {
                _receivedChars[index] = incomingCharacter;
                index++;
                if (index >= _numChars) {
                    index = _numChars - 1;
                }
            }
            else {
                _receivedChars[index] = '\0'; // terminate the string
                receiveInProgress = false;
                index = 0;
                newData = true;
            }
        }
        Serial.print("received chars");
        Serial.println(_receivedChars);
    }
}

void Bluetooth::useNewData(){
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(_receivedChars);

        const char * delimiter = ",";
        char * parts[3]={strtok(_receivedChars,delimiter), strtok (NULL,delimiter), strtok (NULL,delimiter)};

        if(strcmp(parts[0], "Hi from web") == 0){
          Serial.println("Yay web says hi!");
          _device->println("Hi from arduino");
        }
        if(strcmp(parts[0], "setTemp") == 0){ // In this strange world strcmp is 0 if the comparison is true.
          Serial.print("I see targetTemp: ");
          Serial.println(atof(parts[1]));
          _device->print("Aiming for ");
          _device->print(atof(parts[1]));
          _device->println("C");
          delay(3000);
          _device->println("And that's great news to me.");
        }
        if(strcmp(parts[0], "echo") == 0){
          Serial.println("I must echo...");
          _device->print("I echo back    ");
          _device->println(parts[1]);
        }
        if(strcmp(parts[0], "getTemp") == 0){
          Serial.println("I must fetch tempC...");
          _device->print("TempC: ");
          // Heater.getTemp();
        }
        newData = false;
    }
}


