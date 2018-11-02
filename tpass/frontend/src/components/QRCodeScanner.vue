<template>
  <qrcode-stream
    class="camera"
    @decode="onDecode"
    :paused="paused"
    :camera="cameraOptions"
    style="background-size: cover;"
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
          facingMode: { ideal: 'environment' },
          height: {ideal: 1080}
        }
      }
    }
  },
  methods: {
    onDecode (decodedString) {
      this.paused = true
      let data = JSON.parse(decodedString)
      console.log(`onDecode(): QR code data - "${decodedString}"`)
      if (this.isQRDataValid(data)) {
        this.$emit('transaction-init', data)
      } else {
        this.$emit('invalid-data', data)
        this.paused = false
      }
    },
    isQRDataValid (data) {
      return true
    }
  }
}
</script>

<style lang="stylus" scoped>
.qrcode-stream__camera
  object-fit cover!imporant

.camera
  height 100%
</style>
