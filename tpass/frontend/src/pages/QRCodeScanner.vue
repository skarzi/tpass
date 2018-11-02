<template>
  <q-page>
    <QRCodeScanner
      v-on:transaction-init="onTransactionInit"
      @invalid-data="onInvalidData"
      class="fullscreen"
    />
    <q-btn
      round
      color="primary"
      @click="goToSampleTransaction"
      class="fab fixed"
      icon="camera"
      size="lg"
    />
  </q-page>
</template>

<script>
import { createNamespacedHelpers } from 'vuex'
import QRCodeScanner from '../components/QRCodeScanner.vue'

const transactionsNamespace = createNamespacedHelpers('transactions')

export default {
  name: 'PageQRCodeScanner',
  components: {
    QRCodeScanner
  },
  methods: {
    ...transactionsNamespace.mapActions([
      'setTransactionData'
    ]),
    async onTransactionInit (transactionData) {
      // show some message with loader here
      // then send message to device using BLE.
      // users should perform action on they device
      // and after their action app get results by BLE
      // and show them(approved or rejected)
      let transactionID = transactionData.id
      this.$q.loading.show({
        message: 'Connecting with device..'
      })
      console.log(`init transaction with data: "${transactionData}"`)
      const ws = new WebSocket(
        `ws://localhost:8000/ws/transactions/${transactionID}`
      )
      console.log(ws)
      ws.onopen = (event) => {
        console.log('sending data to ws:', transactionData, event)
        let data = {
          url: transactionData.url,
          status: 'init'
        }
        ws.send(JSON.stringify(data))
        this.$q.loading.hide()
      }
      ws.onmessage = (event) => {
        let transaction = JSON.parse(event.data)
        this.setTransactionData(transaction.data)
        this.$router.push(`/transactions/${transactionID}/`)
      }
    },
    onInvalidData (data) {
      console.log(`QR code data is invalid: "${data}"`)
      this.$q.notify({
        message: 'Please scan tpass QR code..',
        type: 'warning',
        position: 'top'
      })
    },
    goToSampleTransaction () {
      let transactionID = 'af5e196bab5f47ecb9b7f4ff2e2efb29'
      this.$router.push(`/transactions/${transactionID}/`)
    }
  }
}
</script>

<style lang="stylus" scoped>
.q-layout-page
  background-color black
.fab
  bottom 18px
  left 50%
  transform translateX(-50%)
  z-index 7447
</style>
