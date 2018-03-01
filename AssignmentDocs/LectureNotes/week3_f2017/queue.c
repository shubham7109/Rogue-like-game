#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int queue_init(queue_t *q)
{
  q->size = 0;
  q->head = q->tail = NULL;

  return 0;
}

int queue_delete(queue_t *q)
{
  int i;

  while (!queue_remove(q, &i))
    ;

  return 0;
}

int queue_add(queue_t *q, int v)
{
  if (q->head) { /* q is not empty */
    if (!(q->tail->next = malloc(sizeof (*q->tail->next)))) {
      fprintf(stderr, "Out of memory.\n");

      return 1;
    }
    q->tail = q->tail->next;
    q->tail->value = v;
    q->tail->next = NULL;
    q->size++;

    return 0;
  } else {
    if (!(q->tail = q->head = malloc(sizeof (*q->tail)))) {
      fprintf(stderr, "Out of memory.\n");

      return 1;
    }
    q->tail->value = v;
    q->tail->next = NULL;
    q->size++;

    return 0;
  }

  return 0; /* Won't be reached */
}

int queue_remove(queue_t *q, int *v)
{
  queue_node_t *n;

  if (!q->size) {
    return 1;
  }

  n = q->head;

  q->head = q->head->next;
  q->size--;
  *v = n->value;
  free(n);

  if (!q->size) {
    q->tail = NULL;
  }

  return 0;
}

int queue_peek(queue_t *q, int *v)
{
  if (q->size) {
    *v = q->head->value;

    return 0;
  }

  return 1;
}

int queue_size(queue_t *q)
{
  return q->size;
}

