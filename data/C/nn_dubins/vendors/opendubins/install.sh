#!/bin/sh

mkdir -p build
#cmake --build build -D CMAKE_INSTALL_PREFIX:STRING=./ src
cd build && cmake -D CMAKE_INSTALL_PREFIX=.. ../src
cd -

make -C build 

mkdir -p include
cp -r src/core/include .
cp -r src/planning/include .

mkdir -p lib
cp build/core/*.a lib
cp build/planning/*.a lib


