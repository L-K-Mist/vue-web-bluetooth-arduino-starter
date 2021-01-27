#include <SoftwareSerial.h>
#include <Arduino.h>
#ifndef BLUETOOTHSERIAL_H
#define BLUETOOTHSERIAL_H

typedef void(*UseNewDataFunction)(char * parts[3], SoftwareSerial* device);
class Bluetooth {
    private:
    static const uint8_t _numChars = 32;
    char _receivedChars[_numChars];
    public:
    SoftwareSerial* _device; // TODO change to public naming.
    boolean newData;
    Bluetooth(SoftwareSerial* hardwareModule, UseNewDataFunction callback);
    // Bluetooth(SoftwareSerial* hardwareModule);
    UseNewDataFunction handleMessage;
    void initialize(void);
    void receive(void);
    void useNewData(void);
};

#endif