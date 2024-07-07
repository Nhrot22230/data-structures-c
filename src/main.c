#include "data_structures.h"
#include <stdio.h>

int main(){
  struct DynArr int_arr;
  DynArr_init(&int_arr, 0, DT_INT);

  int arr[2] = {0,0};

  for(unsigned long i=0; i<10; ++i){
    arr[0] = i;
    DynArr_pushback(&int_arr, &arr[0]);
    //if(i%3==0) DynArr_popback(&int_arr);
  }

  DynArr_print(&int_arr);
  DynArr_sort(&int_arr, 0, int_arr.size - 1, NULL);
  DynArr_print(&int_arr);
  printf("Cap : %ld\n", int_arr.capacity);
  printf("Size: %ld\n", int_arr.size);
  printf("5th: %ld\n", *((long *) DynArr_dataAt(&int_arr, 5)));
  return 0;
}
