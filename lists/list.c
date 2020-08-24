#include "list.h"

void list_init(struct list *list)
{
  list->next=NULL;
  list->data=-1;
}

int list_is_empty(struct list *list)
{
    return (list->next == NULL);
}

size_t list_len(struct list *list)
{
    size_t len;
    for (len=0; list; list = list->next)
      len += 1;
    return len-1;
}

void list_push_front(struct list *list, struct list *elm)
{
    struct list * tmp = list->next;
    list->next = elm;
    elm->next = tmp;
}

struct list *list_pop_front(struct list *list)
{
    if(list_is_empty(list)==1)
        return NULL;
    struct list* res = list->next;
    list->next = res->next;
    res ->next = NULL;
    return res;
}

struct list *list_find(struct list *list, int value)
{
    while(list){
      if(list->data == value)
        return list;
      list = list->next;
    }
    return NULL;
}

int list_is_sorted(struct list *list)
{
  while(list->next){
    if(list->next->data <list->data ){
      return 0;
    }
    list = list->next;
  }
  return 1;
}

void list_insert(struct list *list, struct list *elm)
{
  while(list->next){
    if(list->next->data>=elm->data){
      break;
    }
    list = list->next;
  }
  if(list_is_empty(list))
    list->next=elm;
  else{
    elm->next= list->next;
    list->next= elm;
  }
}

void list_rev(struct list *list)
{
    struct list res;
    list_init(&res);
    while(!list_is_empty(list)){
        list_push_front(&res,list_pop_front(list));
    }
    list->next = (&res)->next;
}

void list_half_split(struct list *list, struct list *second)
{
    int len = list_len(list);
    for (int i = 0; i < len/2; i++) {
      list = list->next;
    }
    second->next=list->next;
    list->next=NULL;
}
