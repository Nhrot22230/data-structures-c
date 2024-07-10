#!/bin/bash

# Paths
TEST_DIR="./test"
INCLUDE_DIR="./include"
SRC_DIR="./src"
BUILD_DIR="./build"

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
  mkdir -p $BUILD_DIR
fi

# Compile and run each test
for test_file in $TEST_DIR/*.c; do
  test_name=$(basename $test_file .c)
  gcc -o $BUILD_DIR/$test_name $test_file $SRC_DIR/*.c -I$INCLUDE_DIR
  if [ $? -eq 0 ]; then
    echo "Running $test_name..."
    $BUILD_DIR/$test_name
    echo "$test_name executed successfully."
  else
    echo "Failed to compile $test_name."
  fi
done
