<template>
  <v-container id="send-string">
    <v-row align="center" justify="center" wrap>
      <v-col sm="12" md="5">
        <v-row>
          <v-text-field
            name="name"
            label="Message to Arduino"
            id="id"
            v-model="command"
          ></v-text-field>
          <v-checkbox
            style="width: 80px;"
            v-model="echo"
            label="Echo?"
          ></v-checkbox>
        </v-row>
      </v-col>
      <v-col sm="12" md="5" justify="end">
        <v-btn @click="send(command)" color="success" align-self="end"
          ><v-icon class="mr-3">mdi-send</v-icon> Send</v-btn
        >
      </v-col>
    </v-row>
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

<style scoped></style>
