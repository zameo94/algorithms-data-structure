#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* INITIALIZATION */

sll_queue *queue_init() {
    sll_queue *queue = malloc(sizeof(*queue));

    if(queue == NULL) {
        return NULL;
    }

    SLL_list *list = initialize_list();

    if(list == NULL) {
        free(queue);
        return NULL;
    }

    queue->list = list;
    return queue;
}

/* INSERT FUNCTIONS */

int enqueue(sll_queue *queue, int data) {
    if(queue == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED; 

    return insert_tail(queue->list, data);
}

/* DELETE FUNCTIONS */

int dequeue(sll_queue *queue, int *output) {
    if(queue == NULL || queue->list == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;

    int status = get_head(queue->list, output);
    
    if(status != SLL_SUCCESS) return status;

    return delete_head(queue->list);
}

/* GET */

int front(sll_queue *queue, int *output) {
    if(queue == NULL || queue->list == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;

    return get_head(queue->list, output);
}

/* PRINTING */

void queue_print(sll_queue *queue) {
    if(queue == NULL) return;

    print_list(queue->list);
}

/* SIZE */

int queue_size(sll_queue *queue) {
    if(queue == NULL || queue->list == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;

    return queue->list->length;
}

/* BOOLEAN CHECKS */

/* 
 * Check if the queue is empty.
 * The pointer 'queue' MUST be allocated. Passing NULL is considered 
 * a logic error and will trigger an assertion failure.
 */
bool queue_is_empty(sll_queue *queue) {
    assert(queue != NULL);

    return is_empty(queue->list);
}

/* CLEANING FUNCTIONS */

int queue_free(sll_queue **queue_ref) {
    if(queue_ref == NULL || *queue_ref == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;

    int result = free_list(&((*queue_ref)->list));

    if(result != SLL_SUCCESS) return result;

    free(*queue_ref);
    *queue_ref = NULL;

    return SLL_SUCCESS;
}

/* CLEAR */

int queue_clear(sll_queue *queue) {
    if(queue == NULL || queue->list == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;

    return clear_list(queue->list);
}

/* DUPLICATE */

int queue_duplicate(sll_queue *old_queue, sll_queue *new_queue) {
    if(old_queue == NULL || old_queue->list == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;
    if(new_queue == NULL || new_queue->list == NULL) return SLL_ERROR_LIST_NOT_ALLOCATED;

    return duplicate_list(old_queue->list, new_queue->list);
}
