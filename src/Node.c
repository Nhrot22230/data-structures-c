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

  node->dtype = dtype;
  node->dtype_size = DataType_size(dtype);
  node->elem = malloc(node->dtype_size);
  DataType_assign(dtype, node->elem, data);
  node->next = NULL;
  node->dtype = dtype;
}

void Node_copy(struct Node *dest, struct Node *src) {
  if (src->dtype == 0) return;
  if (src->dtype == DT_CUSTOM) return;
  Node_init(dest, src->elem, src->dtype);
}

void Node_setElem(struct Node *node, void *data) {
  if (node->dtype == DT_CUSTOM) return;
  DataType_assign(node->dtype, node->elem, data);
}

void Node_free(struct Node *node) {
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
  printf("Address    : %p\n", node);
  printf("Next       : %p\n", node->next);
  if (node->elem != NULL) {
    printf("Elem as ptr: %p\n", node->elem);
    printf("Elem       : "); print(node->elem); printf("\n");
  }
}
