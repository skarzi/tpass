./sync.sh
docker exec nodeos eosiocpp -g work/tpass.abi work/tpass.cpp
docker exec nodeos ls work/tpass.abi
