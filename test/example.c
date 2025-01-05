#include <stdio.h>
#include <assert.h>

// Example function - Should be extracte from src directory
int add(int a, int b) {
    return a + b;
}


void test_add() {
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
    assert(add(0, 0) == 0);
    assert(add(-2, -3) == -5);
    printf("All tests passed!\n");
}

int main() {
    test_add();
    return 0;
}

