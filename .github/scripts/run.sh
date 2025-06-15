#!/bin/bash

BUILD_DIR=$1
TESTS_DIR=$2
TEST_NUM=$3

INPUT_FILE="$TESTS_DIR/files/file_$TEST_NUM.txt"
INPUT="$TESTS_DIR/input/input_$TEST_NUM.txt"
EXPECTED_OUT="$TESTS_DIR/output/output_$TEST_NUM.txt"
EXPECTED_ERR="$TESTS_DIR/error/error_$TEST_NUM.txt"
EXPECTED_EXIT=$(awk "NR==$TEST_NUM" "$TESTS_DIR/exit_codes.txt")

cd "$BUILD_DIR" || { echo "::error:: $BUILD_DIR не найдена"; exit 1; }

chmod +x ./run

if [ ! -f ./run ]; then
    echo "::error:: бинарник ./run не найден в $BUILD_DIR"
    exit 1
fi

CURRENT_EXIT=0
if [ -f "$INPUT_FILE" ] && [ -f "$INPUT" ]; then
    ./run "$INPUT_FILE" < "$INPUT" > current_out 2> current_err || CURRENT_EXIT=$?
elif [ -f "$INPUT_FILE" ]; then
    ./run "$INPUT_FILE" > current_out 2> current_err || CURRENT_EXIT=$?
elif [ -f "$INPUT" ]; then
    ./run < "$INPUT" > current_out 2> current_err || CURRENT_EXIT=$?
else
    ./run > current_out 2> current_err || CURRENT_EXIT=$?
fi

if [ $CURRENT_EXIT -ne "$EXPECTED_EXIT" ]; then
    echo "::error:: выходной код программы не совпадает. Ожидается: $EXPECTED_EXIT, получен: $CURRENT_EXIT"
    exit 1
fi

diff -u "$EXPECTED_OUT" current_out || { echo "::error:: вывод в стандартный поток вывода не совпадает"; exit 1; }
diff -u "$EXPECTED_ERR" current_err || { echo "::error:: вывод в стандартный поток ошибок не совпадает"; exit 1; }