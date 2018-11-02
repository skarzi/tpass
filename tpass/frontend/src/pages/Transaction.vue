<template>
  <q-page class="flex fullscreen" padding>
    <div
      class="row text-center q-px-lg"
      @click="sendSuccessMessage"
    >
      <div class="col-xs-12 transaction q-mt-lg">
        Attempting to log in to
        <span class="transaction-id">
          "{{ transactionData.url }}"
        </span>
      </div>
      <div class="col-xs-12 spinner text-center align-center">
        <Lottie
          :options="checkLottieOptions"
          v-on:animCreated="handleCheckAnimation"
        />
        <Lottie
          :options="spinnerLottieOptions"
          v-on:animCreated="handleSpinnerAnimation"
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
import * as spinnerAnimationData from '../assets/ripple.json'
import * as checkAnimationData from '../assets/check_animation.json'
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
      spinnerLottieOptions: {
        animationData: spinnerAnimationData.default
      },
      checkLottieOptions: {
        animationData: checkAnimationData.default,
        loop: false
      }
    }
  },
  computed: {
    ...transactionsNamespace.mapState(['transactionData']),
    message () {
      if (this.transactionData.status === 1) {
        return 'Approve or reject log in attempt on device.'
      } else if (this.transactionData.status === 2) {
        this.showCheckAnimation()
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
    ]),
    handleSpinnerAnimation (anim) {
      this.spinnerAnim = anim
    },
    handleCheckAnimation (anim) {
      this.checkAnim = anim
      this.checkAnim.stop()
      this.checkAnim.wrapper.style.display = 'none'
    },
    showCheckAnimation () {
      this.spinnerAnim.destroy()
      this.spinnerAnim.wrapper.style.display = 'none'
      this.checkAnim.wrapper.style.display = 'block'
      this.checkAnim.play()
    },
    sendSuccessMessage () {
      this.ws.send(JSON.stringify({
        status: 'approved'
      }))
    }
  },
  mounted () {
    // set few seconds timeout after which set transaction status to rejected
    // and redirect user to scannner
    this.$q.loading.hide()
    this.ws = new WebSocket(
      `wss://4fa2dd19.ngrok.io/ws/transactions/${this.transactionData.id}`
    )
    this.ws.onmessage = (event) => {
      console.log('ws message')
      let transaction = JSON.parse(event.data)
      this.setTransactionData(transaction.data)
      if (transaction.status !== 1) {
        setTimeout(() => {
          console.log('redirecting to /')
          this.$router.push('/')
        }, 5500)
      }
    }
    this.ws.onopen = (event) => {
      setTimeout(() => {
        if (this.transactionData.status === 1) {
          this.ws.send(JSON.stringify({
            status: 'rejected'
          }))
        }
      }, 11000)
    }
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
