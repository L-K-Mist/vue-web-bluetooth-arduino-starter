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
        incomingCharacter = _device->read();
        Serial.print(incomingCharacter);
        if (incomingCharacter == startMarker) {
            receiveInProgress = true;
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
    }
}

void Bluetooth::useNewData(){
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(_receivedChars);

        const char * delimiter = ",";
        // Split the message into maximum 3 comma-delimetered elements of an array.
        char * parts[3]={strtok(_receivedChars,delimiter), strtok (NULL,delimiter), strtok (NULL,delimiter)};

        handleMessage(parts, _device);
        newData = false;
    }
}



