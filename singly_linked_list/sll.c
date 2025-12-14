#include "sll.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int delete_value(SLL_list *list, int value, bool delete_all) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    if(is_empty(list)) {
        return SLL_ERROR_EMPTY;
    }

    struct node *prev = NULL;
    struct node *current = list->head;
    struct node *next = NULL;

    while(current != NULL) {
        next = current->next;

        if(current->data == value) {
            struct node *node_to_delete = current;

            if(list->head == node_to_delete) {
                list->head = list->head->next;
            } else {
                prev->next = node_to_delete->next;
            }

            if(list->tail == node_to_delete) {
                list->tail = prev;
            }

            free(node_to_delete);
            list->length--;

            if(!delete_all) {
                break;
            }
        } else {
            prev = current;
        }

        current = next;
    }

    return SLL_SUCCESS;
}

int delete_single_value(SLL_list *list, int value) {
    return delete_value(list, value, false);
}

int delete_all_values(SLL_list *list, int value) {
    return delete_value(list, value, true);
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

/* CLEANING FUNCTIONS */

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

int clear_list(SLL_list *list) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    struct node *current = list->head;
    struct node *next = NULL;

    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    return SLL_SUCCESS;
}

/* BOOLEAN CHECKS */

bool is_empty(SLL_list *list) {
    if(list == NULL) {
        return false;
    }

    return (list->head == NULL);
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

    struct node *current_node = list->head;

    for(int i = 0; i < position; i++) {
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

/* SUBSTITUTION */

int sub_head(SLL_list *list, int new_value) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    if(is_empty(list)) {
        return SLL_ERROR_EMPTY;
    }

    list->head->data = new_value;

    return SLL_SUCCESS;
}

int sub_at(SLL_list *list, int position, int new_value) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    if(position < 0) {
        return SLL_ERROR_INVALID_POSITION;
    }

    if(position >= list->length) {
        return SLL_ERROR_INVALID_POSITION;
    }

    struct node *current_node = list->head;

    for(int i = 0; i < position; i++) {
        current_node = current_node->next;
    }

    current_node->data = new_value;

    return SLL_SUCCESS;
}

int sub_tail(SLL_list *list, int new_value) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    if(is_empty(list)) {
        return SLL_ERROR_EMPTY;
    }

    list->tail->data = new_value;

    return SLL_SUCCESS;
}

int substitution(SLL_list *list, int old_value, int new_value, bool sub_all) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    struct node *current_node = list->head;

    while(current_node != NULL) {
        if(current_node->data == old_value) {
            current_node->data = new_value;

            if(!sub_all) {
                break;
            }
        }
        current_node = current_node->next;
    }

    return SLL_SUCCESS;
}

int sub(SLL_list *list, int old_value, int new_value) {
    return substitution(list, old_value, new_value, false);
}

int gsub(SLL_list *list, int old_value, int new_value) {
    return substitution(list, old_value, new_value, true);
}

/* SEARCH */

int index_of(SLL_list *list, int value) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    if(is_empty(list)) {
        return SLL_ERROR_EMPTY;
    }

    int position = 0;
    struct node *current_node = list->head; 

    while(current_node != NULL) {
        if(current_node->data == value) return position;
        current_node = current_node->next;
        position++;
    }

    return SLL_ERROR_NOT_FOUND;
}

/* REVERSE */

int reverse_list(SLL_list *list) {
    if(list == NULL) {
        return SLL_ERROR_LIST_NOT_ALLOCATED;
    }

    if(is_empty(list)) {
        return SLL_ERROR_EMPTY;
    }

    if(list->length == 1) {
        return SLL_SUCCESS;
    }

    struct node *prev = NULL;
    struct node *current = list->head;
    struct node *next = NULL;

    list->tail = list->head;

    while(current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list->head = prev;

    return SLL_SUCCESS;
}
