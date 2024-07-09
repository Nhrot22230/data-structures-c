#ifndef DATATYPE_H
#define DATATYPE_H

enum DataType {
  DT_CUSTOM = 1,
  DT_CHAR,
  DT_INT,
  DT_FLOAT,
  DT_LONG,
  DT_DOUBLE,
  DT_UNSIGNED_INT,
  DT_UNSIGNED_LONG
};

typedef void (*PrintFunc)(void *);
typedef int (*CmpFunc)(void *, void *);
typedef int (*CustomFunc)(void *);
typedef void (*AssignFunc)(void *, void *);

PrintFunc DataType_get_print_func(enum DataType dtype);
CmpFunc DataType_get_cmp_func(enum DataType dtype);
unsigned long DataType_size(enum DataType dtype);
void DataType_assign(enum DataType dtype, void *element, void *data);
void DataType_format(enum DataType dtype, char *buffer);


#endif //DATATYPE_H