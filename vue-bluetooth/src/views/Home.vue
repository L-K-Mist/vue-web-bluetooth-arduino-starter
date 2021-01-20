<template>
  <v-card>
    <send-string></send-string>
  </v-card>
</template>

<script>
import SendString from "@/components/SendString";
export default {
  components: {
    SendString,
  },
  data: () => ({
    message: null,
    myCharacteristic: null,
    count: 0,
    command: "",
  }),
};
</script>

<style scoped></style>
