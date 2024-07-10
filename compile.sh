#!/bin/bash

# Paths
SRC_DIR="./src"
INCLUDE_DIR="./include"
BUILD_DIR="./build"
LIB_DIR="./lib"
STATIC_LIB_NAME="libdata_structures.a"
SHARED_LIB_NAME="libdata_structures.so"

# Create build and lib directories if they don't exist
if [ ! -d "$BUILD_DIR" ]; then
  mkdir -p $BUILD_DIR
fi

if [ ! -d "$LIB_DIR" ]; then
  mkdir -p $LIB_DIR
fi

# Function to compile source files into object files
compile_sources() {
  echo "Compiling source files..."
  for src_file in $SRC_DIR/*.c; do
    obj_file=$(basename $src_file .c).o
    gcc -c $src_file -o $BUILD_DIR/$obj_file -I$INCLUDE_DIR
    if [ $? -ne 0 ]; then
      echo "Failed to compile $src_file."
      exit 1
    fi
  done
}

# Function to create static library
create_static_library() {
  echo "Creating static library..."
  ar rcs $LIB_DIR/$STATIC_LIB_NAME $BUILD_DIR/*.o
  if [ $? -eq 0 ]; then
    echo "Static library $STATIC_LIB_NAME created successfully in $LIB_DIR."
  else
    echo "Failed to create static library."
    exit 1
  fi
}

# Function to create shared library
create_shared_library() {
  echo "Creating shared library..."
  gcc -shared -o $LIB_DIR/$SHARED_LIB_NAME $BUILD_DIR/*.o
  if [ $? -eq 0 ]; then
    echo "Shared library $SHARED_LIB_NAME created successfully in $LIB_DIR."
  else
    echo "Failed to create shared library."
    exit 1
  fi
}

# Parse command line arguments
BUILD_SHARED=0

for arg in "$@"
do
  case $arg in
    --shared)
    BUILD_SHARED=1
    shift
    ;;
    *)
    echo "Invalid option: $arg"
    echo "Usage: $0 [--shared]"
    exit 1
    ;;
  esac
done

# Compile sources
compile_sources

# Create the appropriate library based on the flag
if [ $BUILD_SHARED -eq 1 ]; then
  create_shared_library
else
  create_static_library
fi

