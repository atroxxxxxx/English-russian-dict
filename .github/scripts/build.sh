#!/bin/bash

BUILD_DIR="$1"
cmake -S . -B $BUILD_DIR
make
