#!/bin/bash

# Paths
SRC_DIR="./src"
INCLUDE_DIR="./include"
BUILD_DIR="./build"
LIB_NAME="libdatastructures.a"

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
  mkdir -p $BUILD_DIR
fi

# Compile source files into object files
echo "Compiling source files..."
for src_file in $SRC_DIR/*.c; do
  obj_file=$(basename $src_file .c).o
  gcc -c $src_file -o $BUILD_DIR/$obj_file -I$INCLUDE_DIR
  if [ $? -ne 0 ]; then
    echo "Failed to compile $src_file."
    exit 1
  fi
done

# Create static library
echo "Creating static library..."
ar rcs $BUILD_DIR/$LIB_NAME $BUILD_DIR/*.o
if [ $? -eq 0 ]; then
  echo "Static library $LIB_NAME created successfully in $BUILD_DIR."
else
  echo "Failed to create static library."
  exit 1
fi
