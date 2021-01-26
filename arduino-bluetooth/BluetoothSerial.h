#include <SoftwareSerial.h>
#include <Arduino.h>
#ifndef BLUETOOTHSERIAL_H
#define BLUETOOTHSERIAL_H

typedef void(*UseNewDataFunction)();
class Bluetooth {
    private:
    SoftwareSerial* _device;
    const uint8_t _numChars = 32;
    char _receivedChars[32];
    public:
    boolean newData;
    Bluetooth(SoftwareSerial* hardwareModule, UseNewDataFunction callback);
    // Bluetooth(SoftwareSerial* hardwareModule);
    UseNewDataFunction handleMessage;
    void initialize(void);
    void receive(void);
    void useNewData(void);
};

#endif