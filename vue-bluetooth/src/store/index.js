import Vue from "vue";
import Vuex from "vuex";
import bluetooth from "./bluetooth";

Vue.use(Vuex);

export default new Vuex.Store({
  modules: {
    bluetooth,
  },
});
