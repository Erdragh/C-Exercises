#include <stdlib.h>
#include <stdio.h>

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

  list->length = 0;

  for (int i = 0; i < 10; i++) {
    ll_add(list, i);
  }

  printf("at i=0: %d\n", ll_get(list, 0));
  printf("at i=2: %d\n", ll_get(list, 2));
  printf("list length: %d\n", list->length);

  printf("removed first value: %d\n", ll_remove_first(list));
  printf("removed first value: %d\n", ll_remove_first(list));

  printf("at i=0: %d\n", ll_get(list, 0));
  printf("at i=2: %d\n", ll_get(list, 2));
  printf("list length: %d\n", list->length);

  ll_free(list);
}

void ll_free_nodes_after_including(node* node) {
  if (node->next) {
    ll_free_nodes_after_including(node->next);
  }
  free(node);
}

void ll_free(linked_list* this) {
  ll_free_nodes_after_including(this->start);
  free(this);
}

void ll_add(linked_list* this, int value) {
  node* node = malloc(sizeof(node));
  if (!node) {
    abort();
  }
  node->data = value;
  ll_add_node(this, node);
}

node* ll_add_node(linked_list* this, node* node) {
  if (this->length == 0) {
    this->start = node;
    this->end = node;
  } else {
    this->end->next = node;
    this->end = node;
  }
  this->length++;
  return node;
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
  node* node = this->start;
  for (int i = 0; i < index; i++) {
    if (node->next) {
      node = node->next;
    } else {
      break;
    }
  }
  if (node) {
    return node->data;
  } else {
    return 0;
  }
}