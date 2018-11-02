docker run -d -p 9876:9876 --name keosd --network=eosdev \
-i eosio/eos-dev /bin/bash -c "keosd --http-server-address=0.0.0.0:9876 --http-validate-host=0"
