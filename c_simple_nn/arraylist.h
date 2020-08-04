#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdbool.h>

#define ARRAYLIST_INITIAL_CAPACITY 4

typedef struct
{
    size_t size;
    size_t capacity;
    double *data;
} ArrayList;

/* Constructor and Destructor */

void arr_init(ArrayList *arr);
void arr_free_memory(ArrayList *arr);

/* Mutators */

void arr_append(ArrayList *arr, double val);
void arr_prepend(ArrayList *arr, double val);
void arr_delete(ArrayList *arr, int index);
void arr_delete_value(ArrayList *arr, double val);
void arr_set(ArrayList *arr, int index, double val);
void arr_resize(ArrayList *arr);

/* Accessors */

double arr_get(ArrayList *arr, int index);
double arr_pop(ArrayList *arr);
int arr_find_value(ArrayList *arr, double val);
int arr_size(ArrayList *arr);
int arr_capacity(ArrayList *arr);
bool arr_is_empty(ArrayList *arr);

/* Ease of life */
void arr_print(ArrayList *arr);
void arr_full_print(ArrayList *arr);

#endif