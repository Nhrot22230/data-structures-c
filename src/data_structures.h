#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include "DataType.h"

struct Node {
  void *elem;
  enum DataType dtype;
  unsigned long dtype_size;
  struct Node *next;
};

void Node_init(struct Node *node, void *data, enum DataType dtype);
void Node_free(struct Node *node);
struct Node *Node_create(void *data, enum DataType dtype);
void Node_print(struct Node *node);


struct List {
  struct Node *head;
  struct Node *tail;
  enum DataType dtype;
  unsigned long dtype_size;
  int len;
};


void List_init(struct List *list, enum DataType dtype);
void List_insert(struct List *list, void *data, unsigned long idx);
void List_print(struct List *list);
void List_free(struct List *list);
#endif // DATA_STRUCTURES_H
