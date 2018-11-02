require('babel-register');
require('babel-polyfill');

const EOS = require('eosjs');


(async () => {
    const eos = EOS({
        httpEndpoint: 'http://localhost:8888', 
        chainId: 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f', 
        keyProvider: '5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3',
    });
    
    let contract = await eos.contract('tpass');

    try {
        await contract.sendTrans('tpass');
    }
    catch (e) {
        console.log(e);
    }
})();
