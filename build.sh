BINARIES_DIRECTORY=./bin/

mkdir -p $BINARIES_DIRECTORY

pushd open-zwave
make
popd

g++ Main.cpp open-zwave/libopenzwave.a -std=c++17 -pthread -lresolv -lcurl -I./open-zwave/cpp/src/ -o $BINARIES_DIRECTORY/jottai.raspberry-zwave
