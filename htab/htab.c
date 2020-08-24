#include <err.h>
#include <string.h>

#include "htab.h"

uint32_t hash(char *key)
{
    size_t i = 0;
    uint32_t hash = 0;
    while (key[i]!='\0') {
      hash += key[i++];
      hash += hash<<10;
      hash^=hash>>6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

struct htab *htab_new()
{
    struct htab * tab = malloc(sizeof(struct htab));
    if (tab == NULL)
    {
        errx(1,"Not enough memory !");
    }
    tab->capacity = 4;
    tab->size = 0;
    struct pair * p = malloc(4*sizeof(struct pair));
    if (p == NULL)
    {
        errx(1,"Not enough memory !");
    }
    for (size_t i = 0; i < 4; i++) {
      struct pair elm = {0,NULL,NULL,NULL};
      p[i] = elm;
    }
    tab->data = p;
    return tab;
}

#include <stdio.h>
void htab_clear(struct htab *ht)
{
    for (size_t i = 0; i < ht->capacity; i++) {
      struct pair *tmp = ht->data[i].next;
      if(tmp)
      while(tmp && tmp->next){
        if(tmp->next && tmp->next->next==NULL)
        {
          free(tmp->next);
          tmp->next=NULL;
          tmp=ht->data[i].next;
        }
        else
          tmp=tmp->next;
      }
      free(ht->data[i].next);
      ht->data[i].next=NULL;
    }
    ht->size = 0;
}

void htab_free(struct htab *ht)
{
    htab_clear(ht);
    free(ht->data);
    free(ht);
}

struct pair *htab_get(struct htab *ht, char *key)
{
    int index = hash(key)%ht->capacity;
    struct pair * pairs = ht->data[index].next;
    while(pairs!= NULL){
      if(pairs->key == key){
        return pairs;
      }
      pairs = pairs->next;
    }
    return NULL;
}

void htab_normal_insert(struct htab *ht, char *key, void *value, int index){
  struct pair * tmp = ht->data[index].next;
  if(tmp == NULL)
    ht->size+=1;
  struct pair * toAdd = malloc(sizeof(struct pair));
  toAdd->hkey = hash(key);
  toAdd->key = key;
  toAdd->value = value;
  toAdd->next = NULL;
  ht->data[index].next = toAdd;
  toAdd->next = tmp;
}

void helper(struct htab *ht, char *key, void *value){
  struct htab * newH = htab_new();
  newH->capacity = ht->capacity * 2;
  newH->data = realloc(newH->data, newH->capacity*sizeof(struct pair));
  for (size_t i = 0; i < newH->capacity; i++) {
    newH->data[i].next = NULL;
  }
  for (size_t i = 0; i < ht->capacity; i++){
    struct pair * pairs = ht->data[i].next;
    while(pairs!= NULL){
      htab_normal_insert(newH,pairs->key,pairs->value,pairs->hkey%newH->capacity);
      pairs = pairs->next;
    }
  }
  htab_normal_insert(newH,key,value,hash(key)%newH->capacity);

  htab_clear(ht);
  free(ht->data);
  *ht=*newH;
  free(newH);
}
int htab_insert(struct htab *ht, char *key, void *value)
{
    if(htab_get(ht,key)!=NULL)
      return 0;
    int index = hash(key)%ht->capacity;
    if((ht->data[index].next != NULL && 100*ht->size/ht->capacity>=75) || 100*ht->size/ht->capacity<75)
        htab_normal_insert(ht,key,value,index);
    else{
      helper(ht,key,value);
      while(100*ht->size/ht->capacity>75){
        helper(ht,key,value);
      }
    }
    return 1;
}

void htab_remove(struct htab *ht, char *key)
{
  int index = hash(key)%ht->capacity;
  struct pair * tmp = &ht->data[index];
  while(tmp && tmp->next){
    if(tmp->next->key == key){
      struct pair * tmp2 = tmp->next;
      tmp->next = tmp->next->next;
      free(tmp2);
    }
    tmp = tmp->next;
  }
}
