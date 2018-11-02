import Eos from 'eosjs'
import { walletsAPI } from './axiosInstances'

function EOSClient (accountName) {
  this.accountName = accountName
  this.httpEndpoint = 'http://192.168.4.2:8888'
  this.chainId = 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f'
  this.keyProvider = '5Jmr1vo2inBPv7sUBBgiYzK6JxZhpY8To2E5X79pyRh8NAxH46j'
  this._client = Eos({httpEndpoint: this.httpEndpoint, chainId: this.chainId, keyProvider: this.keyProvider})
}

EOSClient.prototype.startTransaction = function (contractName, recipient, amount) {
  amount = `${amount.toFixed(4)} EOS`
  return this._client.contract(contractName).then((contract) => {
    let options = { authorization: this.accountName }
    return contract.send(recipient, amount, options)
  })
}

// ostatnia tranzakcje wysylam do barwika
EOSClient.prototype.outgoingTransactions = function () {
  return this._client.contract('easeos').then((contract) => {
    // let options = { authorization: this.accountName }
    return this._client.getTableRows({
      code: 'easeos',
      scope: 'easeos',
      table: 'outgoing',
      json: true
    })
  })
}

EOSClient.prototype.endTransaction = function (transferTransaction) {
  return this._client.pushTransaction(transferTransaction)
}

EOSClient.prototype.manageTransaction = function (transactionData) {
  console.log(`managing transaction ${transactionData}`)
  let data = {
    data: {
      from: this.accountName,
      to: transactionData.to,
      amount: transactionData.amount,
      date: transactionData.date,
      chainId: this.chainId
    }
  }
  console.log('sending to wallet')
  console.log(data)
  return walletsAPI.post('/sign', data).then((response) => {
    if (response.data.status === 'CONFIRMED') {
      console.log('transaction confirmed')
      return this.endTransaction(response.hash)
    } else {
      console.log('transaction NOT confirmed')
      return response
    }
  })
}

export default EOSClient
