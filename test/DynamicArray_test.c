#include "DynamicArray.h"
#include "DataType.h"
#include <stdio.h>
#include <assert.h>

// Function prototypes for the test functions
void test_DynArr_init();
void test_DynArr_clear();
void test_DynArr_expand();
void test_DynArr_pushback();
void test_DynArr_insertAt();
void test_DynArr_popback();
void test_DynArr_dataAt();
void test_DynArr_print();
void test_DynArr_sort();

void DynArr_test_all() {
  test_DynArr_init();
  test_DynArr_clear();
  test_DynArr_expand();
  test_DynArr_pushback();
  test_DynArr_insertAt();
  test_DynArr_popback();
  test_DynArr_dataAt();
  test_DynArr_print();
  test_DynArr_sort();

  printf("All dynamic array tests passed successfully.\n");
}

int main() {
  DynArr_test_all();
  return 0;
}

void test_DynArr_init() {
  struct DynArr dynArr;
  assert(DynArr_init(&dynArr, 5, DT_INT) == 0);
  assert(dynArr.size == 5);
  assert(dynArr.capacity >= 5);
  assert(dynArr.dtype == DT_INT);
  assert(dynArr.dtype_size == sizeof(int));
  DynArr_clear(&dynArr);

  printf("DynArr_init tested successfully.\n");
}

void test_DynArr_clear() {
  struct DynArr dynArr;
  DynArr_init(&dynArr, 5, DT_INT);
  assert(DynArr_clear(&dynArr) == 0);
  assert(dynArr.arr == NULL);
  assert(dynArr.size == 0);
  assert(dynArr.capacity == 0);

  printf("DynArr_clear tested successfully.\n");
}

void test_DynArr_expand() {
  struct DynArr dynArr;
  DynArr_init(&dynArr, 5, DT_INT);
  assert(DynArr_expand(&dynArr, 20) == 0);
  assert(dynArr.capacity >= 20);
  DynArr_clear(&dynArr);

  printf("DynArr_expand tested successfully.\n");
}

void test_DynArr_pushback() {
  struct DynArr dynArr;
  DynArr_init(&dynArr, 0, DT_INT);
  int value = 42;
  assert(DynArr_pushback(&dynArr, &value) == 0);
  assert(dynArr.size == 1);
  assert(*(int *)DynArr_dataAt(&dynArr, 0) == value);
  DynArr_clear(&dynArr);

  printf("DynArr_pushback tested successfully.\n");
}

void test_DynArr_insertAt() {
  struct DynArr dynArr;
  DynArr_init(&dynArr, 5, DT_INT);
  int value = 42;
  assert(DynArr_insertAt(&dynArr, &value, 2) == 0);
  assert(*(int *)DynArr_dataAt(&dynArr, 2) == value);
  DynArr_clear(&dynArr);

  printf("DynArr_insertAt tested successfully.\n");
}

void test_DynArr_popback() {
  struct DynArr dynArr;
  DynArr_init(&dynArr, 1, DT_INT);
  int value = 42;
  DynArr_pushback(&dynArr, &value);
  assert(DynArr_popback(&dynArr) == 0);
  assert(dynArr.size == 1);  // The initial size was 1
  DynArr_clear(&dynArr);

  printf("DynArr_popback tested successfully.\n");
}

void test_DynArr_dataAt() {
  struct DynArr dynArr;
  DynArr_init(&dynArr, 5, DT_INT);
  int value = 42;
  DynArr_insertAt(&dynArr, &value, 2);
  assert(*(int *)DynArr_dataAt(&dynArr, 2) == value);
  DynArr_clear(&dynArr);

  printf("DynArr_dataAt tested successfully.\n");
}

void test_DynArr_print() {
  struct DynArr dynArr;
  DynArr_init(&dynArr, 3, DT_INT);
  int values[] = {1, 2, 3};
  for (int i = 0; i < 3; i++) {
      DynArr_insertAt(&dynArr, &values[i], i);
  }
  printf("Expected output: 1 2 3\nActual output: ");
  DynArr_print(&dynArr);
  DynArr_clear(&dynArr);

  printf("DynArr_print tested successfully.\n");
}

void test_DynArr_sort() {
  struct DynArr dynArr;
  DynArr_init(&dynArr, 5, DT_INT);
  int values[] = {5, 3, 4, 1, 2};
  for (int i = 0; i < 5; i++) {
      DynArr_insertAt(&dynArr, &values[i], i);
  }
  DynArr_sort(&dynArr, 0, dynArr.size - 1, NULL);
  printf("Expected output: 1 2 3 4 5\nActual output: ");
  DynArr_print(&dynArr);
  DynArr_clear(&dynArr);

  printf("DynArr_sort tested successfully.\n");
}

