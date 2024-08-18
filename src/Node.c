#include "Node.h"
#include <stdlib.h>
#include <stdio.h>

/* 
 * ====================================================================
 * Node Functions
 * ====================================================================
*/

struct Node *Node_create() {
  struct Node *node = malloc(sizeof(struct Node));
  return node;
}

void Node_init(struct Node *node, void *data, enum DataType dtype) {
  if (dtype == DT_CUSTOM) return;

  node->dtype_size = DataType_size(dtype);
  node->dtype = dtype;
  node->elem = malloc(node->dtype_size);
  DataType_assign(dtype, node->elem, data);
  node->next = NULL;
}

void Node_copy(struct Node *dest, struct Node *src) {
  if (dest == NULL || src == NULL || src->dtype == DT_CUSTOM) return;
  Node_init(dest, src->elem, src->dtype);
  dest->next = src->next;
}

void Node_setElem(struct Node *node, void *data) {
  if (node == NULL || node->dtype == DT_CUSTOM) return;
  if (node->elem == NULL) node->elem = malloc(node->dtype_size);
  DataType_assign(node->dtype, node->elem, data);
}

void Node_free(struct Node *node, int freeNext) {
  if (node == NULL || node->dtype == DT_CUSTOM) return;
  if (node->elem != NULL) free(node->elem);
  if (node->next != NULL && freeNext) {
    Node_free(node->next, 1);
    free(node->next);
  } 
  node->next = NULL;
  node->elem = NULL;
}

void Node_print(struct Node *node) {
  if (node == NULL || node->dtype == DT_CUSTOM) return;
  PrintFunc print = DataType_get_print_func(node->dtype);
  printf("Node info:\n");
  printf("Address    : %p\n", node);
  printf("Next       : %p\n", node->next);
  if (node->elem != NULL) {
    printf("Elem as ptr: %p\n", node->elem);
    printf("Elem       : "); print(node->elem); printf("\n");
  }
}

void Node_init_custom(struct Node *node, void *data, unsigned long dSize, AssignFunc Assign) {
  node->elem = malloc(dSize);
  Assign(node->elem, data);
  node->dtype_size = dSize;
  node->dtype = DT_CUSTOM;
  node->next = NULL;
}

void Node_copy_custom(struct Node *dest, struct Node *src, AssignFunc Assign) {
  if (dest == NULL || src == NULL || src->dtype == DT_CUSTOM) return;
  Node_init_custom(dest, src->elem, src->dtype_size, Assign);
  dest->next = src->next;
}

void Node_setElem_custom(struct Node *node, void *data, AssignFunc Assign) {
  if (node->elem == NULL) node->elem = malloc(node->dtype_size);
  Assign(node->elem, data);
}

void Node_free_custom(struct Node *node, CustomFunc Free, int freeNext) {
  if (node == NULL || node->dtype == DT_CUSTOM) return;
  if (node->elem != NULL) free(node->elem);
  if (node->next != NULL && freeNext) {
    Node_free_custom(node->next, Free, freeNext);
    Free(node->next);
  } 
  node->next = NULL;
}

void Node_print_custom(struct Node *node, PrintFunc Print) {
  if (node == NULL || node->dtype == DT_CUSTOM) return;
  printf("Node info:\n");
  printf("Address    : %p\n", node);
  printf("Next       : %p\n", node->next);
  if (node->elem != NULL) Print(node->elem);
}
