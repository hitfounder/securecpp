#/bin/sh

mkdir build
cd build

export CXX=/usr/bin/clang++
cmake ..
make

./fuzztest ../corpus
