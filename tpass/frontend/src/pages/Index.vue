<template>
  <q-page class="flex flex-center">
    <img alt="Quasar logo" src="~assets/quasar-logo-full.svg">
    <q-btn
      round
      color="primary"
      @click="goToQRCodeScanner"
      class="fixed"
      icon="camera"
      size="md"
      style="right: 18px; bottom: 18px"
    />
  </q-page>
</template>

<script>
export default {
  name: 'PageIndex',
  methods: {
    goToQRCodeScanner () {
      this.$router.push('/scanner')
    }
  }
}
</script>

<style lang="stylus" scoped>
</style>
