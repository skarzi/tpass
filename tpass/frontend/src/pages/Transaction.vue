<template>
  <q-page class="flex fullscreen" padding>
    <div class="row text-center q-px-lg">
      <div class="col-xs-12 transaction q-mt-lg">
        Attempting to log in to
        <span class="transaction-id">
          "{{ transactionData.url }}"
        </span>
      </div>
      <div class="col-xs-12 spinner text-center align-center">
        <Lottie
          :options="lottieOptions"
        />
      </div>
      <div class="col-xs-12 message">
        {{ message }}
      </div>
    </div>
  </q-page>
</template>

<script>
import Lottie from 'vue-lottie'
import * as animationData from '../assets/ripple.json'
import { createNamespacedHelpers } from 'vuex'

const transactionsNamespace = createNamespacedHelpers('transactions')

export default {
  name: 'PageTransaction',
  components: {
    Lottie
  },
  data () {
    return {
      transactionID: this.$route.params.transactionID,
      lottieOptions: {
        animationData: animationData.default
      }
    }
  },
  computed: {
    ...transactionsNamespace.mapState(['transactionData']),
    message () {
      if (this.transactionData.status === 1) {
        return 'Approve or reject log in attempt on device.'
      } else if (this.transactionData.status === 2) {
        return 'Access granted'
      } else if (this.transactionData.status === 3) {
        return 'Access rejected'
      } else {
        return 'Error occured. Try again later.'
      }
    }
  },
  methods: {
    ...transactionsNamespace.mapActions([
      'setTransactionData'
    ])
  },
  mounted () {
    // set few seconds timeout after which set transaction status to rejected
    // and redirect user to scannner
    const ws = new WebSocket(
      `ws://localhost:8000/ws/transactions/${this.transactionData.id}`
    )
    ws.onmessage = (event) => {
      console.log('ws message')
      let transaction = JSON.parse(event.data)
      this.setTransactionData(transaction.data)
      setTimeout(() => {
        console.log('redirecting to /')
        this.$router.push('/')
      }, 4000)
    }
    setTimeout(() => {
      if (this.transactionData.status === 1) {
        ws.send(JSON.stringify({
          status: 'rejected'
        }))
      }
    }, 10000)
  }
}
</script>

<style lang="stylus" scoped>
.transaction
  font-size 1.2em

.transaction-id
  font-weight bold
  font-size 1.2em

.spinner
  height 250px

.message
  font-size 1.5em
</style>
