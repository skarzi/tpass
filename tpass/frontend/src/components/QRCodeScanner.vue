<template>
  <qrcode-stream
    class="camera"
    @decode="onDecode"
    :paused="paused"
    :camera="cameraOptions"
  >
  </qrcode-stream>
</template>

<script>
export default {
  name: 'QRCodeScanner',
  data () {
    return {
      dataRegexp: /[0-9a-fA-F]{8}-?[0-9a-fA-F]{4}-?[0-9a-fA-F]{4}-?[0-9a-fA-F]{4}-?[0-9a-fA-F]{12}/,
      paused: false,
      cameraOptions: {
        audio: false,
        video: {
          facingMode: { ideal: 'environment' }
        }
      }
    }
  },
  methods: {
    onDecode (decodedString) {
      this.paused = true
      console.log(`onDecode(): QR code data - "${decodedString}"`)
      if (this.isQRDataValid(decodedString)) {
        this.$emit('transaction-init', decodedString)
      } else {
        this.$emit('invalid-data', decodedString)
      }
      this.paused = false
    },
    isQRDataValid (data) {
      return data.match(this.dataRegexp) !== null
    }
  }
}
</script>

<style lang="stylus" scoped>
.camera
  height 100%
</style>
