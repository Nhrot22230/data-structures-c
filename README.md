# Data Structures in C

Welcome to the **Data Structures in C** repository! This project is a collection of common data structures implemented in the C programming language. It is designed to serve as a learning resource for those interested in understanding how these data structures work and how they can be implemented in C.

## Repository Details

- **Repo Name:** data-structures-c
- **Description:** A collection of data structures implemented in C, including dynamic arrays, lists, heaps, B-trees, and tries. This repository serves as a learning resource and a reference for implementing common data structures in C.

## Table of Contents

- [Introduction](#introduction)
- [Data Structures Implemented](#data-structures-implemented)
- [How to Use](#how-to-use)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This repository includes implementations of various data structures such as dynamic arrays, lists, heaps, B-trees, and tries. Each data structure is implemented in its own directory with a corresponding header file and test cases to demonstrate its usage.

## Directory Structure

- `include/` - Contains header files for the data structures.
- `src/` - Contains source files for the data structures.
- `test/` - Contains test files for each data structure.
- `build/` - Directory where compiled files and executables are stored.
- `lib/` - Directory for storing compiled libraries.
- `README.md` - This file.
- `compile.sh` - Script for setting up the project.
- `compile_test.sh` - Script for setting up the tests for the project.

## Data Structures Implemented

- **Dynamic Arrays:** A resizable array that grows as needed.
- **Lists:** A linked list implementation.

## Planned Data Structures

- **Heaps:** A binary heap for priority queue operations.
- **B-Trees:** A balanced tree data structure that maintains sorted data and allows searches, sequential access, insertions, and deletions in logarithmic time.
- **Tries:** A tree-like data structure used to store a dynamic set or associative array where the keys are usually strings.
- **Stack:** A LIFO (Last In, First Out) data structure.
- **Queue:** A FIFO (First In, First Out) data structure.
- **Priority Queue:** A data structure that allows the extraction of the highest priority element.
- **Hash Table:** A data structure that associates keys with values for fast lookups.
- **Graph:** A data structure to represent relationships between pairs of objects.
- **Binary Search Tree:** A binary tree where each node has at most two children, and the left child's value is less than the parent's value and the right child's value is greater.
- **AVL Tree:** A self-balancing binary search tree.
- **Red-Black Tree:** Another type of self-balancing binary search tree.
- **Trie:** A specialized data structure for rapid retrieval of strings.

## How to Use

This section explains how to use the data structures library in your own projects.

### Step 1: Clone the Repository

First, clone the repository to get access to the source code, headers, and pre-built libraries.

```sh
git clone https://github.com/yourusername/data-structures-c.git
cd data-structures-c
```

### Step 2: Build the Library

You can choose to build either a static or shared library.

#### Build Static Library

```sh
./compile.sh
```

#### Build Shared Library

```sh
./compile.sh --shared
```

### Step 3: Copy Header and Library Files

Copy the header files from the `include` directory and the library files from the `lib` directory to your project's directory.

#### Copy Header Files

```sh
cp -r include /path/to/your/project
```

#### Copy Static Library

```sh
cp lib/libdata_structures.a /path/to/your/project/lib
```

#### Copy Shared Library

```sh
cp lib/libdata_structures.so /path/to/your/project/lib
```

### Step 4: Compile Your Project

To compile your project using the data structures library, you need to specify the paths to the header files and the library. Here is an example using `gcc`:

#### Using Static Library

```sh
gcc -o my_project main.c -I/path/to/your/project/include -L/path/to/your/project/lib -ldata_structures
```

#### Using Shared Library

```sh
gcc -o my_project main.c -I/path/to/your/project/include -L/path/to/your/project/lib -ldata_structures -Wl,-rpath,/path/to/your/project/lib
```

### Example Project Structure

Here is an example of how your project directory might look after copying the necessary files:

```
my_project/
├── include/
│   ├── DataType.h
│   ├── DynamicArray.h
│   ├── List.h
│   └── Node.h
├── lib/
│   ├── libdata_structures.a  # or libdata_structures.so
├── src/
│   └── main.c
└── Makefile  # Optional, for automated build process
```

### Example `main.c`

Here is a simple example of what your `main.c` might look like:

```c
#include "DynamicArray.h"
#include "DataType.h"
#include <stdio.h>

int main() {
    struct DynArr dynArr;
    DynArr_init(&dynArr, 0, DT_INT);

    int value = 42;
    DynArr_pushback(&dynArr, &value);

    printf("Value in dynamic array: %d\n", *(int *)DynArr_dataAt(&dynArr, 0));

    DynArr_clear(&dynArr);
    return 0;
}
```

## Contributing

Feel free to contribute to this repository by adding new data structures, improving existing implementations, or fixing bugs. Please make sure to include test cases for any new features or data structures you add.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```
Feel free to customize the repository name, description, and the `README.md` content as needed!
```