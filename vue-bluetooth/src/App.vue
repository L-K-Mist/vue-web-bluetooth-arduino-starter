<template>
  <v-app>
    <v-app-bar app color="primary" dark>
      Web Bluetooth Temp Controller
      <v-spacer></v-spacer>
      <v-btn @click="start">See Devices</v-btn>
    </v-app-bar>

    <v-main>
      <router-view></router-view>
    </v-main>
  </v-app>
</template>

<script>
export default {
  name: "SendString",

  data: () => ({
    message: null,
    myCharacteristic: null,
    count: 0,
    command: "",
  }),
  beforeDestroy() {
    this.$store.dispatch("bluetooth/garbageCollect");
  },
  methods: {
    start() {
      this.$store.dispatch("bluetooth/initializeBluetooth");
    },
  },
};
</script>
