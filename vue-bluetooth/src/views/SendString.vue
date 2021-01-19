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
export default {
  name: "SendString",

  data: () => ({
    command: "",
  }),
  methods: {
    send(message) {
      this.$store.dispatch("bluetooth/send", message);
      debugger;
    },
  },
};
</script>
