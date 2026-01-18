#ifndef QUEUE_H
#define QUEUE_H

#include "../singly_linked_list/sll.h"
#include <stdbool.h>

typedef struct {
    SLL_list *list;
} sll_queue;

/* PROTOTYPES FUNCTIONS */

sll_queue *queue_init();

// Insert
int enqueue(sll_queue *queue, int data);

// Delete
int dequeue(sll_queue *queue, int *output);

// Get
int front(sll_queue *queue, int *output);

// Utility
void queue_print(sll_queue *queue);
int queue_size(sll_queue *queue);
int queue_free(sll_queue **queue_ref);
bool queue_is_empty(sll_queue *queue);
int queue_clear(sll_queue *queue);
int queue_duplicate(sll_queue *old_queue, sll_queue *new_queue);

#endif
