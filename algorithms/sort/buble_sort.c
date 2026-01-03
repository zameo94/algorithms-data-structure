#include <stdio.h>
#include <stdbool.h>

// Setup Errors code
#define ERROR_ARRAY_NOT_ALLOCATED -11

// Input Error
#define ERROR_INVALID_LENGTH -30

// Success code
#define SUCCESS 0

static void swap_values(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp; 
}

/*
 * Implementing buble sort algorithm, O(n^2)
*/
int bubble_sort(int *array, size_t len) {
    if(array == NULL) return ERROR_ARRAY_NOT_ALLOCATED;

    if (len < 2) return SUCCESS;

    for(size_t i = 0; i < len; i++) {
        bool swapped = false;

        for(size_t j = 0; j < len - i - 1; j++) {
            if(array[j] > array[j + 1]) {
                swap_values(&array[j], &array[j + 1]);
                swapped = true;
            }
        }

        // If no swap happened, the array is already sorted
        if(!swapped) break;
    }

    return SUCCESS;
}

int main(void) {
    int my_array[] = { 65, 6, 3, 9, 32, 10 };
    size_t len = sizeof(my_array) / sizeof(my_array[0]);

    printf("Array before sorting:\n");

    for(size_t i = 0; i < len; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");

    int result = bubble_sort(my_array, len);

    if(result == ERROR_ARRAY_NOT_ALLOCATED) {
        printf("Error: Invalid array.\n");
    } else if(result == ERROR_INVALID_LENGTH) {
        printf("Error: Invalid array length.\n");
    } else if(result == SUCCESS) {
        printf("Array sorted:\n");

        for(size_t i = 0; i < len; i++) {
            printf("%d ", my_array[i]);
        }
        printf("\n");
    }

    return 0;
}