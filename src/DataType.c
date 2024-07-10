#include "DataType.h"
#include <stdlib.h>
#include <stdio.h>
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

int cmp_char(void *i_ptr, void *j_ptr) {
  char a = *(char *)i_ptr;
  char b = *(char *)j_ptr;
  
  if (a < b) return -1;
  if (a > b) return 1;
  return 0;
}

int cmp_int(void *i_ptr, void *j_ptr) {
  int a = *(int *)i_ptr;
  int b = *(int *)j_ptr;

  if (a < b) return -1;
  if (a > b) return 1;
  return 0;
}
 
int cmp_float(void *i_ptr, void *j_ptr) {
  float a = *(float *)i_ptr;
  float b = *(float *)j_ptr;

  if (a < b) return -1;
  if (a > b) return 1;
  return 0;
}

int cmp_long(void *i_ptr, void *j_ptr) {
  long a = *(long *)i_ptr;
  long b = *(long *)j_ptr;

  if (a < b) return -1;
  if (a > b) return 1;
  return 0;
}

int cmp_double(void *i_ptr, void *j_ptr) {
  double a = *(double *)i_ptr;
  double b = *(double *)j_ptr;

  if (a < b) return -1;
  if (a > b) return 1;
  return 0;
}

int cmp_unsigned_int(void *i_ptr, void *j_ptr) {
  unsigned int a = *(unsigned int *)i_ptr;
  unsigned int b = *(unsigned int *)j_ptr;

  if (a < b) return -1;
  if (a > b) return 1;
  return 0;
}

int cmp_unsigned_long(void *i_ptr, void *j_ptr) {
  unsigned long a = *(unsigned long *)i_ptr;
  unsigned long b = *(unsigned long *)j_ptr;

  if (a < b) return -1;
  if (a > b) return 1;
  return 0;
}


PrintFunc DataType_get_print_func(enum DataType dtype) {
  switch (dtype) {
    case DT_CHAR: return print_char;
    case DT_INT: return print_int;
    case DT_FLOAT: return print_float;
    case DT_LONG: return print_long;
    case DT_DOUBLE: return print_double;
    case DT_UNSIGNED_INT: return print_unsigned_int;
    case DT_UNSIGNED_LONG: return print_unsigned_long;
    default: return NULL;
  }
  return NULL;
}

CmpFunc DataType_get_cmp_func(enum DataType dtype) {
  switch (dtype) {
    case DT_CHAR: return cmp_char;
    case DT_INT: return cmp_int;
    case DT_FLOAT: return cmp_float;
    case DT_LONG: return cmp_long;
    case DT_DOUBLE: return cmp_double;
    case DT_UNSIGNED_INT: return cmp_unsigned_int;
    case DT_UNSIGNED_LONG: return cmp_unsigned_long;
    default: return NULL;
  }
  return NULL;
}

unsigned long DataType_size(enum DataType dtype) {
  switch (dtype) {
    case DT_CHAR: return 1;
    case DT_INT: return 4;
    case DT_FLOAT: return 4;
    case DT_LONG: return 8;
    case DT_DOUBLE: return 8;
    case DT_UNSIGNED_INT: return 4;
    case DT_UNSIGNED_LONG: return 8;
    default: return 0;
  }
  return 0;
}

void DataType_format(enum DataType dtype, char *buffer) {
  switch (dtype) {
    case DT_CHAR: 
      strcpy(buffer, "%c");
      break;
    case DT_CUSTOM: 
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
    case DT_CUSTOM:
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
