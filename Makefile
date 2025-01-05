LIBS=""
INCLUDE=""
CFLAGS="-Wall -Wextra"
CC="gcc"

all:
	$CC src/hello.c

test:
	echo 'Test not implemented yet'

clean:
	rm -rf build
