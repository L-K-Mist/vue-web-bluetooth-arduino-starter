<template>
  <v-app>
    <v-app-bar app color="accent">
      Web Bluetooth Temp Controller
      <v-spacer></v-spacer>
      <v-btn color="primary" @click="start"
        ><v-icon class="mr-3">mdi-bluetooth</v-icon> See Devices</v-btn
      >
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
  methods: {
    async start() {
      try {
        this.myCharacteristic = await bluetooth.initialize({}, this.onChange);
      } catch (error) {
        console.error(error.message);
      }
    },
    onChange(event) {
      const value = event.target.value;
      this.$store.dispatch("bluetooth/decodeMessage", value);
    },
  },
};
</script>
