#!/bin/bash

BUILD_DIR=$1

mkdir "$BUILD_DIR"
sudo apt-get update
sudo apt-get install -y build-essential
cmake -S . -B $BUILD_DIR
cmake --build $BUILD_DIR --target all -- -j$(nproc)
