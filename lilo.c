#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

typedef struct NODE node;

struct NODE {
  int data;
  node* next;
};

typedef struct {
  unsigned int length;
  node* start;
  node* end;
} linked_list;

node* ll_add_node(linked_list*, node*);
void ll_add(linked_list*, int);
int ll_remove_first(linked_list*);
void ll_free(linked_list*);
void ll_free_nodes_after_including(node*);
int ll_get(linked_list* this, int index);
int main() {
  linked_list* list = malloc(sizeof(linked_list));

  if (!list) {
    abort();
  }

  list->start = NULL;
  list->end = NULL;
  list->length = 0;

  for (int i = 0; i < 10; i++) {
    ll_add(list, i);
  }

  printf("at i=0: %d\n", ll_get(list, 0));
  printf("at i=2: %d\n", ll_get(list, 2));
  printf("at i=9: %d\n", ll_get(list, 9));
  printf("list length: %d\n", list->length);

  printf("removed first value: %d\n", ll_remove_first(list));
  printf("removed first value: %d\n", ll_remove_first(list));

  printf("at i=0: %d\n", ll_get(list, 0));
  printf("at i=2: %d\n", ll_get(list, 2));
  printf("at i=9: %d\n", ll_get(list, 9));
  printf("list length: %d\n", list->length);

  ll_free(list);
}

void ll_free_nodes_after_including(node* node_to_free) {
  if (node_to_free->next) {
    ll_free_nodes_after_including(node_to_free->next);
  }
  free(node_to_free);
}

void ll_free(linked_list* this) {
  ll_free_nodes_after_including(this->start);
  free(this);
}

void ll_add(linked_list* this, int value) {
  node* node_to_add = malloc(sizeof(node));
  if (!node_to_add) {
    abort();
  }
  node_to_add->next = NULL;
  node_to_add->data = value;
  ll_add_node(this, node_to_add);
}

node* ll_add_node(linked_list* this, node* node_to_add) {
  if (this->length == 0) {
    this->start = node_to_add;
    this->end = node_to_add;
  } else {
    this->end->next = node_to_add;
    this->end = node_to_add;
  }
  this->length++;
  return node_to_add;
}

int ll_remove_first(linked_list* this) {
  int value = 0;
  if (this->length > 0) {
    node* start = this->start;
    value = start->data;
    this->start = this->start->next;
    free(start);
    this->length--;
  }
  return value;
}

int ll_get(linked_list* this, int index) {
  node* node_to_get = this->start;
  for (int i = 0; i < index; i++) {
    if (node_to_get->next) {
      node_to_get = node_to_get->next;
    } else {
      break;
    }
  }
  if (node_to_get) {
    return node_to_get->data;
  } else {
    return 0;
  }
}