#include "queue.h"
#include <stdio.h>

int main(void) {
    sll_queue *queue = queue_init();
    enqueue(queue, 10);
    enqueue(queue, 20);

    printf("Queue size: %d\n", queue_size(queue));
    printf("Queue:\n");
    queue_print(queue);

    sll_queue *queue2 = queue_init();
    printf("Duplication....\n");
    queue_duplicate(queue, queue2);
    printf("Queue 2:\n");
    queue_print(queue2);
    
    int val;
    dequeue(queue, &val);
    printf("Dequeued: %d\n", val);

    printf("Queue size: %d\n", queue_size(queue));
    queue_print(queue);

    queue_clear(queue);
    printf("Queue size: %d\n", queue_size(queue));
    queue_print(queue);
    
    queue_free(&queue);
    queue_free(&queue2);
    
    return 0;
}
