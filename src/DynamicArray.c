#include "DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 
 * ====================================================================
 * Dynamic Array Functions
 * ====================================================================
*/

int DynArr_init(struct DynArr *dynArr, unsigned long initialSize, enum DataType dType){
  if (dType == DT_CUSTOM) return -1;
  
  dynArr->dtype_size = DataType_size(dType);
  if(dynArr->dtype_size == 0) return -2;
  dynArr->dtype = dType;
  dynArr->size = initialSize;
  dynArr->capacity = 2;
  
  for(unsigned long cap = 2; cap <= initialSize; cap = cap*2) {
    dynArr->capacity = cap * 2;
  }
  
  dynArr->arr = malloc(dynArr->capacity * dynArr->dtype_size);
  if (dynArr->arr == NULL) return -2;
  return 0;
}

int DynArr_clear(struct DynArr *dynArr){
  if (dynArr->capacity == 0) return -1;
  if (dynArr->arr == NULL) return -2;

  free(dynArr->arr);
  dynArr->arr = NULL;
  dynArr->capacity = 0;
  dynArr->size = 0;
  return 0;
}

int DynArr_expand(struct DynArr *dynArr, unsigned long cap){
  if (dynArr->dtype == DT_CUSTOM) return -1;
  if (dynArr->capacity == 0) return -2;

  unsigned long to_alloc = dynArr->dtype_size * cap;
  void *aux = malloc(to_alloc);
  if (aux == NULL) return -3;

  void *i_ptr = NULL, *j_ptr = NULL;
  for (unsigned long i = 0; i < dynArr->size && i < cap; ++i) {
    i_ptr = (char *)dynArr->arr + i*dynArr->dtype_size;
    j_ptr = (char *)aux + i*dynArr->dtype_size;
    DataType_assign(dynArr->dtype, j_ptr, i_ptr);
  }

  free(dynArr->arr);
  dynArr->arr = aux;
  dynArr->capacity = cap;
  return 0;
}

int DynArr_pushback(struct DynArr *dynArr, void *data){
  if (dynArr->dtype == DT_CUSTOM) return -1;
  if (dynArr->capacity == 0) return -2;
  
  unsigned long idx = dynArr->size;
  if(dynArr->size + 1 == dynArr->capacity && DynArr_expand(dynArr, dynArr->capacity*2) < 0) return -3;
  
  void *element = (char *)dynArr->arr + idx*dynArr->dtype_size;
  
  DataType_assign(dynArr->dtype, element, data);
  dynArr->size++;
  return 0;
}

int DynArr_insertAt(struct DynArr *dynArr, void *data, unsigned long idx) {
  if (dynArr->dtype == DT_CUSTOM) return -1;
  if(dynArr->capacity == 0 || dynArr->size == 0) return -2;
  if(idx >= dynArr->size) return -3;

  void *element = (char *)dynArr->arr + idx * dynArr->dtype_size;
  DataType_assign(dynArr->dtype, element, data);
  
  return 0;
}

int DynArr_popback(struct DynArr *dynArr) {
  if (dynArr->dtype == DT_CUSTOM) return -1;
  if (dynArr->capacity == 0 || dynArr->size == 0) return -2;
  
  unsigned long idx = dynArr->size - 1;
  void *element = (char *)dynArr->arr + idx * dynArr->dtype_size;

  switch (dynArr->dtype) {
    case DT_CHAR: 
      *((char *) element) = 0;
      break;
    case DT_INT: 
      *((int *) element) = 0;
      break;
    case DT_FLOAT:
      *((float *)element) = 0;
      break;
    case DT_LONG: 
      *((long *)element) = 0;
      break;
    case DT_DOUBLE:
      *((double *)element) = 0;
      break;
    case DT_UNSIGNED_INT:
      *((unsigned int *)element) = 0;
      break;
    case DT_UNSIGNED_LONG:
      *((unsigned long *)element) = 0;
      break;
    default: break;
  }
  dynArr->size--;

  if (dynArr->size < dynArr->capacity / 4 && 
      DynArr_expand(dynArr, dynArr->capacity / 2) < 0) 
    return -3;

  return 0;
}

const void *DynArr_dataAt(struct DynArr *dynArr, unsigned long idx) {
  if(dynArr->capacity == 0 || dynArr->size == 0) return NULL;
  if(idx > dynArr->size) return NULL;

  void *element = (char *)dynArr->arr + idx * dynArr->dtype_size;

  return element;
}

void DynArr_print(struct DynArr *dynArr) {
  if (dynArr->dtype == DT_CUSTOM) return;
  if (dynArr->capacity == 0 || dynArr->size == 0) return;

  PrintFunc print_func = DataType_get_print_func(dynArr->dtype);
  if (print_func == NULL) {
    printf("Unknown data type\n");
    return;
  }

  for(unsigned long i = 0; i<dynArr->size; ++i) {
    if (i != 0) printf(" ");
    void *element = (char *)dynArr->arr + i*dynArr->dtype_size;
    print_func(element);
  }
  printf("\n");
}

void merge(void *arr, unsigned long l, unsigned long m, unsigned long r, enum DataType dtype, int (*cmp_func)(void *, void *)) {
  unsigned long n1 = m - l + 1;
  unsigned long n2 = r - m;

  void *L = malloc(n1 * DataType_size(dtype));
  void *R = malloc(n2 * DataType_size(dtype));

  if (L == NULL || R == NULL) {
      if (L) free(L);
      if (R) free(R);
      return;
  }

  memcpy(L, (char *)arr + l * DataType_size(dtype), n1 * DataType_size(dtype));
  memcpy(R, (char *)arr + (m + 1) * DataType_size(dtype), n2 * DataType_size(dtype));

  unsigned long i = 0, j = 0, k = l;

  void *i_ptr, *j_ptr, *k_ptr;
  while (i < n1 && j < n2) {
    i_ptr = (char *)L   + i * DataType_size(dtype);
    j_ptr = (char *)R   + j * DataType_size(dtype);
    k_ptr = (char *)arr + k * DataType_size(dtype);

    if (cmp_func(i_ptr, j_ptr) <= 0) {
      DataType_assign(dtype, k_ptr, i_ptr);
      i++;
    } else {
      DataType_assign(dtype, k_ptr, j_ptr);
      j++;
    }
    k++;
  }

  while (i < n1) {
    i_ptr = (char *)L   + i * DataType_size(dtype);
    k_ptr = (char *)arr + k * DataType_size(dtype);
    DataType_assign(dtype, k_ptr, i_ptr);
    i++;
    k++;
  }

  while (j < n2) {
    j_ptr = (char *)R   + j * DataType_size(dtype);
    k_ptr = (char *)arr + k * DataType_size(dtype);
    DataType_assign(dtype, k_ptr, j_ptr);
    j++;
    k++;
  }

  free(L);
  free(R);
}

void mergeSort(void *arr, unsigned long l, unsigned long r, enum DataType dtype, int (*cmp_func)(void *, void *)) {
  if (l >= r) return;
  unsigned long m = l + (r - l) / 2;

  mergeSort(arr, l, m, dtype, cmp_func);
  mergeSort(arr, m + 1, r, dtype, cmp_func);

  merge(arr, l, m, r, dtype, cmp_func);
}

void DynArr_sort(struct DynArr *dynArr, unsigned long begin, unsigned long end, int (*cmp_func)(void *, void *)) {
  if (dynArr->capacity == 0 || dynArr->size == 0 || begin >= end || end >= dynArr->size) return;
  if (dynArr->dtype == DT_CUSTOM) return;

  if (cmp_func == NULL) cmp_func = DataType_get_cmp_func(dynArr->dtype);
  mergeSort(dynArr->arr, begin, end, dynArr->dtype, cmp_func);
}

/* 
 * ====================================================================
 * DynArr_Custom Functions
 * ====================================================================
*/

int DynArr_init_custom(struct DynArr *dynArr, unsigned long initialSize, unsigned long dTypeSize){
  if (dTypeSize == 0) return -1;
  dynArr->dtype = DT_CUSTOM;
  dynArr->dtype_size = dTypeSize;
  dynArr->size = initialSize;
  dynArr->capacity = 1;
  for(unsigned long cap = 1; cap <= initialSize; cap*=2){
    dynArr->capacity = cap*2;
  }

  dynArr->arr = malloc(dynArr->capacity*dynArr->dtype_size);
  if(dynArr->arr == NULL) return -2;
  memset(dynArr->arr, 0, dynArr->capacity*dynArr->dtype_size);
  return 0;
}

int DynArr_insertAt_custom(struct DynArr *dynArr, void *data, unsigned long idx, 
    AssignFunc assignFunc) {
  if (dynArr->dtype != DT_CUSTOM) return -1;
  if (dynArr->capacity == 0 || idx >= dynArr->size) return -2;

  void *elem = (char *)dynArr->arr + idx*dynArr->dtype_size;
  assignFunc(elem, data);

  return 0;
}

int DynArr_clear_custom(struct DynArr *dynArr, CustomFunc freeFunc) {
  if (dynArr->dtype != DT_CUSTOM) return -1;
  if (dynArr->arr == NULL) return -2;

  if (freeFunc != NULL) {
    void *i_ptr = NULL;
    for (unsigned int i=0; i < dynArr->size; ++i) {
      i_ptr = (char *)dynArr->arr + i*dynArr->dtype_size;
      freeFunc(i_ptr);
    }
  }
  
  free(dynArr->arr);
  dynArr->arr = NULL;
  return 0;
}


void DynArr_print_custom(struct DynArr *dynArr, CustomFunc printFunc) {
  if (dynArr->dtype != DT_CUSTOM) return;
  if (dynArr->capacity == 0) return;

  void *i_ptr = NULL;
  for (unsigned long i = 0; i < dynArr->size; ++i) {
    i_ptr = (char *)dynArr->arr + i*dynArr->dtype_size;
    printFunc(i_ptr);
  }
  printf("\n");
}


