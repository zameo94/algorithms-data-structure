#ifndef SLL_H
#define SLL_H

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

SLL_list *initialize_list();

// Insert
int insert_head(SLL_list *list, int data);
int insert_at(SLL_list *list, int data, int position); 
int insert_tail(SLL_list *list, int data);

// Delete
int delete_head(SLL_list *list);
int delete_at(SLL_list *list, int position);
int delete_tail(SLL_list *list);

// Get
int get_head(SLL_list *list, int *output);
int get_at(SLL_list *list, int position, int *output);
int get_tail(SLL_list *list, int *output);

// Substitution
int sub_head(SLL_list *list, int new_value);
int sub_at(SLL_list *list, int position, int new_value);
int sub_tail(SLL_list *list, int new_value);
int substitution(SLL_list *list, int old_value, int new_value, bool sub_all);
int sub(SLL_list *list, int old_value, int new_value);
int gsub(SLL_list *list, int old_value, int new_value);

// Utility
void print_list(SLL_list *list);
int free_list(SLL_list **list_ref);
bool is_empty(SLL_list *list);

#endif
