export default {
  count: 0,
  async initialize(configuration, handler) {
    debugger;
    const device = await navigator.bluetooth.requestDevice({
      filters: [
        {
          name: configuration.name || "BTO5", // BTO5 is a common default name on these BLE modules.
        },
      ],
      optionalServices: [configuration.serviceId || 0xffe0],
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
    console.log("Notifications have been started.");
    debugger;
    return characteristic;
  },
};
