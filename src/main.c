#include "DataType.h"
#include "DynamicArray.h"
#include "data_structures.h"

#include <stdio.h>
#include <stdlib.h>

void DynArr_test(void){
  struct DynArr int_arr;
  DynArr_init(&int_arr, 0, DT_INT);
  int arr[2] = {0,0};
  for(unsigned long i=0; i<10; ++i){
    arr[0] = i;
    DynArr_pushback(&int_arr, &arr[0]);
  }

  DynArr_print(&int_arr);
  DynArr_sort(&int_arr, 0, int_arr.size - 1, NULL);
  DynArr_print(&int_arr);
  printf("Cap : %ld\n", int_arr.capacity);
  printf("Size: %ld\n", int_arr.size);
  printf("5th: %d\n", *((int *) DynArr_dataAt(&int_arr, 5)));
  DynArr_clear(&int_arr);
}

void Wrap_Node_copy(void *dest, void *src){
  struct Node *dest_node = dest;
  struct Node *src_node = src;

  Node_init(dest_node, src_node->elem, src_node->dtype);
}

int Wrap_Node_free(void *node) {
  struct Node *free_node = node;
  printf("Hello\n");
  Node_free(free_node);
  return 0;
}

void DynArr_test_custom(void){
  struct DynArr dynArr;
  struct Node inode;
  int num = 5;
  Node_init(&inode, &num, DT_INT);
  DynArr_init_custom(&dynArr, 10, sizeof(struct Node));
  DynArr_insertAt_custom(&dynArr, &inode, 0, Wrap_Node_copy);
  
  *(int*)inode.elem = 8;
  struct Node lostnode = *(struct Node *) DynArr_dataAt(&dynArr, 0); 

  Node_print(&inode);
  Node_print(&lostnode);

  DynArr_clear_custom(&dynArr, Wrap_Node_free);
  
  Node_print(&inode);
  Node_print(&lostnode);
  
  Node_free(&inode);
  Node_free(&lostnode);
}

void Node_test(void) {
  int a = 5, b = 1;
  struct Node dest, src;
  Node_init(&src, &a, DT_INT);
  Node_init(&dest, src.elem, DT_INT);
  DataType_assign(dest.dtype, dest.elem, &b);
  printf("Node: {%d}\n", *(int *)src.elem);
  printf("Node: {%d}\n", *(int *)dest.elem);
  
  Node_free(&src);
  Node_free(&dest);
}

void List_test(void){
  struct List list;
  List_init(&list, DT_INT);

  for(int i=0; i < 10; ++i) {
    int num = i;//1 + i%7*(i%5 - i%3);
    List_insert(&list, &num, -1);
  }
  List_print(&list);
  List_free(&list);
}

int main(){
  DynArr_test_custom();
  //Node_test();
  //List_test();
  return 0;
}
