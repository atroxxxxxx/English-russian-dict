#!/bin/bash

BUILD_DIR=$1
TESTS_DIR=$2
TEST_NUM=$3

INPUT_FILE="$TESTS_DIR/input/input_$TEST_NUM.txt"
EXPECTED_OUT="$TESTS_DIR/output/output_$TEST_NUM.txt"
EXPECTED_ERR="$TESTS_DIR/error/error_$TEST_NUM.txt"
EXPECTED_EXIT=$(awk "NR==$TEST_NUM" $TESTS_DIR/exit_codes.txt)

cd "$BUILD_DIR" || { echo "::error::Failed to cd to $BUILD_DIR"; exit 1; }

if [ ! -f ./run ]; then
    echo "::error::Binary ./run not found in $BUILD_DIR"
    exit 1
fi

if [ -f ../$INPUT_FILE ]; then
    ./run ../$INPUT_FILE > current_out 2> current_err || CURRENT_EXIT=$?
else
    ./run > current_out 2> current_err || CURRENT_EXIT=$?
fi

if [ $CURRENT_EXIT -ne $EXPECTED_EXIT ]; then
    echo "::error::Exit code mismatch. Expected $EXPECTED_EXIT, got $CURRENT_EXIT"
    exit 1
fi

diff -u "../$EXPECTED_OUT" current_out || { echo "::error::Stdout mismatch"; exit 1; }
diff -u "../$EXPECTED_ERR" current_err || { echo "::error::Stderr mismatch"; exit 1; }
