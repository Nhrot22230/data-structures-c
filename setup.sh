BUILD_DIR="build"
LIB_DIR="lib/"

rm -rf $BUILD_DIR
mkdir $BUILD_DIR

gcc -o "$BUILD_DIR/main" src/data_structures.c src/main.c


