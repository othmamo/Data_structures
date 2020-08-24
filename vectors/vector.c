#include <err.h>
#include "vector.h"

struct vector *vector_new()
{
    struct vector * v = malloc(sizeof(struct vector));
    int * data = malloc(sizeof(int));
    v->capacity = 1;
    v->size = 0;
    v->data = data;
    return v;
}

void vector_free(struct vector *v)
{
    free(v->data);
    free(v);
}

void double_capacity(struct vector *v)
{
    v->capacity *=2;
    v->data = realloc(v->data, v->capacity * sizeof(int));
}

void vector_push(struct vector *v, int x)
{
    if(v->size+1>v->capacity){
      double_capacity(v);
    }
    v->data[v->size] = x;
    v->size += 1;
}

int vector_pop(struct vector *v, int *x)
{
    if(v->size == 0)
      return 0;
    *(x) = *(v->data + v->size-1);
    v->size -=1;
    return 1;
}

int vector_get(struct vector *v, size_t i, int *x)
{
    if(i>=v->size)
      return 0;
    *x = *(v->data+i);
    return 1;
}

void vector_insert(struct vector *v, size_t i, int x)
{
    if(i<v->size+1){
      if(v->size+1>v->capacity){
        double_capacity(v);
      }
      int tmp = x;
      int tmp2 = x;
      v->size += 1;
      for (; i < v->size; i++) {
        tmp2 = *(v->data+i);
        *(v->data+i) = tmp;
        tmp = tmp2;
      }
    }
}

int vector_remove(struct vector *v, size_t i, int *x)
{
    if(i>=v->size){
      return 0;
    }
    *x = *(v->data + i);
    for (; i < v->size-1; i++) {
      int tmp = *(v->data+i);
      *(v->data+i) = *(v->data+i+1);
      *(v->data+i+1)=tmp;
    }
    v->size-=1;
    return 1;
}
