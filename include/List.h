#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include "DataType.h"
#include "Node.h"

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
