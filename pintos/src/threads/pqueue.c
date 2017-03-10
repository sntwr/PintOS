#include "threads/pqueue.h"

/* Allocates space for heap types's data and initializes it
 * Caller must ensure/check that:
 * h is not NULL
 * h->heap is a valid memory address (i.e. NOT NULL) after the call
 */
heap64_t * 
heap64_init (heap64_t *h, int max_nelem)
{
  ASSERT( h != NULL);
  h->heap = malloc (max_nelem * sizeof(heap64_elem_t) );
  h->max_nelem = max_nelem;
  h->n_elem = 0;

  return h;
}

/* Returns true if heap has no elements 
 * Caller must ensure that:
 * h is not NULL
 */
bool
heap64_is_empty (heap64_t *h)
{
  ASSERT (h != NULL);
  return (h->n_elem <= 0);
}

/* Returns true if heap is full
 * Caller must ensure that:
 * h is not NULL
 */
bool
heap64_is_full (heap64_t *h)
{
  ASSERT (h != NULL);
  return (h->n_elem >= h->max_nelem);
}

/* Min heapifies the heap in h->heap from index ind (1 based)
 * Caller must ensure that
 * h is not NULL
 */
void
heap64_minpq_heapify (heap64_t *h, int ind)
{
  ASSERT (h != NULL);
  
  int smallest;
  while (1) {
    int l = HEAP_LCHILD(ind);
    int r = HEAP_RCHILD(ind);

    if (l <= h->n_elem && h->heap[l].key < h->heap[ind].key)
      smallest = l;
    else
      smallest = ind;

    if (r <= h->n_elem && h->heap[r].key < h->heap[smallest].key)
      smallest = r;
    
    if (smallest == ind) 
      break;
    else {
      heap64_elem_t temp = h->heap[ind];
      h->heap[ind] = h->heap[smallest];
      h->heap[smallest] = temp;

      ind = smallest;
    }
  }
}


void
heap64_maxpq_heapify (heap64_t *h, int ind)
{
  ASSERT (h != NULL);
  
  int largest;
  while (1) {
    int l = HEAP_LCHILD(ind);
    int r = HEAP_RCHILD(ind);

    if (l <= h->n_elem && h->heap[l].key > h->heap[ind].key)
      largest = l;
    else
      largest = ind;

    if (r <= h->n_elem && h->heap[r].key > h->heap[largest].key)
      largest = r;

    if (largest == ind)
      break;
    else {
      heap64_elem_t temp = h->heap[ind];
      h->heap[ind] = h->heap[largest];
      h->heap[largest] = temp;

      ind = largest;
    }
  }
}


/* Returns pointer to top element in heap
 * Caller must ensure/check that:
 * h is not NULL
 * heap has at least one element
 * Caller must cast the returned void * to their expected type
 */
void *
heap64_peek (heap64_t *h)
{
  ASSERT (h != NULL);
  return h->heap + 1;
}

/* Inserts into min heap
 * Caller must ensure that
 * h is not NULL
 * heap has at least one element
 * Caller must pass pointer to the element they are inserting
 */
void
heap64_minpq_insert (heap64_t *h, void* elem)
{
  ASSERT (h != NULL);
  ASSERT (elem != NULL);

  int i, p;
  
  i = ++(h->n_elem);
  h->heap[i] = *((heap64_elem_t *)elem);

  while (i > 1 && h->heap[p = HEAP_PARENT(i)].key > h->heap[i].key) {
    heap64_elem_t temp = h->heap[p];
    h->heap[p]= h->heap[i];
    h->heap[i] = temp;  

    i = p;
  }
}

void
heap64_maxpq_insert (heap64_t *h, void *elem)
{
  ASSERT (h != NULL);

  int i, p;
  
  i = ++(h->n_elem);
  h->heap[i] = *((heap64_elem_t *)elem);

  while (i > 1 && h->heap[p = HEAP_PARENT(i)].key < h->heap[i].key) {
    heap64_elem_t temp = h->heap[p];
    h->heap[p]= h->heap[i];
    h->heap[i] = temp;  

    i = p;
  }
}

void
heap64_minpq_pop (heap64_t *h)
{
  ASSERT (h != NULL);
  
  h->heap[1] = h->heap[h->n_elem--];
  heap64_minpq_heapify(h, 1);
}

void
heap64_maxpq_pop (heap64_t *h)
{
  ASSERT (h != NULL);
  
  h->heap[1] = h->heap[h->n_elem--];
  heap64_maxpq_heapify(h, 1);
}

void
pr_heap (heap64_t *h, void (*pr_data)(void *))
{
  ASSERT (h != NULL);
  int i;
  for (i = 1; i <= h->n_elem; i++) {
    printf ("(%d)[ key = %"PRId64" ; { ", i, h->heap[i].key);
    pr_data (h->heap[i].data);
    printf (" } ]\n");
  }
}

