# vue-web-bluetooth-arduino-starter

A nice starting point for a PWA that talks to an arduino.
Opens up a way to use a standby phone as a gui for multiple hobby, home and security devices.

Maybe software isn't eating the *whole* world, but it certainly is gobbling up physical dials and switches!!

Now you can give any arduino project a GUI.

Based heavily off of the vanilla [WebBluetooth-Terminal](https://github.com/hewittwill/WebBluetooth-Terminal), and [Web Bluetooth Samples](https://googlechrome.github.io/samples/web-bluetooth/)

This was the exact module used: [JDY-08 CC2541 BLUETOOTH 4.0 BLE SERIAL MODULE](https://www.diyelectronics.co.za/store/bluetooth/1441-jdy-08-cc2541-bluetooth-40-ble-serial-module.html)

Here's a [video intro and demo](https://www.youtube.com/watch?v=4jZKu5tQWnM).


## Potential Gotchas
Make sure your browser has web-bluetooth enabled.

Note that web-bluetooth only works with Bluetooth Low Energy (BLE) 4.0 devices.

The exact module I used has a default baud rate of 115200. I will probably drop that down to 9600 for my personal projects, because I think that will carry the messages better over longer distances. Some examples of such commands can be seen in bluetooth-hardware-utils.ino , but different modules might differ, so refer to the datasheet for specifics.

## To Do
- Better PWA aspects (particularly an update-available alert)
- Demonstration of a more fleshed out GUI using this as a starting point.
