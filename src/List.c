#include "List.h"
#include <stdlib.h>
#include <stdio.h>

void List_init(struct List *list, enum DataType dtype){
  list->len = 0;
  list->head = NULL;
  list->tail = NULL;
  list->dtype = dtype;
}

void List_insert(struct List *list, void *data, unsigned long idx) {
  struct Node *node = Node_create();
  Node_init(node, data, list->dtype);
  if (node == NULL) return;
  if (list->head == NULL) {
    list->head = node;
    list->tail = list->head;
  }
  else if (idx == 0) {
    node->next = list->head;
    list->head = node;
  }
  else if (idx >= list->len) {
    list->tail->next = node;
    list->tail = node;
  }
  else {
    struct Node *prev = NULL;
    struct Node *curr = list->head;

    for (unsigned long i = 0; i < idx; ++i) {
      prev = curr;
      curr = curr->next;
    }

    prev->next = node;
    node->next = curr;
  }
  list->len++;
}

void List_erase(struct List *list, unsigned long idx) {
  if (list->head == NULL) return;
  if (list->len == 0) return;
  struct Node *aux = NULL;
  if (idx == 0) {
    struct Node *aux = list->head;
    list->head = list->head->next;
    if (aux == list->tail) list->tail = NULL;
  }
  else {
    struct Node *prev = NULL;
    struct Node *curr = list->head;
    for(unsigned long i = 0; i < idx; ++i) {
      if (i == idx){
        prev->next = curr->next;
        if(curr == list->tail) list->tail = prev;
        break;
      }
      aux = curr;
      prev = curr;
      curr = curr->next;
    }
  }

  
  if (aux == NULL) return;
  Node_free(aux, 0);
  free(aux);
}


void List_print(struct List *list) {
  PrintFunc print = DataType_get_print_func(list->dtype);
  struct Node *cur = list->head;
  while(cur != NULL) {
    print(cur->elem);
    printf(" -> ");
    cur = cur->next;
  }
  printf("NULL\n");
}


void List_free(struct List *list){
  if (list->head != NULL) {
    Node_free(list->head, 1);
    free(list->head);
    list->head = NULL;
  }
  list->len = 0;
}
