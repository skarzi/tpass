<template>
  <q-page class="flex items-start q-mx-lg" padding>
    <div class="container row">
      <div class="col-xs-12 text-center">
        <img
          alt="tpass"
          src="~assets/tpass.png"
          class="logo"
        >
      </div>
      <div class="col-xs-12 q-my-lg text-center">
        <div class="slogan q-mt-md">
          Scan QR code to authenticate
        </div>
        <q-btn
          rounded
          @click="goToQRCodeScanner"
          class="scan-button q-mt-xl"
          size="lg"
          label="Scan"
        />
      </div>
      <div class="col-xs-12 activity">
        <q-list no-border>
          <q-list-header class="list-header text-center">
            Latest activity:
          </q-list-header>
          <q-item
            v-for="transaction in transactions"
            :key="transaction.id"
          >
            <q-item-side>
              <q-icon
                :name="transaction.status == 3 ? 'warning' : 'check_circle'"
                :color="transaction.status == 3 ? 'negative' : 'positive'"
                size="20px"
              />
              {{ transaction.init_date | agoify }}
            </q-item-side>
            <q-item-main />
            <q-item-side
              color="primary"
              right
            >
              {{ transaction.url | urlize }}
            </q-item-side>
          </q-item>
        </q-list>
      </div>
    </div>
  </q-page>
</template>

<script>
import timeago from 'timeago.js'

export default {
  name: 'PageIndex',
  data () {
    return {
      transactions: []
    }
  },
  methods: {
    goToQRCodeScanner () {
      this.$router.push('/scanner')
    }
  },
  filters: {
    urlize (value) {
      let url = value
      const maxLength = 20
      try {
        const urlObject = new URL(value)
        url = urlObject.hostname
      } catch (error) {
        console.log(value, error)
      }
      if (url.length > maxLength) {
        return url.slice(0, maxLength) + '...'
      }
      return url
    },
    agoify (value) {
      let date = new Date(value)
      return timeago().format(date)
    }
  },
  mounted () {
    this.$axios.get(
      'http://localhost:8000/transactions/',
      {
        params: {
          page_size: 5
        }
      }
    ).then(response => {
      console.log(response)
      this.transactions = response.data.results
    }).catch(error => {
      console.log(error)
    })
  }
}
</script>

<style lang="stylus" scoped>
@import '~variables'

.q-item
  border solid $primary 1px

.container
  margin-top 25%

.logo
  height 80px

.slogan
  font-size 1.2em

.scan-button
  width 75%
  background-image linear-gradient(90deg, $primary, #0af)
  box-shadow 5px 5px 24px 0 rgba(0, 160, 255, .56)
  color white

.list-header
  font-size 1.2em
  color $tertiary
</style>
