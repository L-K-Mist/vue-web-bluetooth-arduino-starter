export default {
  count: 0,
  characteristic: null,
  async initialize(configuration, handler) {
    const device = await navigator.bluetooth.requestDevice({
      filters: [
        {
          name: "BT05",
        },
      ],
      optionalServices: [0xffe0],
    });
    const server = await device.gatt.connect();
    const service = await server.getPrimaryService(
      configuration.serviceId || 0xffe0
    );
    const characteristic = await service.getCharacteristic(
      configuration.characteristicId || 0xffe1
    );
    await characteristic.startNotifications();
    await characteristic.addEventListener(
      "characteristicvaluechanged",
      handler
    );
    this.characteristic = characteristic;
    console.log("Notifications have been started: ", this.characteristic);
    this.send("Hi from web"); // Arduino is expecting this message as part of the initial handshake.
    return characteristic;
  },
  send(message) {
    let enc = new TextEncoder(); // By default this encodes to utf-8
    // Why the <opening and closing> characters?
    // Went with this guy's example 3 for the reasons he mentions: https://forum.arduino.cc/index.php?topic=396450.0
    this.characteristic.writeValue(enc.encode(`<${message}>`));
  },
};
