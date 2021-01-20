<template>
  <v-card>
    <v-card-title>
      Send Messages to your Arduino
    </v-card-title>
    <v-card-text>
      <v-form>
        <v-row align="center" justify="center" wrap>
          <v-col sm="12" md="5">
            <v-row>
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
            </v-row>
          </v-col>
          <v-col sm="12" md="5" justify="end">
            <v-btn @click="send(command)" color="success" align-self="end"
              ><v-icon class="mr-3">mdi-send</v-icon> Send</v-btn
            >
          </v-col>
        </v-row>
      </v-form>
      <v-row>
        <v-col xs="12">Arduino says: {{ arduinoSays }}</v-col>
      </v-row>
    </v-card-text>
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
  },
  methods: {
    send(message) {
      bluetooth.send(this.echo ? `echo,${message}` : message);
    },
  },
};
</script>
