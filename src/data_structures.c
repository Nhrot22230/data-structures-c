#include "data_structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_char(void *data) {
  printf("%c", *(char *)data);
}

void print_ptr(void *data) {
  printf("%p", *(void **)data);
}

void print_int(void *data) {
  printf("%d", *(int *)data);
}

void print_float(void *data) {
  printf("%f", *(float *)data);
}

void print_long(void *data) {
  printf("%ld", *(long *)data);
}

void print_double(void *data) {
  printf("%lf", *(double *)data);
}

void print_unsigned_int(void *data) {
  printf("%u", *(unsigned int *)data);
}

void print_unsigned_long(void *data) {
  printf("%lu", *(unsigned long *)data);
}

PrintFunc DataType_get_print_func(enum DataType dtype) {
  switch (dtype) {
    case DT_CHAR: return print_char;
    case DT_PTR: return print_ptr;
    case DT_INT: return print_int;
    case DT_FLOAT: return print_float;
    case DT_LONG: return print_long;
    case DT_DOUBLE: return print_double;
    case DT_UNSIGNED_INT: return print_unsigned_int;
    case DT_UNSIGNED_LONG: return print_unsigned_long;
    default: return NULL;
  }
}

int cmp_char(void *i_ptr, void *j_ptr) {
  char a = *(char *)i_ptr;
  char b = *(char *)j_ptr;

  return (a - b);
}

int cmp_int(void *i_ptr, void *j_ptr) {
  int a = *(int *)i_ptr;
  int b = *(int *)j_ptr;

  return (a - b);
}

int cmp_float(void *i_ptr, void *j_ptr) {
  float a = *(float *)i_ptr;
  float b = *(float *)j_ptr;

  return (a - b);
}
int cmp_long(void *i_ptr, void *j_ptr) {
  long a = *(long *)i_ptr;
  long b = *(long *)j_ptr;

  return (a - b);
}
int cmp_double(void *i_ptr, void *j_ptr) {
  double a = *(double *)i_ptr;
  double b = *(double *)j_ptr;

  return (a - b);
}
int cmp_unsigned_int(void *i_ptr, void *j_ptr) {
  unsigned int a = *(unsigned int *)i_ptr;
  unsigned int b = *(unsigned int *)j_ptr;

  return (a - b);
}
int cmp_unsigned_long(void *i_ptr, void *j_ptr) {
  unsigned long a = *(unsigned long *)i_ptr;
  unsigned long b = *(unsigned long *)j_ptr;

  return (a - b);
}

CmpFunc DataType_get_cmp_func(enum DataType dtype) {
  switch (dtype) {
    case DT_CHAR: return cmp_char;
    case DT_PTR: return NULL;
    case DT_INT: return cmp_int;
    case DT_FLOAT: return cmp_float;
    case DT_LONG: return cmp_long;
    case DT_DOUBLE: return cmp_double;
    case DT_UNSIGNED_INT: return cmp_unsigned_int;
    case DT_UNSIGNED_LONG: return cmp_unsigned_long;
    default: return NULL;
  }
}


unsigned long DataType_size(enum DataType dtype) {
  switch (dtype) {
    case DT_CHAR: return 1;
    case DT_PTR: return 4;
    case DT_INT: return 4;
    case DT_FLOAT: return 4;
    case DT_LONG: return 8;
    case DT_DOUBLE: return 8;
    case DT_UNSIGNED_INT: return 4;
    case DT_UNSIGNED_LONG: return 8;
  }

  return 0;
}

void DataType_format(enum DataType dtype, char *buffer) {
  switch (dtype) {
    case DT_CHAR: 
      strcpy(buffer, "%c");
      break;
    case DT_PTR: 
      strcpy(buffer, "%p");
      break;
    case DT_INT: 
      strcpy(buffer, "%d");
      break;
    case DT_FLOAT:
      strcpy(buffer, "%f");
      break;
    case DT_LONG: 
      strcpy(buffer, "%ld");
      break;
    case DT_DOUBLE:
      strcpy(buffer, "%lf");
      break;
    case DT_UNSIGNED_INT:
      strcpy(buffer, "%u");
      break;
    case DT_UNSIGNED_LONG:
      strcpy(buffer, "%lu");
      break;
  }
}


void DataType_assign(enum DataType dtype, void *element, void *data) {
  switch (dtype) {
    case DT_CHAR: 
      *((char *) element) = *((char *) data);
      break;
    case DT_PTR: 
      *((void **) element) = data;
      break;
    case DT_INT: 
      *((int *) element) = *((int *) data);
      break;
    case DT_FLOAT:
      *((float *)element) = *((float *) data);
      break;
    case DT_LONG: 
      *((long *)element) = *((long *) data);
      break;
    case DT_DOUBLE:
      *((double *)element) = *((double *) data);
      break;
    case DT_UNSIGNED_INT:
      *((unsigned int *)element) = *((unsigned int *) data);
      break;
    case DT_UNSIGNED_LONG:
      *((unsigned long *)element) = *((unsigned long *) data);
      break;
  }
}

int DynArr_init(struct DynArr *dynArr, unsigned long initialSize, enum DataType dataType){
  unsigned long dtypeSize = DataType_size(dataType);
  if (dtypeSize == 0) return -1;
  dynArr->dtype = dataType;

  dynArr->size = initialSize;
  dynArr->capacity = 2;
  for (unsigned long cap = 1; cap < initialSize * 2; cap *= 2) {
    dynArr->capacity = cap;
  }

  dynArr->arr = malloc(dtypeSize * dynArr->capacity);
  memset(dynArr->arr, 0, dtypeSize * dynArr->capacity);
  if(dynArr->arr == NULL) return -1;

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
  if(dynArr->capacity == 0) return -1;
  
  void *aux = malloc(DataType_size(dynArr->dtype) * cap);
  if (aux == NULL) return -2;

  void **auxArr = (void **)aux;

  for(unsigned int i=0; i<dynArr->size && i < cap; ++i) {
    auxArr[i] = ((void **)dynArr->arr)[i];
  }

  free(dynArr->arr);
  dynArr->arr = aux;
  dynArr->capacity = cap;
  return 0;
}



int DynArr_pushback(struct DynArr *dynArr, void *data){
  if(dynArr->capacity == 0) return -1;

  unsigned long idx = dynArr->size;
  if(dynArr->size + 1 == dynArr->capacity && DynArr_expand(dynArr, dynArr->capacity * 2) < 0) return -2;

  void *element = (char *)dynArr->arr + idx * DataType_size(dynArr->dtype);
  DataType_assign(dynArr->dtype, element, data);
  
  dynArr->size++;
  return 0;
}



int DynArr_insertAt(struct DynArr *dynArr, void *data, unsigned long idx) {
  if(dynArr->capacity == 0 || dynArr->size == 0) return -1;
  if(idx >= dynArr->size) return -2;

  void *element = (char *)dynArr->arr + idx * DataType_size(dynArr->dtype);
  DataType_assign(dynArr->dtype, element, data);
  
  return 0;
}

int DynArr_popback(struct DynArr *dynArr) {
  if(dynArr->capacity == 0 || dynArr->size == 0) return -1;

  unsigned long idx = dynArr->size - 1;
  void *element = (char *)dynArr->arr + idx * DataType_size(dynArr->dtype);

  switch (dynArr->dtype) {
    case DT_CHAR: 
      *((char *) element) = 0;
      break;
    case DT_PTR: 
      *((void **) element) = NULL;
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
  }
  dynArr->size--;

  if (dynArr->size < dynArr->capacity / 4 && DynArr_expand(dynArr, dynArr->capacity / 2) < 0 ) return -2;

  return 0;
}


const void *DynArr_dataAt(struct DynArr *dynArr, unsigned long idx) {
  if(dynArr->capacity == 0 || dynArr->size == 0) return NULL;
  if(idx > dynArr->size) return NULL;

  void *element = (char *)dynArr->arr + idx * DataType_size(dynArr->dtype);

  return element;
}


void DynArr_print(struct DynArr *dynArr) {
  if(dynArr->capacity == 0 || dynArr->size == 0) return;

  PrintFunc print_func = DataType_get_print_func(dynArr->dtype);
  if (!print_func) {
    printf("Unknown data type\n");
    return;
  }

  for(unsigned long i = 0; i<dynArr->size; ++i) {
    if (i != 0) printf(" ");
    void *element = (char *)dynArr->arr + i * DataType_size(dynArr->dtype);
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


  if (cmp_func == NULL) cmp_func = DataType_get_cmp_func(dynArr->dtype);

  mergeSort(dynArr->arr, begin, end, dynArr->dtype, cmp_func);
}
