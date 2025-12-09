#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ERROR STATUS CONSTANTS */

// Success code
#define SLL_SUCCESS 0

// Allocation/Setup Errors code
#define SLL_ERROR_MEMORY_ALLOCATION -10
#define SLL_ERROR_LIST_NOT_ALLOCATED -11

// List status Error
#define SLL_ERROR_EMPTY -20

// Input Errora
#define SLL_ERROR_INVALID_POSITION -30
#define SLL_ERROR_INVALID_ARGUMENT -31

struct node {
    int data;
    struct node *next;
};

typedef struct {
    struct node *head;
    struct node *tail;
    int length;
} SLL_list;

/* PROTOTYPES FUNCTIONS */

// Initialization
SLL_list *initialize_list();

// Insert
int insert_head(SLL_list *list, int data);
int insert_at(SLL_list *list, int data, int position); 
int insert_tail(SLL_list *list, int data);

// Delete
int delete_head(SLL_list *list);
int delete_at(SLL_list *list, int position);
int delete_tail(SLL_list *list);

// Get/Query
bool is_empty(SLL_list *list);
int get_head(SLL_list *list, int *output);
int get_at(SLL_list *list, int position, int *output);
int get_tail(SLL_list *list, int *output);

// Utility
void print_list(SLL_list *list);
int free_list(SLL_list **list_ref);

/* INITIALIZATION */

SLL_list *initialize_list() {
    SLL_list *list = malloc(sizeof(*list)); 

    if(list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    return list;
}

/* INSERT FUNCTIONS */

int insert_head(SLL_list *list, int data) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }
    
    struct node *new_node = malloc(sizeof(*new_node));

    if(new_node == NULL) {
        return SLL_ERROR_MEMORY_ALLOCATION;
    }

    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;

    if(list->tail == NULL){
        list->tail = new_node;
    }

    list->length++;

    return SLL_SUCCESS;
}

int insert_at(SLL_list *list,int data, int position) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    if(position < 0) {
        return SLL_ERROR_INVALID_POSITION;
    }

    if(position > list->length) {
        return SLL_ERROR_INVALID_POSITION;
    }

    if(position == 0) {
        return insert_head(list, data);
    }

    if(position == list->length) {
        return insert_tail(list, data);
    }

    struct node *tmp_node = list->head;

    for(int i = 0; i < (position - 1); i++) {
        tmp_node = tmp_node->next;
    }

    struct node *node_to_insert = malloc(sizeof(*node_to_insert));

    if(node_to_insert == NULL) {
        return SLL_ERROR_MEMORY_ALLOCATION;
    }

    node_to_insert->data = data;
    node_to_insert->next = tmp_node->next;
    tmp_node->next = node_to_insert;

    list->length++;

    return SLL_SUCCESS;
}

int insert_tail(SLL_list *list, int data) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    struct node *new_node = malloc(sizeof(*new_node));

    if(new_node == NULL) {
        return SLL_ERROR_MEMORY_ALLOCATION;
    }

    new_node->data = data;
    new_node->next = NULL;

    if(list->head == NULL){
        list->head = new_node;
    } else {
        list->tail->next = new_node;
    }

    list->tail = new_node;
    list->length++;

    return SLL_SUCCESS;
}

/* DELETE FUNCTIONS */

int delete_head(SLL_list *list) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    if(list->head == NULL) {
        return SLL_ERROR_EMPTY;
    }

    struct node *original_head = list->head;
    list->head = list->head->next;

    if(list->tail == original_head) {
        list->tail = NULL;
    }

    free(original_head);
    list->length--;

    return SLL_SUCCESS;
}

int delete_at(SLL_list *list, int position) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    if(position < 0) {
        return SLL_ERROR_INVALID_POSITION;
    }

    struct node *tmp_node = list->head;

    if(position == 0) {
        return delete_head(list);
    }

    for(int i = 0; tmp_node != NULL && i < (position - 1); i++) {
        tmp_node = tmp_node->next;
    }

    if(tmp_node == NULL || tmp_node->next == NULL) {
        return SLL_ERROR_INVALID_POSITION;
    }

    struct node *node_to_del = tmp_node->next;
    tmp_node->next = node_to_del->next;

    if(list->tail == node_to_del) {
        list->tail = tmp_node;
    }

    free(node_to_del);
    list->length--;

    return SLL_SUCCESS;
}

int delete_tail(SLL_list *list) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    if(list->tail == NULL) {
        return SLL_ERROR_EMPTY;
    }

    struct node *current = list->head;
    struct node *tail = list->tail;

    if(current == tail) {
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
        free(tail);

        return SLL_SUCCESS;
    }

    while(current->next != tail) {
        current = current->next;
    }

    current->next = NULL;
    list->tail = current;
    list->length--;
    free(tail);

    return SLL_SUCCESS; 
}

/* PRINTING */

void print_list(SLL_list *list) {
    if(list->length == 0) {
        return;
    }

    struct node *tmp = list->head;

    while (tmp != NULL) {
        printf("%d -> ", tmp->data);
        tmp = tmp->next;
    }

    printf("NULL\n");
}

/* FREE FUNCTIONS */

int free_list(SLL_list **list_ref) {
    if(*list_ref == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    SLL_list *list = *list_ref;

    struct node *current = list->head;
    struct node *next_node;

    while(current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    free(list);
    *list_ref = NULL;

    return SLL_SUCCESS;
}

/* BOOLEAN CHECKS */

bool is_empty(SLL_list *list) {
    if(list == NULL) {
        return false;
    }

    return (list->length == 0);
}

/* GET AT SPECIFIC POSITION */

int get_head(SLL_list *list, int *output) {
    if(output == NULL) {
        return SLL_ERROR_INVALID_ARGUMENT;
    }

    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    if(is_empty(list)) {
        return SLL_ERROR_EMPTY;
    }

    *output = list->head->data;

    return SLL_SUCCESS;
}

int get_at(SLL_list *list, int position, int *output) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    if(position < 0) {
        return SLL_ERROR_INVALID_POSITION;
    }

    if(position >= list->length) {
        return SLL_ERROR_INVALID_POSITION;
    }

    if(position == 0) {
        return get_head(list, output);
    }

    if(position == (list->length - 1)) {
        return get_tail(list, output);
    }

    struct node *current_node = list->head->next;

    for(int i = 1; i < position; i++) {
        current_node = current_node->next;
    }

    *output = current_node->data;

    return SLL_SUCCESS;
}

int get_tail(SLL_list *list, int *output) {
    if(output == NULL) {
        return SLL_ERROR_INVALID_ARGUMENT;
    }

    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    if(is_empty(list)) {
        return SLL_ERROR_EMPTY;
    }

    *output = list->tail->data;

    return SLL_SUCCESS;
}

int main(void) {
    SLL_list *my_list = initialize_list();

    if(my_list == NULL) {
        printf("Error initializing the list. Aborting\n");
        return -1;
    }

    printf("Is emtpy?: %s\n", is_empty(my_list) ? "true" : "false");

    insert_head(my_list, 5);

    printf("Is emtpy?: %s\n", is_empty(my_list) ? "true" : "false");
    insert_head(my_list, 10);
    insert_head(my_list, 20);

    print_list(my_list);
    printf("List length: %d\n", my_list->length);

    delete_head(my_list);

    print_list(my_list);
    printf("List length: %d\n", my_list->length);
    free_list(&my_list);

    SLL_list *my_list2 = initialize_list();

    if(my_list2 == NULL) {
        printf("Error initializing the list. Aborting\n");
        return -1;
    }

    insert_head(my_list2, 5);
    insert_head(my_list2, 10);
    insert_head(my_list2, 20);
    insert_head(my_list2, 30);
    insert_head(my_list2, 40);
    insert_head(my_list2, 50);

    print_list(my_list2);
    printf("List length: %d\n", my_list2->length);

    delete_at(my_list2, 1);

    print_list(my_list2);
    printf("List length: %d\n", my_list2->length);

    insert_tail(my_list2, 60);
    print_list(my_list2);
    printf("List length: %d\n", my_list2->length);

    delete_tail(my_list2);
    print_list(my_list2);
    printf("List length: %d\n", my_list2->length);

    insert_at(my_list2, 70, 2);
    print_list(my_list2);
    printf("List length: %d\n", my_list2->length);

    insert_at(my_list2, 80, 5);
    print_list(my_list2);
    printf("List length: %d\n", my_list2->length);

    insert_at(my_list2, 90, 7);
    print_list(my_list2);
    printf("List length: %d\n", my_list2->length);

    insert_at(my_list2, 100, 0);
    print_list(my_list2);
    printf("List length: %d\n", my_list2->length);

    int x = 0;

    get_head(my_list2, &x);
    printf("x: %d\n", x);
    get_tail(my_list2, &x);
    printf("x: %d\n", x);
    get_at(my_list2, 3, &x);
    printf("x: %d\n", x);

    free_list(&my_list2);
    free_list(&my_list2);

    return 0;
}