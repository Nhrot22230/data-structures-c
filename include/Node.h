#ifndef NODE_H
#define NODE_H
#include "DataType.h"

struct Node {
  void *elem;
  enum DataType dtype;
  unsigned long dtype_size;
  struct Node *next;
};

void Node_init(struct Node *node, void *data, enum DataType dtype);
void Node_copy(struct Node *dest, struct Node *src);
void Node_setElem(struct Node *node, void *data);
void Node_free(struct Node *node);
struct Node *Node_create();
void Node_print(struct Node *node);

#endif//NODE_H
