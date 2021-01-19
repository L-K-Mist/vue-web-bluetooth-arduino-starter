<template>
  <v-container>
    <v-text-field
      name="name"
      label="label"
      id="id"
      v-model="command"
    ></v-text-field>
    <v-checkbox v-model="echo" label="Must arduino echo back?"></v-checkbox>
    <v-btn @click="send(command)" color="success">Send Command</v-btn>
  </v-container>
</template>

<script>
import bluetooth from "@/helpers/bluetooth";
export default {
  name: "SendString",

  data: () => ({
    command: "",
    echo: false,
  }),
  methods: {
    send(message) {
      bluetooth.send(this.echo ? `echo,${message}` : message);
    },
  },
};
</script>
