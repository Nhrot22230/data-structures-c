#include "DataType.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

// Function prototypes for the test functions
void test_print_functions();
void test_cmp_functions();
void test_get_print_func();
void test_get_cmp_func();
void test_size();
void test_format();
void test_assign();

void DataType_test_all() {
  test_print_functions();
  test_cmp_functions();
  test_get_print_func();
  test_get_cmp_func();
  test_size();
  test_format();
  test_assign();

  printf("All tests passed successfully.\n");
}

int main(){
  DataType_test_all();
  return 0;
}

void test_print_functions() {
  char c = 'a';
  int i = 42;
  float f = 3.14;
  long l = 1234567890L;
  double d = 2.718281828;
  unsigned int ui = 100;
  unsigned long ul = 9876543210UL;

  printf("Testing print functions:\n");
  printf("Expected output: a\nActual output: ");
  print_char(&c);
  printf("\n");

  printf("Expected output: 42\nActual output: ");
  print_int(&i);
  printf("\n");

  printf("Expected output: 3.140000\nActual output: ");
  print_float(&f);
  printf("\n");

  printf("Expected output: 1234567890\nActual output: ");
  print_long(&l);
  printf("\n");

  printf("Expected output: 2.718282\nActual output: ");
  print_double(&d);
  printf("\n");

  printf("Expected output: 100\nActual output: ");
  print_unsigned_int(&ui);
  printf("\n");

  printf("Expected output: 9876543210\nActual output: ");
  print_unsigned_long(&ul);
  printf("\n");

  printf("Print functions tested successfully.\n");
}

void test_cmp_functions() {
  char c1 = 'a', c2 = 'b';
  int i1 = 1, i2 = 2;
  float f1 = 1.1, f2 = 1.2;
  long l1 = 1000, l2 = 2000;
  double d1 = 3.14, d2 = 2.71;
  unsigned int ui1 = 10, ui2 = 20;
  unsigned long ul1 = 100, ul2 = 200;

  assert(cmp_char(&c1, &c2) < 0);
  assert(cmp_int(&i1, &i2) < 0);
  assert(cmp_float(&f1, &f2) < 0);
  assert(cmp_long(&l1, &l2) < 0);
  assert(cmp_double(&d1, &d2) > 0);
  assert(cmp_unsigned_int(&ui1, &ui2) < 0);
  assert(cmp_unsigned_long(&ul1, &ul2) < 0);

  printf("Comparison functions tested successfully.\n");
}

void test_get_print_func() {
  assert(DataType_get_print_func(DT_CHAR) == print_char);
  assert(DataType_get_print_func(DT_INT) == print_int);
  assert(DataType_get_print_func(DT_FLOAT) == print_float);
  assert(DataType_get_print_func(DT_LONG) == print_long);
  assert(DataType_get_print_func(DT_DOUBLE) == print_double);
  assert(DataType_get_print_func(DT_UNSIGNED_INT) == print_unsigned_int);
  assert(DataType_get_print_func(DT_UNSIGNED_LONG) == print_unsigned_long);

  printf("DataType_get_print_func tested successfully.\n");
}

void test_get_cmp_func() {
  assert(DataType_get_cmp_func(DT_CHAR) == cmp_char);
  assert(DataType_get_cmp_func(DT_INT) == cmp_int);
  assert(DataType_get_cmp_func(DT_FLOAT) == cmp_float);
  assert(DataType_get_cmp_func(DT_LONG) == cmp_long);
  assert(DataType_get_cmp_func(DT_DOUBLE) == cmp_double);
  assert(DataType_get_cmp_func(DT_UNSIGNED_INT) == cmp_unsigned_int);
  assert(DataType_get_cmp_func(DT_UNSIGNED_LONG) == cmp_unsigned_long);

  printf("DataType_get_cmp_func tested successfully.\n");
}

void test_size() {
  assert(DataType_size(DT_CHAR) == sizeof(char));
  assert(DataType_size(DT_INT) == sizeof(int));
  assert(DataType_size(DT_FLOAT) == sizeof(float));
  assert(DataType_size(DT_LONG) == sizeof(long));
  assert(DataType_size(DT_DOUBLE) == sizeof(double));
  assert(DataType_size(DT_UNSIGNED_INT) == sizeof(unsigned int));
  assert(DataType_size(DT_UNSIGNED_LONG) == sizeof(unsigned long));

  printf("DataType_size tested successfully.\n");
}

void test_format() {
  char buffer[10];

  DataType_format(DT_CHAR, buffer);
  assert(strcmp(buffer, "%c") == 0);

  DataType_format(DT_CUSTOM, buffer);
  assert(strcmp(buffer, "%p") == 0);

  DataType_format(DT_INT, buffer);
  assert(strcmp(buffer, "%d") == 0);

  DataType_format(DT_FLOAT, buffer);
  assert(strcmp(buffer, "%f") == 0);

  DataType_format(DT_LONG, buffer);
  assert(strcmp(buffer, "%ld") == 0);

  DataType_format(DT_DOUBLE, buffer);
  assert(strcmp(buffer, "%lf") == 0);

  DataType_format(DT_UNSIGNED_INT, buffer);
  assert(strcmp(buffer, "%u") == 0);

  DataType_format(DT_UNSIGNED_LONG, buffer);
  assert(strcmp(buffer, "%lu") == 0);

  printf("DataType_format tested successfully.\n");
}

void test_assign() {
  char c1 = 'a', c2;
  int i1 = 42, i2;
  float f1 = 3.14, f2;
  long l1 = 1234567890L, l2;
  double d1 = 2.718281828, d2;
  unsigned int ui1 = 100, ui2;
  unsigned long ul1 = 9876543210UL, ul2;

  DataType_assign(DT_CHAR, &c2, &c1);
  assert(c2 == c1);

  DataType_assign(DT_INT, &i2, &i1);
  assert(i2 == i1);

  DataType_assign(DT_FLOAT, &f2, &f1);
  assert(f2 == f1);

  DataType_assign(DT_LONG, &l2, &l1);
  assert(l2 == l1);

  DataType_assign(DT_DOUBLE, &d2, &d1);
  assert(d2 == d1);

  DataType_assign(DT_UNSIGNED_INT, &ui2, &ui1);
  assert(ui2 == ui1);

  DataType_assign(DT_UNSIGNED_LONG, &ul2, &ul1);
  assert(ul2 == ul1);

  printf("DataType_assign tested successfully.\n");
}

