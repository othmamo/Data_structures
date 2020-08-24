#ifndef _LIST_H_
#define _LIST_H_
#include <stdlib.h>

struct list
{
  struct list *next;
  int data;
};

void list_init(struct list *list);

int list_is_empty(struct list *list);

size_t list_len(struct list *list);

void list_push_front(struct list *list, struct list *elm);

struct list *list_pop_front(struct list *list);

// Return the first element of the list that have (value) as the value
struct list *list_find(struct list *list, int value);


int list_is_sorted(struct list *list);

// Insert elm in a sorted list keeping it sorted
void list_insert(struct list *list, struct list *elm);

// Reverse the elements of the list
void list_rev(struct list *list);

// Split the list in half
void list_half_split(struct list *list, struct list *second);

#endif
