<template>
  <v-app>
    <v-app-bar app color="primary" dark>
      Web Bluetooth Temp Controller
      <v-spacer></v-spacer>
      <v-btn color="secondary" @click="start"
        ><v-icon class="mr-3">mdi-bluetooth</v-icon> See Devices</v-btn
      >
    </v-app-bar>

    <v-main>
      <router-view></router-view>
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
  beforeDestroy() {
    this.myCharacteristic.removeEventListener(
      "characteristicvaluechanged",
      this.onChange
    );
  },
  methods: {
    async start() {
      try {
        this.myCharacteristic = await bluetooth.initialize({}, this.onChange);
      } catch (error) {
        console.error(error);
      }
    },
    onChange(event) {
      const value = event.target.value;
      let decoder = new TextDecoder("utf-8");
      let message = decoder.decode(value);
      console.log("onChange - message", message);
      if (message.includes("Hi from arduino")) {
        console.log(`Handshake completed. Arduino says: ${message}`);
      }
    },
    send(message) {
      let enc = new TextEncoder(); // By default this encodes to utf-8
      this.myCharacteristic.writeValue(enc.encode(`<${message}>`));
    },
  },
};
</script>
