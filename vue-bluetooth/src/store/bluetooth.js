const state = {
  arduinoCharacteristic: null,
  count: 0,
};

const getters = {};

const actions = {
  async initializeBluetooth({ state, dispatch }, payload) {
    try {
      const device = await navigator.bluetooth.requestDevice({
        filters: [
          {
            name: "BT05",
          },
        ],
        optionalServices: [0xffe0],
      });
      const server = await device.gatt.connect();
      const service = await server.getPrimaryService(0xffe0);
      const characteristic = await service.getCharacteristic(0xffe1);
      await characteristic.startNotifications();
      await characteristic.addEventListener(
        "characteristicvaluechanged",
        handleCharacteristicValueChanged
      );
      console.log("Notifications have been started.");
      state.arduinoCharacteristic = characteristic;
    } catch (error) {
      console.error(error);
    }
    function handleCharacteristicValueChanged(event) {
      const value = event.target.value;
      let decoder = new TextDecoder("utf-8");
      // console.log("Received " + value.getUint8(0));

      let message = decoder.decode(value);
      console.log("handleCharacteristicValueChanged - message", message);
      if (message.includes("A")) {
        state.count++;
        console.log("count", state.count);
        if (state.count > 3) {
          dispatch("send", "BeautifulStore");
          state.count = 0;
        }
      }
    }
  },
  garbageCollect({ state }) {
    state.bluetooth.arduinoCharacteristic.removeEventListener(
      "characteristicvaluechanged",
      handleCharacteristicValueChanged
    );
  },
  async send({ state }, payload) {
    state.arduinoCharacteristic.writeValue(str2ab(payload));
    debugger;
    function str2ab(str) {
      let enc = new TextEncoder();
      return enc.encode(`<${str}>`);
    }
  },
};

let count = 0;

export default {
  namespaced: true,
  state,
  getters,
  actions,
};
