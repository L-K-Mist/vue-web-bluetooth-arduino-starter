export default {
  count: 0,
  characteristic: null,
  async initialize(configuration, handler, device) {
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
    console.log("Notifications have been started.");
    this.characteristic = characteristic;
    return this.characteristic;
  },
  send(message) {
    debugger;
    let enc = new TextEncoder(); // By default this encodes to utf-8
    this.characteristic.writeValue(enc.encode(`<${message}>`));
    debugger;
  },
};
