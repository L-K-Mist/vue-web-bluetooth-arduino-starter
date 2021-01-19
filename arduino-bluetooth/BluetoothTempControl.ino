#include <SoftwareSerial.h>

#include "thermistor.h"
// Analog pin used to read the NTC
#define NTC_PIN A0

#include "TempSensor.h"
#include "Heater.h"

TempSensor tempSensor(NTC_PIN);
Heater heater(&tempSensor);

// Global temperature reading
float temp;

SoftwareSerial BluetoothDevice(3,4);

const byte numChars = 32;
char receivedChars[numChars];

boolean newData = false;

void setup() {
  heater.setup();

  Serial.begin(115200);
  BluetoothDevice.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  delay(100);
  establishContact();  // send a byte to establish contact until receiver responds
}

void loop() {
  recvWithStartEndMarkers();
  useNewData();
  delay(100);
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (BluetoothDevice.available() > 0 && newData == false) {
        rc = BluetoothDevice.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }
        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void useNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
          char * part1;
          char * part2;
          char * part3;
          part1 = strtok(receivedChars," ");
          part2 = strtok (NULL," ");
          part3 = strtok (NULL," ");
          Serial.print("first part: ");
          Serial.println(part1);
          Serial.print("second part: ");
          Serial.println(part2);
          Serial.print("third part: ");
          Serial.println(part3);
          // Serial.print("second bit: ");
          // Serial.println(part1[1]);
          // float aFloat = atof(strtok (NULL," "));  
          // Serial.println(aFloat, 3);
        if(strcmp(part1, "setT") == 0){
          
          Serial.print("I see targetTemp: ");
          Serial.println(atof(part2));
        }
        if(strcmp(part1, "getT") == 0){
          Serial.println("I must fetch tempC...");
          BluetoothDevice.print("TempC: ");
          BluetoothDevice.println(heater.getTempC());
        }

        newData = false;
    }
}


// TODO Research async-await like functionality for c++ arduino.
void establishContact() {
  while (BluetoothDevice.available() <= 0) {
    BluetoothDevice.println("A");   // send an initial string
    delay(600);
  }
}



