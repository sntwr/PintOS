#ifndef PQUEUE_H_INCLUDED
#define PQUEUE_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "threads/malloc.h"

typedef struct heap64_elem_t
{
  void *data;
  int64_t key;
} heap64_elem_t;

typedef struct heap64_t
{
  heap64_elem_t *heap;
  int n_elem;
  int max_nelem;
} heap64_t;


extern heap64_t * 
heap64_init (heap64_t *h, int max_nelem);

extern bool
heap64_is_empty (heap64_t *h);

extern bool
heap64_is_full (heap64_t *h);

#define HEAP_PARENT(i) ((i)>>1)
#define HEAP_LCHILD(i) ((i)<<1)
#define HEAP_RCHILD(i) (((i)<<1)+1)

extern void 
heap64_minpq_heapify (heap64_t *h, int ind);

extern void
heap64_maxpq_heapify (heap64_t *h, int ind);

extern void *
heap64_peek (heap64_t *h);

extern void
heap64_minpq_insert (heap64_t *h, void* elem);

extern void
heap64_maxpq_insert (heap64_t *h, void *elem);

extern void
heap64_minpq_pop (heap64_t *h);

extern void
heap64_maxpq_pop (heap64_t *h);

extern void
pr_heap (heap64_t *h, void (*pr_data)(void *));

#endif
