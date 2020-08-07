#include <stdio.h>
#include <stdlib.h>
#include "arraylist.h"

/* Constructor and Destructor */

void arr_init(ArrayList *arr)
{
    arr->size = 0;
    arr->capacity = ARRAYLIST_INITIAL_CAPACITY;
    arr->data = malloc(sizeof(double) * arr->capacity);
}

void arr_free_memory(ArrayList *arr)
{
    free(arr->data);
}

/* Mutators */

void arr_append(ArrayList *arr, double val)
{
    arr_resize(arr);
    arr->data[arr->size++] = val;
}

void arr_prepend(ArrayList *arr, double val)
{
    for (int i = arr->size; i >= 0; i--)
    {
        arr_set(arr, i + 1, arr->data[i]);
    }
    arr_set(arr, 0, val);
}

void arr_delete(ArrayList *arr, int index)
{
    for (int i = index; i < arr->size; i++)
    {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
}

void arr_delete_value(ArrayList *arr, double val)
{
    for (int i = 0; i < arr->size; i++)
    {
        if (arr->data[i] == val)
        {
            arr_delete(arr, i);
        }
    }
}

void arr_set(ArrayList *arr, int index, double val)
{
    while (index > arr->size)
    {
        arr_append(arr, 0);
    }
    arr->data[index] = val;
}

void arr_resize(ArrayList *arr)
{
    if (arr->size >= arr->capacity)
    {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, sizeof(double) * arr->capacity);
    }
}

/* Readers */

double arr_get(ArrayList *arr, int index)
{
    if (index > arr->capacity || index < 0)
    {
        printf("Index %d out of bounds for ArrayList of size %ld\n", index, arr->size);
        exit(1);
    }
    return arr->data[index];
}

double arr_pop(ArrayList *arr)
{
    double data = arr->data[arr->size - 1];
    arr_set(arr, arr->size - 1, 0);
    arr->size--;
    return data;
}

int arr_find_value(ArrayList *arr, double val)
{
    for (int i = 0; i < arr->size; i++)
    {
        if (arr->data[i] == val)
        {
            return i;
        }
    }
    return -1;
}

int arr_size(ArrayList *arr)
{
    return arr->size;
}

int arr_capacity(ArrayList *arr)
{
    return arr->capacity;
}

bool arr_is_empty(ArrayList *arr)
{
    return arr->size == 0;
}

/* Ease of life */
void arr_print(ArrayList *arr)
{
    if (arr_is_empty(arr))
    {
        printf("[]");
    }
    else
    {
        printf("[");
        int i = 0;
        for (i = 0; i < arr->size - 1; i++)
        {
            printf("%.4f, ", arr_get(arr, i));
        }
        printf("%.4f]", arr_get(arr, i));
    }
}

void arr_full_print(ArrayList *arr)
{
    printf("(size: %d, cap: %d) ", arr_size(arr), arr_capacity(arr));
    arr_print(arr);
}