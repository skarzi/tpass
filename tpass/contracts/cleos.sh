docker exec -it nodeos /opt/eosio/bin/cleos \
    --url http://127.0.0.1:8888 \
    --wallet-url http://172.23.0.3:9876 \
    $@
