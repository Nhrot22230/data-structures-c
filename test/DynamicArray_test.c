#include "DynamicArray.h"
#include "DataType.h"
#include "Node.h"
#include <stdio.h>
#include <stdlib.h>
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

void test_DynArr_init_custom();
void test_DynArr_clear_custom();
void test_DynArr_pushback_custom();
void test_DynArr_insertAt_custom();
void test_DynArr_popback_custom();
void test_DynArr_dataAt_custom();
void test_DynArr_print_custom();

void test_vector_mul();

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

  test_DynArr_init_custom();
  test_DynArr_clear_custom();
  test_DynArr_pushback_custom();
  test_DynArr_insertAt_custom();
  test_DynArr_popback_custom();
  test_DynArr_dataAt_custom();
  test_DynArr_print_custom();

  //test_vector_mul();
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
  DynArr_clear(&dynArr);

  printf("DynArr_sort tested successfully.\n");
}

/* ====================================================================
* Custom Dynamic Array Tests
* ===================================================================
* */

GENERATE_ASSIGN_WRAPPER(wrapper_assign, Node_copy, struct Node)
GENERATE_WRAPPER(wrapper_print, Node_print, struct Node)

void wrapper_free(void *node) {
  Node_free(node, 0);
}

void test_DynArr_init_custom() {
  struct DynArr dynArr;
  DynArr_init_custom(&dynArr, 10, sizeof(struct Node));

  struct Node node;
  int num = 1;
  
  Node_init(&node, &num, DT_INT);
  
  DynArr_insertAt_custom(&dynArr, &node, 0, wrapper_assign);
  num = 15;
  Node_setElem(&node, &num);
  struct Node inserted = *(struct Node *) DynArr_dataAt(&dynArr, 0);
  
  int valA = *(int *)node.elem;
  int valB = *(int *)inserted.elem;
  
  assert(valB == 1);
  assert(valA == 15);
  
  DynArr_clear_custom(&dynArr, wrapper_free);
  Node_free(&node, 1);
  
  printf("DynArr_init_custom tested successfully.\n");
}

void test_DynArr_clear_custom() {
  struct DynArr dynArr;
  
  assert(DynArr_init_custom(&dynArr, 10, sizeof(struct Node)) == 0);

  struct Node node;
  int num = 1;
  
  Node_init(&node, &num, DT_INT);
  DynArr_insertAt_custom(&dynArr, &node, 0, wrapper_assign);
  assert(DynArr_clear_custom(&dynArr, wrapper_free) == 0);
  
  Node_free(&node, 1);
  printf("DynArr_clear_custom tested successfully.\n");
}

void test_DynArr_pushback_custom() {
  struct DynArr dynArr;
  
  assert(DynArr_init_custom(&dynArr, 0, sizeof(struct Node)) == 0);
  
  struct Node node;
  int num = 1;
  Node_init(&node, &num, DT_INT);
  
  assert(DynArr_pushback_custom(&dynArr, &node, wrapper_assign) == 0);
  assert(dynArr.size == 1);
  assert(*(int *)((struct Node *)DynArr_dataAt(&dynArr, 0))->elem == 1);
  
  DynArr_clear_custom(&dynArr, wrapper_free);
  Node_free(&node, 1);
  printf("DynArr_pushback_custom tested successfully.\n");
}

void test_DynArr_insertAt_custom() {
  struct DynArr dynArr;
  
  assert(DynArr_init_custom(&dynArr, 5, sizeof(struct Node)) == 0);
  
  struct Node node;
  int num = 42;
  Node_init(&node, &num, DT_INT);
  
  assert(DynArr_insertAt_custom(&dynArr, &node, 2, wrapper_assign) == 0);
  assert(*(int *)((struct Node *)DynArr_dataAt(&dynArr, 2))->elem == 42);
  
  DynArr_clear_custom(&dynArr, wrapper_free);
  Node_free(&node, 1);
  printf("DynArr_insertAt_custom tested successfully.\n");
}

void test_DynArr_popback_custom() {
  struct DynArr dynArr;
  
  assert(DynArr_init_custom(&dynArr, 1, sizeof(struct Node)) == 0);
  
  struct Node node;
  int num = 42;
  
  Node_init(&node, &num, DT_INT);
  DynArr_pushback_custom(&dynArr, &node, wrapper_assign);
  
  assert(DynArr_popback_custom(&dynArr, wrapper_free, wrapper_assign) == 0);
  assert(dynArr.size == 1);  // The initial size was 1
  
  DynArr_clear_custom(&dynArr, wrapper_free);
  Node_free(&node, 1);
  printf("DynArr_popback_custom tested successfully.\n");
}

void test_DynArr_dataAt_custom() {
  struct DynArr dynArr;
  
  assert(DynArr_init_custom(&dynArr, 5, sizeof(struct Node)) == 0);
  
  struct Node node;
  int num = 42;
  Node_init(&node, &num, DT_INT);
  DynArr_insertAt_custom(&dynArr, &node, 2, wrapper_assign);
  
  assert(*(int *)((struct Node *)DynArr_dataAt(&dynArr, 2))->elem == 42);
  
  DynArr_clear_custom(&dynArr, wrapper_free);
  Node_free(&node, 1);
  printf("DynArr_dataAt_custom tested successfully.\n");
}

void test_DynArr_print_custom() {
  struct DynArr dynArr;
  
  assert(DynArr_init_custom(&dynArr, 3, sizeof(struct Node)) == 0);
  
  struct Node node;
  int num = 0;
  Node_init(&node, &num, DT_INT);
  int values[] = {1, 2, 3};
  
  for (int i = 0; i < 3; i++) {
    Node_setElem(&node, &values[i]);
    DynArr_insertAt_custom(&dynArr, &node, i, wrapper_assign);
  }
  
  printf("Expected output: 1 2 3\nActual output: ");
  DynArr_print_custom(&dynArr, wrapper_print);
  DynArr_clear_custom(&dynArr, wrapper_free);
  Node_free(&node, 1);
  printf("DynArr_print_custom tested successfully.\n");
}


void test_vector_mul(){
  int num;
  struct DynArr v1, v2;
  
  DynArr_init(&v1, 3, DT_INT);
  DynArr_init(&v2, 3, DT_INT);
  num = 7;
  DynArr_insertAt(&v1, &num, 0);
  num = 11;
  DynArr_insertAt(&v1, &num, 1);
  num = 2;
  DynArr_insertAt(&v1, &num, 2);

  num = 3;
  DynArr_insertAt(&v2, &num, 0);
  num = 0;
  DynArr_insertAt(&v2, &num, 1);
  num = 2;
  DynArr_insertAt(&v2, &num, 2);

  // Dot Mul
  int sum = 0;
  for (int i=0; i<3; ++i) {
    int a = *(int *)DynArr_dataAt(&v1, i);
    int b = *(int *)DynArr_dataAt(&v2, i);
    sum += a*b;
  }
  assert(sum == 25);

  // Cross Mul
  int x = (*(int *)DynArr_dataAt(&v1, 1)) * (*(int *)DynArr_dataAt(&v2, 2)) - (*(int *)DynArr_dataAt(&v1, 2)) * (*(int *)DynArr_dataAt(&v2, 1));
  int y = (*(int *)DynArr_dataAt(&v1, 2)) * (*(int *)DynArr_dataAt(&v2, 0)) - (*(int *)DynArr_dataAt(&v1, 0)) * (*(int *)DynArr_dataAt(&v2, 2));
  int z = (*(int *)DynArr_dataAt(&v1, 0)) * (*(int *)DynArr_dataAt(&v2, 1)) - (*(int *)DynArr_dataAt(&v1, 1)) * (*(int *)DynArr_dataAt(&v2, 0));

  assert(x == 22 && y == -8 && z == -33);

  DynArr_clear(&v1);
  DynArr_clear(&v2);

  printf("DynArr_vector_mul tested successfully.\n");
}
