<template>
  <v-app>
    <v-app-bar app color="primary" dark>
      Web Bluetooth Temp Controller
      <v-spacer></v-spacer>
      <v-badge :value="isConnected" color="success" icon="mdi-check" overlap>
        <v-btn
          class="blue--text text--darken-4"
          :disabled="isConnected"
          color="accent"
          @click="start"
          ><v-icon class="mr-3">mdi-bluetooth</v-icon>
          {{ isConnected ? "Connected" : "See Devices" }}</v-btn
        >
      </v-badge>
    </v-app-bar>
    <v-main>
      <v-container>
        <router-view></router-view>
      </v-container>
    </v-main>
  </v-app>
</template>

<script>
import bluetooth from "@/helpers/bluetooth";
export default {
  data: () => ({
    message: null,
    myCharacteristic: null,
    count: 0,
    command: "",
  }),
  mounted() {
    // this.start(); // This just demonstrates that start only works if triggered by a user action.
  },
  computed: {
    isConnected() {
      return this.$store.state.bluetooth.isConnected;
    },
  },
  methods: {
    async start() {
      try {
        this.myCharacteristic = await bluetooth.initialize(
          {},
          this.onChange,
          this.onDisconnected
        );
        this.$store.dispatch("bluetooth/isConnected", true);
      } catch (error) {
        console.error(error.message);
      }
    },
    onChange(event) {
      const value = event.target.value;
      this.$store.dispatch("bluetooth/decodeMessage", value);
    },
    onDisconnected() {
      // TODO someday: Add automatic reconnect like: https://googlechrome.github.io/samples/web-bluetooth/automatic-reconnect-async-await.html
      this.$store.dispatch("bluetooth/isConnected", false);
    },
  },
};
</script>
<style scoped>
.button {
  color: navy;
}
</style>
