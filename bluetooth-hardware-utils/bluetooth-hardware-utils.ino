#include <SoftwareSerial.h>

/* 
This is a usefull place to start, while getting to know your bluetooth hardware-module.
Note: ble_cmd only works while there is no currently active bluetooth connection.
See comment at the end of this file for the commands for the module I was using.
If you get increasing errors at longer distances (5 meters), it might help to set the 
baud rate lower with AT+BAUD.
*/

SoftwareSerial ble_device(3,4);

String str_ii = "";
int ii_0 = 0;

void setup() {  
  Serial.begin(115200);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  ble_device.begin(115200);
  delay(100);
  // ble_help(); // uncomment to print commands available for your ble hardware-module.
  delay(100);
}

void loop() {
  Serial.println("Hello Dee!");
  ble_device.println("hi");
  // Enter AT+ commands of interest here (BLE Address, UUIDs, Power settings)
   ble_cmd("AT+CHAR","Char UUID: "); // printout character UUID
   ble_cmd("AT+UUID", "Service UUID: ");
   ble_cmd("AT+VERSION","Version: "); // module version  
   ble_cmd("AT+PIN","pin: "); 
  //  ble_cmd("AT+CHAR","Char UUID: "); // printout character UUID
  //  ble_cmd("AT+VERSION","Version: "); // module version  
  //  ble_cmd("AT+RST",""); // reset BLE module
  delay(2000);
}

String ble_cmd(String cmd_str,String desc_str){
  str_ii = "";
  unsigned long t1 = millis();
  ble_device.println(cmd_str);
  while (true){
    char in_char = ble_device.read();
    if (int(in_char)==-1 or int(in_char)==42){
      if ((millis()-t1)>2000){ // 2 second timeout
        return "Err";
      }
      continue;
    }
    if (in_char=='\n'){
      Serial.print("Bluetooth "+desc_str);
      Serial.println(str_ii.substring(0,str_ii.length()));
      return str_ii;
    }
    str_ii+=in_char;
  }
}

void ble_help(){
  ble_device.println("AT+HELP"); // list all AT+ commands
  while (true){ // loop to print all AT+ commands
    char in_char = ble_device.read();
    if (int(in_char)==-1 or int(in_char)==42){continue;}
    str_ii+=in_char;
    if (in_char=='\n'){
      if (str_ii==String('\r')+String('\n')){
        if (ii_0 == 0){
          ii_0 = 1;
          continue;
        }
        break; // break after more than 1 empty carriage return and newline
      }
      Serial.print(str_ii);
      str_ii = "";
    }
  }
}

/*
 Command             Description			           
 ---------------------------------------------------------------- 
 AT                  Check if the command terminal work normally  
 AT+RESET            Software reboot				   
 AT+VERSION          Get firmware, bluetooth, HCI and LMP version 
 AT+HELP             List all the commands		           
 AT+NAME             Get/Set local device name                    
 AT+PIN              Get/Set pin code for pairing                 
 AT+BAUD             Get/Set baud rate		                   
 AT+LADDR            Get loaal bluetooth address		   
 AT+ADDR             Get local bluetooth address		   
 AT+DEFAULT          Restore factory default			   
 AT+RENEW            Restore factory default			   
 AT+STATE            Get current state				   
 AT+PWRM             Get/Set power on mode(low power) 		   
 AT+POWE             Get/Set RF transmit power 		   
 AT+SLEEP            Sleep mode 		                   
 AT+ROLE             Get/Set current role.	                   
 AT+PARI             Get/Set UART parity bit.                     
 AT+STOP             Get/Set UART stop bit.                       
 AT+INQ              Search slave model                           
 AT+SHOW             Show the searched slave model.               
 AT+CONN             Connect the index slave model.               
 AT+IMME             System wait for command when power on.	   
 AT+START            System start working.			   
 AT+UUID             Get/Set system SERVER_UUID .            	   
 AT+CHAR             Get/Set system CHAR_UUID .            	   
 -----------------------------------------------------------------

*/
