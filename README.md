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
![how it works](https://i.imgur.com/sEmQRkM.png)
1. You go to a website integrated with tpass
**Webservice shows you a qr code you scan with your smartphone**
![example site](https://i.imgur.com/TxQ2649.png)
2. **Message for authorization is pushed to hardware device**
3. **You need to authenticate on token and smartphone**
![app](https://i.imgur.com/FuTBI15.png)
![approve login](https://i.imgur.com/V8SqPxy.png)
4. **Blockchain verifies the messages**
5. **You are authorized :)**
![authorized](https://i.imgur.com/Rq2t82o.png)

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

![mobile app](https://i.imgur.com/ey1Q7O0.png)
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

![hardware](https://i.imgur.com/6QkiHeL.jpg)

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
