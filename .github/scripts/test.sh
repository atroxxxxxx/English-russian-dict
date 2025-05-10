#!/bin/bash

BUILD_DIR=$1

cd $BUILD_DIR

./test_exec || CURRENT_EXIT=$?

if [ $CURRENT_EXIT -ne 0 ]; then
  echo "::error:: самостоятельное тестирование с помощью Gtest framework выполняется с ненулевым кодом"
  exit 1
fi

echo "тестирование в порядке"
exit 0
