#include <stdio.h>

// Setup Errors code
#define ERROR_ARRAY_NOT_ALLOCATED -11

// Input Error
#define ERROR_INVALID_LENGTH -30

// General Error
#define ERROR_NOT_FOUND -40

/*
 * Implementing linear search algorithm, O(n)
*/
ssize_t linear_search(const int *array, size_t len, int x) {
    if(array == NULL) return ERROR_ARRAY_NOT_ALLOCATED;

    if(len < 1) return ERROR_INVALID_LENGTH;

    for(size_t i = 0; i < len; i++) {
        if(array[i] == x) return i;
    }

    return ERROR_NOT_FOUND;
}

int main(void) {
    int my_arr[] = { 1, 3, 5, 10, 4, 87, 9};
    size_t len = sizeof(my_arr) / sizeof(my_arr[0]);
    int x = 10;

    ssize_t result = linear_search(my_arr, len, x);

    if (result == ERROR_NOT_FOUND) {
    printf("Value %d not found in the array.\n", x);
    } else if (result == ERROR_ARRAY_NOT_ALLOCATED) {
        printf("Error: Invalid array.\n");
    } else if (result == ERROR_INVALID_LENGTH) {
        printf("Error: Invalid array length.\n");
    } else {
        printf("Value %d found at position: %zd\n", x, result);
    }

    return 0;
}
