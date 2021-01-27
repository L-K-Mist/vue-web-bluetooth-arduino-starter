#include <SoftwareSerial.h>
#include "BluetoothSerial.h"

SoftwareSerial BluetoothDevice(3,4);

// onMessageReceived is a callback function.
// This is where you decide the message logic.
// Each message has a maximum of three comma-separated parts.
// Note that I haven't used part 3 at all, since - for now - I only need parts one and two.
void onMessageReceived(char * messageParts[3], SoftwareSerial* device){
    if(strcmp(messageParts[0], "Hi from web") == 0){ // In this strange world strcmp is 0 if the comparison is true.
        Serial.println("Yay web says hi!");
        device->println("Hi from arduino");
    }
    if(strcmp(messageParts[0], "echo") == 0){
        device->print("I echo back    ");
        device->println(messageParts[1]);
    }
    if(strcmp(messageParts[0], "setTemp") == 0){ 
        device->print("Aiming for ");
        device->print(atof(messageParts[1]));
        device->println("C");
    }
    if(strcmp(messageParts[0], "getTemp") == 0){
        Serial.println("I must fetch tempC...");
        device->print("TempC: ");
        // Heater.getTemp();
    }
}
// &BluetoothDevice is dependency injection and composition. myBluetooth has a BluetoothDevice; and has a callback.
Bluetooth myBluetooth(&BluetoothDevice, onMessageReceived);

void setup() {
  Serial.begin(115200); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  myBluetooth.setup();
  delay(500);
}

void loop() {
  myBluetooth.loop();
  delay(1000);
}


