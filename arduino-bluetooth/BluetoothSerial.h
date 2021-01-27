#include <SoftwareSerial.h>
#include <Arduino.h>
#ifndef BLUETOOTHSERIAL_H
#define BLUETOOTHSERIAL_H

typedef void(*UseNewDataFunction)(char * parts[3], SoftwareSerial* device);
class Bluetooth {
    private:
    static const uint8_t _numChars = 32;
    char _receivedChars[_numChars];
    SoftwareSerial* _device; // TODO change to public naming.
    boolean newData;
    void receive(void);
    void useNewData(void);
    UseNewDataFunction handleMessage;
    public:
    Bluetooth(SoftwareSerial* hardwareModule, UseNewDataFunction callback);
    // Bluetooth(SoftwareSerial* hardwareModule);
    void setup(void);
    void loop(void);
};

#endif