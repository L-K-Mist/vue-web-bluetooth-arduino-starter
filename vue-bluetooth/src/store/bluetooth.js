import bluetooth from "../helpers/bluetooth";
let decoder = new TextDecoder("utf-8");
let encoder = new TextEncoder(); // By default this encodes to utf-8
const state = {
  message: "",
};

const getters = {};

const actions = {
  decodeMessage({ commit }, message) {
    message = decoder.decode(message);
    if (message.includes("Hi from arduino")) {
      console.log(`Handshake completed. Arduino says: ${message}`);
    }
    commit("setMessage", message);
  },
  sendMessage(_, message) {
    bluetooth.send(message);
  },
};

const mutations = {
  setMessage(state, message) {
    state.message = message;
  },
};

export default {
  namespaced: true,
  state,
  getters,
  actions,
  mutations,
};
