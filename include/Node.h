#ifndef NODE_H
#define NODE_H
#include "DataType.h"

struct Node {
  void *elem;
  enum DataType dtype;
  unsigned long dtype_size;
  struct Node *next;
};

struct Node *Node_create();
void Node_init(struct Node *node, void *data, enum DataType dtype);
void Node_copy(struct Node *dest, struct Node *src);
void Node_setElem(struct Node *node, void *data);
void Node_free(struct Node *node, int freeNext);
void Node_print(struct Node *node);

void Node_init_custom(struct Node *node, void *data, unsigned long dSize, AssignFunc Assign);
void Node_copy_custom(struct Node *dest, struct Node *src, AssignFunc Assign);
void Node_setElem_custom(struct Node *node, void *data, AssignFunc Assign);
void Node_free_custom(struct Node *node, CustomFunc Free, int freeNext);
void Node_print_custom(struct Node *node, PrintFunc Print);


#endif//NODE_H
