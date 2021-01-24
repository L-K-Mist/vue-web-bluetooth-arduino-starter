<template>
  <v-card>
    <template v-if="isConnected || true">
      <v-card-title>
        Send Messages to your Arduino
      </v-card-title>
      <v-card-text>
        <p>
          The module seems to get
          <code>DOMException: GATT operation failed for unknown reason</code>
          on strings longer than 12 characters, even when I changed the numChars
          on the arduino side. Keep in mind though: you're more likely to be
          sending commands like <code>getTemp</code> and
          <code>setTemp,55</code> than full sentences.
        </p>
        <v-form>
          <v-row
            class="message-module"
            width="400"
            align="center"
            justify="center"
            wrap
          >
            <div class="check-input">
              <v-text-field
                name="name"
                label="Message to Arduino"
                id="id"
                v-model="command"
                @keydown.enter="send(command)"
                :counter="12"
                v-mask="'XXXXXXXXXXXX'"
              ></v-text-field>
              <v-checkbox
                style="width: 80px;"
                v-model="echo"
                label="Echo?"
              ></v-checkbox>
            </div>
            <v-btn
              class="ml-2 send-button"
              @click="send(command)"
              color="success"
              align-self="end"
              ><v-icon class="mr-3">mdi-send</v-icon> Send</v-btn
            >
          </v-row>
        </v-form>
        <v-row>
          <v-col xs="12"
            >Arduino says: <strong>{{ arduinoSays }}</strong></v-col
          >
        </v-row>
      </v-card-text>
    </template>
  </v-card>
</template>

<script>
import bluetooth from "@/helpers/bluetooth";
export default {
  name: "send-string",
  data: () => ({
    command: "",
    echo: true,
  }),
  computed: {
    arduinoSays() {
      return this.$store.state.bluetooth.message;
    },
    isConnected() {
      return this.$store.state.bluetooth.isConnected;
    },
  },
  methods: {
    send(message) {
      bluetooth.send(this.echo ? `echo,${message}` : message);
    },
  },
};
</script>

<style>
.send-button {
  max-width: 100px;
}
.message-module {
  max-width: 450px;
  /* border: 2px dotted blue; */
}
.check-input {
  display: inline-flex;
  /* border: 2px dotted purple; */
}
.check-input .v-text-field {
  max-width: 200px;
  /* border: 2px dotted blue; */
  margin-right: 10px;
}
</style>
