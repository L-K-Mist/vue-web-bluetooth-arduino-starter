import bluetooth from "../helpers/bluetooth";
let decoder = new TextDecoder("utf-8");

const state = {
  message: "",
  isConnected: false,
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
  isConnected({ commit }, isConnected) {
    commit("isConnected", isConnected);
  },
};

const mutations = {
  setMessage(state, message) {
    state.message = message;
  },
  isConnected(state, isConnected) {
    state.isConnected = isConnected;
  },
};

export default {
  namespaced: true,
  state,
  getters,
  actions,
  mutations,
};
