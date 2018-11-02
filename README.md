# tpass
## TWO FACTOR AUTHENTICATION BASED ON BLOCKCHAIN PRIVATE KEYS INSTEAD OF PASSWORDS

## Motivation
Passwords are not secure we all know that. Acually according to studies more than 80% of data breaches comes from unsecure passwords.

**TPass lets you move from old rusty passwords**. All you need is just **two private keys stored in a secure storage on any device** such as computer, smartphone, smartwatch or hardware token. You don’t need to trust 3rd party solutions. And you’ll know about every attempt of login and you will be able to easily revoke authorization and change private keys if something goes wrong.

In this project we use eos blockchain, but you can fork this repo and create your own implementation using any blockchain supporting smart contracts.

## What you find in this repository
This demo project shows you:
1. How to integrate tpass to webpage for authentication
2. How to create smartphone app to work with tpass
3. How to create hardware token to work with tpass
4. How tpass smart contract is build

## How it works
![alt text](https://lh5.googleusercontent.com/sl6Z0wHpqiFg_v_OShv7b1UZzAvIqFH2eK8AwApDL_aYAyXNorciBp8GwzvS_MV0fyC_thWdqQyupVJuSXqA=w1920-h969-rw)
1. **Webservice shows you a qr code you scan with your smartphone**
![alt text](https://lh6.googleusercontent.com/laqRgE9t0JucRzRQAcXY9_sBHZZLGSQNk4XPX3sThW9BXJWinAUs9gWvwcB8tyqhh_TmBKwc5fmY-r-xeZ1d=w1920-h969-rw)
2. **Message for authorization is pushed to hardware device**
3. **You need to authenticate on token and smartphone**
![alt text](https://lh5.googleusercontent.com/ORs2snz7w1FprSnownDArdoJ2-CNJIU0ByCr5M4SYgpzQK6kOlgPmCOgCpXH3Bx2J5dUE3rGJkv_4ow_wpcv=w1920-h920-rw)
![alt text](https://lh5.googleusercontent.com/dwtQ3LD_OTOpB6EikGW0clauB3FUigchQdiXIylFj5-lAy6h9_VNbLka_mkjiv3bBAdJikWZtVCPpqTrTN6b=w1920-h920-rw)
4. **Blockchain verifies the messages**
5. **You are authorized :)**
![alt text](https://lh3.googleusercontent.com/gj3yr_78xTIITRWrpkcVZC5CtPhKz7FaR0MTOpC0UfNdmTBAVHPLt28qy9r0bRG2IRHVuJuu9CUA0KRfG-BQ=w1920-h969)

## Getting Started
The purpose of this paragraph is to setup you development environment and let you develop this project yourself.

This repo contains 4 modules

 1. Smart contract
 2. Hardware module
 3. Mobile app 
 4. Example website integrated with **tpass** 

### Installing

#### Frontend part
To start, we need to have `Docker` installed on your computer. Frontend part of our project can be build by running 
```
docker-compose up --build
```
The app is running under 
`localhost:8080`

![alt text](https://lh3.googleusercontent.com/ymnzKMZPE2A_g4ZmGCooTEM7CW6o0_gzkjJgvc7LvRAU63dDymoj1B289mkW9D5h-6Hr_SRXOzjf1r8z1QLO=w1920-h920-rw)
#### Smartcontract
To start the smartcontract you need to have _EOS.IO_ on your computer. 
Full documentation can be found here [eos](https://developers.eos.io/)

To do this simply run 
```
cd ~
git clone https://github.com/EOSIO/eosio-project-boilerplate-simple
cd eosio-project-boilerplate-simple
```
First you create an alias 
```
alias eosiocpp='docker exec eosio_notechain_container eosiocpp'
```
The folder you need to place our smart contracts is the following
```bash
cd ~/eosio-project-boilerplate-simple/eosio_docker/contracts
```
And run with
```
./quick_start.sh
```
Next, we need to generate a WASM file. A WASM file is a compiled smart contract ready to be uploded to EOSIO network.
```
eosiocpp -o /opt/eosio/bin/contracts/tpass/tpass.wast /opt/eosio/bin/contracts/tpass/tpass.cpp
```
Please note the path to the files is within Docker container, not your host machine, so please add /opt/eosio/bin/contracts/ to point to the right contracts folder.

We now need to generate an ABI file:
```
eosiocpp -g /opt/eosio/bin/contracts/tpass/tpass.abi /opt/eosio/bin/contracts/tpass/tpass.cpp
```
You have created the smart contract. 
To uplad first create user account:
```
alias cleos='docker exec eosio_notechain_container /opt/eosio/bin/cleos -u http://localhost:8888'

cleos create key --to-console
cleos create key --to-console
```
Uplad keys to the wallet
```
cleos wallet import --private-key PRIVATEKEYOWNER
cleos wallet import --private-key PRIVATEKEYACTIVE
```

To create a new account we need to open the eosiomain wallet and then run a cleos command:
```
cleos create account eosio DAOuser pubkey1 pubkey2
cleos get account DAOuser -j
```

Save the keys in a separate file. We will need them later.

To uplad it on blockchain use:
```
cleos set contract testacc /opt/eosio/bin/contracts/example/ --permission DAOuser@active
```
Run the transaction:
```
cleos push action testacc hi '["DAOuser"]' -p DAOuser@active
```


#### Hardware
Hardware uses sparkfun nrf52832 breakout board and 128x64 monochrome oled screen with sh1106 i2c controller.

![alt text](https://lh6.googleusercontent.com/9UITQkZWaEraV00-TlSD-nJtVrFnaR-M58xQcRNi5mjntNouXicZEHnypGd7j972Kg7EX7sMwDXWzXRDdkei=w1920-h920-rw)

To install it on your arduino board you should follow instruction on website [Arduino](https://www.arduino.cc/en/Guide/HomePage)

### Built With
We used in this project
* Docker
* EOS.IO
* C++
* Arduino
* Vue.js
* Quasar
* Webflow.io

## Authors
* **Łukasz Skarżyński**
* **Bartosz Barwikowski**
* **Kondrad Daroch**
* **Łukasz Berwid**

#### Disclaimer
Project made for Malta Blockchain Summit hackathon 2018c</br>
[hackaton website](https://malta-blockchain.devpost.com) </br>
[project page](https://devpost.com/software/tpass)
