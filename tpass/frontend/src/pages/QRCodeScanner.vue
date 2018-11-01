<template>
  <q-page>
    <QRCodeScanner
      v-on:transaction-init="onTransactionInit"
      @invalid-data="onInvalidData"
    />
  </q-page>
</template>

<script>
import QRCodeScanner from '../components/QRCodeScanner.vue'

export default {
  name: 'PageQRCodeScanner',
  components: {
    QRCodeScanner
  },
  methods: {
    onTransactionInit (transactionID) {
      // show some message with loader here
      // then send message to device using BLE.
      // users should perform action on they device
      // and after their action app get results by BLE
      // and show them(approved or rejected)
      console.log(`init transaction with id: "${transactionID}"`)
      this.$router.push(`/transactions/${transactionID}/`)
    },
    onInvalidData (data) {
      console.log(`QR code data is invalid: "${data}"`)
      this.$q.notify({
        message: 'Please scan tpass QR code..',
        type: 'warning',
        position: 'top'
      })
    }
  }
}
</script>

<style lang="stylus" scoped>
</style>
