#include "data_structures.h"
#include <stdlib.h>
#include <stdio.h>

/* 
 * ====================================================================
 * Node Functions
 * ====================================================================
*/

struct Node *Node_create(void *data, enum DataType dtype) {
  struct Node *node = malloc(sizeof(struct Node));
  Node_init(node, data, dtype);
  return node;
}


void Node_init(struct Node *node, void *data, enum DataType dtype) {
  node->dtype = dtype;
  node->dtype_size = DataType_size(dtype);
  node->elem = malloc(node->dtype_size);
  DataType_assign(dtype, node->elem, data);
  node->next = NULL;
  node->dtype = dtype;
}

void Node_free(struct Node *node) {
  printf("Node free is called on: %p\n", node);
  if (node->elem != NULL) free(node->elem);
  if (node->next != NULL) {
    Node_free(node->next);
    free(node->next);
  }
  
  node->next = NULL;
  node->elem = NULL;
}

void Node_print(struct Node *node) {
  PrintFunc print = DataType_get_print_func(node->dtype);
  printf("Node info:\n");
  printf("Addres     : %p\n", node);
  printf("Next       : %p\n", node->next);
  printf("Elem as ptr: %p\n", node->elem);
  printf("Elem       :"); print(node->elem); printf("\n");
}

void List_init(struct List *list, enum DataType dtype){
  list->len = 0;
  list->head = NULL;
  list->tail = NULL;
  list->dtype = dtype;
}

void List_insert(struct List *list, void *data, unsigned long idx) {
  struct Node *node = Node_create(data, list->dtype);
  if (node == NULL) return;
  if (list->head == NULL) {
    list->head = node;
    list->tail = list->head;
  }
  else if (idx == 0) {
    node->next = list->head;
    list->head = node;
  }
  else if (idx >= list->len) {
    list->tail->next = node;
    list->tail = node;
  }
  else {
    struct Node *prev = NULL;
    struct Node *curr = list->head;

    for (unsigned long i = 0; i < idx; ++i) {
      prev = curr;
      curr = curr->next;
    }

    prev->next = node;
    node->next = curr;
  }
  list->len++;
}


void List_print(struct List *list) {
  PrintFunc print = DataType_get_print_func(list->dtype);
  struct Node *cur = list->head;
  while(cur != NULL) {
    print(cur->elem);
    printf(" -> ");
    cur = cur->next;
  }
  printf("NULL\n");
}


void List_free(struct List *list){
  if (list->head != NULL) {
    Node_free(list->head);
    free(list->head);
    list->head = NULL;
  }
  list->len = 0;
}
