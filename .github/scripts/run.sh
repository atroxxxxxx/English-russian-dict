#!/bin/bash

BUILD_DIR=$1
TESTS_DIR=$2
TEST_NUM=$3

INPUT_FILE="$TESTS_DIR/input/input_$TEST_NUM.txt"
EXPECTED_OUT="$TESTS_DIR/output/output_$TEST_NUM.txt"
EXPECTED_ERR="$TESTS_DIR/error/error_$TEST_NUM.txt"
EXPECTED_EXIT=$(awk "NR==$TEST_NUM" "$TESTS_DIR/exit_codes.txt")

cd "$BUILD_DIR"
if [ -f "$INPUT_FILE" ];
then
  ./run > current_out 2> current_error
fi
CURRENT_EXIT=$?

if [ $CURRENT_EXIT -ne $EXPECTED_EXIT ];
then
  echo "::error::Exit code mismatch. Expected $EXPECTED_EXIT, got $ACTUAL_EXIT"
  exit 1
fi

diff -u "$EXPECTED_OUT" actual_out || { echo "::error::Stdout mismatch"; exit 1; }
diff -u "$EXPECTED_ERR" actual_err || { echo "::error::Stderr mismatch"; exit 1; }
