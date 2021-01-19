#include <SoftwareSerial.h>
// Analog pin used to read the NTC
#define NTC_PIN A0

// Global temperature reading
float temp;

SoftwareSerial BluetoothDevice(3,4);

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;

void setup() {
  Serial.begin(115200); 
  BluetoothDevice.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  delay(100);
  // For Handshaking
  establishContact();  // send a byte to establish contact until receiver responds
}

void loop() {
  receiveWithStartEndMarkers();
  useNewData();
  delay(100);
}

void establishContact() {
  while (BluetoothDevice.available() <= 0) {
    BluetoothDevice.println("A");   // send an initial string
    delay(600);
  }
}


void receiveWithStartEndMarkers() {
  static boolean receiveInProgress = false;
  static byte index = 0;
  char startMarker = '<';
  char endMarker = '>';
  char incomingCharacter;

  while (BluetoothDevice.available() > 0 && newData == false) {
    incomingCharacter = BluetoothDevice.read();

    if (receiveInProgress == true) {
        if (incomingCharacter != endMarker) {
            receivedChars[index] = incomingCharacter;
            index++;
            if (index >= numChars) {
                index = numChars - 1;
            }
        }
        else {
            receivedChars[index] = '\0'; // terminate the string
            receiveInProgress = false;
            index = 0;
            newData = true;
        }
    }
    else if (incomingCharacter == startMarker) {
        receiveInProgress = true;
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
          // This is how we split a string(actually character array) with a delimiter without c++ std lib.
          const char delimiter = " ";
          part1 = strtok(receivedChars,delimiter);
          part2 = strtok (NULL,delimiter);
          part3 = strtok (NULL,delimiter);
          Serial.print("first part: ");
          Serial.println(part1);
          Serial.print("second part: ");
          Serial.println(part2);
          Serial.print("third part: ");
          Serial.println(part3);
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





