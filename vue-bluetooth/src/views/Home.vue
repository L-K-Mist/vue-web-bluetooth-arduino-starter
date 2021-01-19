<template>
  <send-string></send-string>
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
