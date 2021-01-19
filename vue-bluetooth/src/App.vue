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
  // beforeDestroy() {
  //   this.$store.dispatch("bluetooth/garbageCollect");
  // },
  methods: {
    async start() {
      try {
        const device = await navigator.bluetooth.requestDevice({
          filters: [
            {
              name: "BT05",
            },
          ],
          optionalServices: [0xffe0],
        });
        // const server = await device.gatt.connect();
        // const service = await server.getPrimaryService(0xffe0);
        // const characteristic = await service.getCharacteristic(0xffe1);
        this.myCharacteristic = await bluetooth.initialize(
          {},
          this.onChange,
          device
        );
      } catch (error) {
        console.error(error);
      }
    },
    onChange(event) {
      const value = event.target.value;
      let decoder = new TextDecoder("utf-8");
      let message = decoder.decode(value);
      console.log("handleCharacteristicValueChanged - message", message);
      if (message.includes("A")) {
        this.count++;
        console.log("count", this.count);
        if (this.count > 3) {
          this.send("Hello from Web");
          this.count = 0;
        }
      }
    },
    send(message) {
      let enc = new TextEncoder(); // By default this encodes to utf-8
      this.myCharacteristic.writeValue(enc.encode(`<${message}>`));
    },
  },
};
</script>
