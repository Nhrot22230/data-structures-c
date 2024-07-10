#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include "DataType.h"

struct DynArr {
  void *arr;
  enum DataType dtype;
  unsigned long dtype_size;
  unsigned long size;
  unsigned long capacity;
};


int DynArr_init(struct DynArr *dynArr, unsigned long initialSize, enum DataType dataType);
int DynArr_clear(struct DynArr *dynArr);
int DynArr_expand(struct DynArr *dynArr, unsigned long cap);
int DynArr_pushback(struct DynArr *dynArr, void *data);
int DynArr_popback(struct DynArr *dynArr);
int DynArr_insertAt(struct DynArr *dynArr, void *data, unsigned long idx);
const void *DynArr_dataAt(struct DynArr *dynArr, unsigned long idx);
void DynArr_print(struct DynArr *dynArr);
void DynArr_sort(struct DynArr *dynArr, unsigned long begin, unsigned long end, int (*cmp_func)(void *, void*));


int DynArr_init_custom(struct DynArr *dynArr, unsigned long initialSize, unsigned long dTypeSize);
int DynArr_clear_custom(struct DynArr *dynArr, CustomFunc freeFunc);
int DynArr_expand_custom(struct DynArr *dynArr, unsigned long cap, CustomFunc allocFunc);
int DynArr_pushback_custom(struct DynArr *dynArr, void *data, CustomFunc allocFunc);
int DynArr_popback_custom(struct DynArr *dynArr, CustomFunc freeFunc);
int DynArr_insertAt_custom(struct DynArr *dynArr, void *data, unsigned long idx, AssignFunc assignFunc);
const void *DynArr_dataAt_custom(struct DynArr *dynArr, unsigned long idx);
void DynArr_print_custom(struct DynArr *dynArr, CustomFunc printFunc);


#endif //DYNAMICARRAY_H
