<template>
  <q-layout view="lHh Lpr lFf">
    <q-layout-header>
      <q-toolbar
        color="primary"
        :glossy="$q.theme === 'mat'"
        :inverted="$q.theme === 'ios'"
      >
        <q-btn
          flat
          dense
          round
          @click="goBack"
        >
          <!-- app logo goes here -->
          <q-icon name="category" />
        </q-btn>
        <q-toolbar-title>
          tpass
        </q-toolbar-title>
      </q-toolbar>
    </q-layout-header>

    <q-page-container>
      <router-view />
    </q-page-container>

  </q-layout>
</template>

<script>
export default {
  name: 'MyLayout',
  data () {
    return {
    }
  },
  methods: {
    goBack () {
      this.$router.push('/')
    }
  }
}
</script>

<style>
</style>
