import bluetooth from "../helpers/bluetooth";

const state = {
  arduinoCharacteristic: null,
  count: 0,
};

const getters = {};

const actions = {
  async initializeBluetooth({ state, dispatch }, payload) {
    const onChange = (event) => {
      const value = event.target.value;
      let decoder = new TextDecoder("utf-8");
      let message = decoder.decode(value);
      console.log("handleCharacteristicValueChanged - message", message);
      if (message.includes("A")) {
        this.count++;
        console.log("count", this.count);
        if (this.count > 3) {
          dispatch("send", "BeautifulStore");
          this.count = 0;
        }
      }
    };
    try {
      state.arduinoCharacteristic = await bluetooth.initialize({}, onChange);
    } catch (error) {
      console.error(error);
    }
  },
  // garbageCollect({ state }) {
  //   state.bluetooth.arduinoCharacteristic.removeEventListener(
  //     "characteristicvaluechanged",
  //     handleCharacteristicValueChanged
  //   );
  // },
  async send({ state }, payload) {
    let enc = new TextEncoder(); // By default this encodes to utf-8
    state.arduinoCharacteristic.writeValue(enc.encode(`<${payload}>`));
  },
};

let count = 0;

export default {
  namespaced: true,
  state,
  getters,
  actions,
};
