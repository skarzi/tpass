./sync.sh
docker exec nodeos eosiocpp -o work/tpass.wast work/tpass.cpp
docker exec nodeos ls work/tpass.wast
docker exec nodeos ls work/tpass.wasm
