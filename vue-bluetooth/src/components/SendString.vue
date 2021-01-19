<template>
  <v-container>
    <v-text-field
      name="name"
      label="label"
      id="id"
      v-model="command"
    ></v-text-field>
    <v-btn @click="send(command)" color="success">Send Command</v-btn>
  </v-container>
</template>

<script>
import bluetooth from "@/helpers/bluetooth";
export default {
  name: "SendString",

  data: () => ({
    command: "",
  }),
  methods: {
    send(message) {
      bluetooth.send(message);
    },
  },
};
</script>
