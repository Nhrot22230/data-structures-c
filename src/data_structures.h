#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

enum DataType {
  DT_CHAR,
  DT_PTR, // La idea es poder guardar structuras pero lo veo complicado
  DT_INT,
  DT_FLOAT,
  DT_LONG,
  DT_DOUBLE,
  DT_UNSIGNED_INT,
  DT_UNSIGNED_LONG
};

typedef void (*PrintFunc)(void *);
typedef int (*CmpFunc)(void *, void *);

PrintFunc DataType_get_print_func(enum DataType dtype);
CmpFunc DataType_get_cmp_func(enum DataType dtype);
unsigned long DataType_size(enum DataType dtype);
void DataType_assign(enum DataType dtype, void *element, void *data);
void DataType_format(enum DataType dtype, char *buffer);

struct DynArr {
  void *arr;
  enum DataType dtype;
  unsigned long size;
  unsigned long capacity;
};

int DynArr_init(struct DynArr *dynArr, unsigned long initialSize, 
    enum DataType dataType);
int DynArr_clear(struct DynArr *dynArr);
int DynArr_expand(struct DynArr *dynArr, unsigned long cap);
int DynArr_pushback(struct DynArr *dynArr, void *data);
int DynArr_popback(struct DynArr *dynArr);
int DynArr_insertAt(struct DynArr *dynArr, void *data, unsigned long idx);
const void *DynArr_dataAt(struct DynArr *dynArr, unsigned long idx);
void DynArr_print(struct DynArr *dynArr);
void DynArr_sort(struct DynArr *dynArr, unsigned long begin, 
    unsigned long end, int (*cmp_func)(void *, void*));


struct Node {
  void *elem;
  struct Node *next;
};

struct List {
  struct Node *head;
  struct Node *tail;
  int len;
};



#endif // DATA_STRUCTURES_H
