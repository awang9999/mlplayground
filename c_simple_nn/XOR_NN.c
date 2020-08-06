/*

Project: C Neural Network that learns XOR
Author: Alexander Wang (aw576@cornell.edu/alexander.wang2001@gmail.com)
Last updated: 2020-08-04

Description:
In this project, I will attempt to recreate the popular
simple neural network that learns fuzzy XOR behavior from scratch in
the C language. Modules such as ArrayList.c and Vector.c were inspired
from the works of previous C programmers and extended in functionality
by myself. The neural network code will be guided by Santiago
Becerra's article.
(https://towardsdatascience.com/simple-neural-network-implementation-in-c-663f51447547).

This neural network will consist of 1 hidden layer with two hidden nodes. This
will be the simplest architecture capable of learning the fuzzy XOR behavior.

Expected XOR Behavior:
A    B    Output
----------------
0    0       0
0    1       1
1    0       1
1    1       0

Planned Activation functions for each layer:
Input layer: identity
Hidden layer: tanh
Output layer: sigmoid

*/

#include <stdio.h>
#include <time.h>
#include "vector.h"
#include "matrix.h"

void test_ArrayLists()
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    printf("Creating ArrayList... ");
    ArrayList a;
    arr_init(&a);
    printf("Done.\n");

    printf("Result: ");
    arr_full_print(&a);
    printf("\n");

    printf("Is the ArrayList empty? (Expected true): %s\n", arr_is_empty(&a) ? "true" : "false");
    printf("Size of the ArrayList (Expected 0): %d\n", arr_size(&a));
    printf("Capacity of the ArrayList (Expected 4): %d\n", arr_capacity(&a));

    printf("\n");

    printf("Inserting values 0-9 to the ArrayList... ");

    for (int i = 0; i < 10; i++)
    {
        arr_append(&a, i);
    }
    printf("Done.\n");

    printf("Result: ");
    arr_full_print(&a);
    printf("\n");

    printf("Size of the ArrayList (Expected 10): %d\n", arr_size(&a));
    printf("Capacity of the ArrayList (Expected 16): %d\n", arr_capacity(&a));
    printf("Is the ArrayList empty? (Expected false): %s\n", arr_is_empty(&a) ? "true" : "false");

    printf("\n");

    printf("Prepending 3.14 to ArrayList... ");
    arr_prepend(&a, 3.14);
    printf("Done.\n");

    printf("Result: ");
    arr_full_print(&a);
    printf("\n");

    printf("Getting the prepended value (Expected 3.14): %.2f\n", arr_get(&a, 0));
    printf("Size of the ArrayList (Expected 11): %d\n", arr_size(&a));

    printf("\n");

    printf("Popping the last item (Expected 9.00): %.2f\n", arr_pop(&a));
    printf("Result: ");
    arr_full_print(&a);
    printf("\n");
    printf("Size of the ArrayList (Expected 10): %d\n", arr_size(&a));

    printf("\n");

    printf("Popping the last item (Expected 8.00): %.2f\n", arr_pop(&a));
    printf("Result: ");
    arr_full_print(&a);
    printf("\n");
    printf("Size of the ArrayList (Expected 9): %d\n", arr_size(&a));

    // Should now be 5
    printf("Getting a[5] (Expected 4.00): %.2f\n", arr_get(&a, 5));

    printf("\n");

    // Deleting it
    printf("Deleting a[5]... ");
    arr_delete(&a, 5);
    printf("Done.\n");
    printf("Result: ");
    arr_full_print(&a);
    printf("\n");
    printf("Size of the ArrayList (Expected 8): %d\n", arr_size(&a));

    printf("a[3] (Expected 2.00): %.2f\n", arr_get(&a, 3));
    printf("a[4] (Expected 3.00): %.2f\n", arr_get(&a, 4));
    // Should now be 5
    printf("a[5] (Expected 5.00): %.2f\n", arr_get(&a, 5));
    printf("a[6] (Expected 6.00): %.2f\n", arr_get(&a, 6));
    printf("a[7] (Expected 7.00): %.2f\n", arr_get(&a, 7));

    printf("\n");

    printf("Deleting the value 1.00... ");
    arr_delete_value(&a, 1);
    printf("Done.\n");
    printf("Result: ");
    arr_full_print(&a);
    printf("\n");
    printf("a[1] (Expected 0.00): %.2f\n", arr_get(&a, 1));
    printf("Finding value 2 (Expected 2): %d\n", arr_find_value(&a, 2));
    printf("Finding value 22 (Expected -1): %d\n", arr_find_value(&a, 22));

    arr_free_memory(&a);

    printf("\n");
    printf("All tests for ArrayList module done.\n");
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Completed in %f seconds. \n", cpu_time_used);
}

void print_test_vector_results(Vector *v1, Vector *v2)
{
    printf("Results: \n");
    printf("v1: ");
    v_full_print(v1);
    printf("\n");
    printf("v2: ");
    v_full_print(v2);
    printf("\n");
    printf("\n");
}

void test_Vectors()
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    printf("Initializing Vectors... ");
    Vector v1;
    Vector v2;
    v_init(&v1, 3);
    v_init(&v2, 3);
    printf("Done.\n");
    print_test_vector_results(&v1, &v2);

    printf("Filling vectors with values... ");
    v_set(&v1, 0, 1.23);
    v_set(&v1, 1, 4.56);
    v_set(&v1, 2, 7.89);
    v_set(&v2, 0, 3);
    v_set(&v2, 1, 4);
    v_set(&v2, 2, 5);
    printf(" Done.\n");
    print_test_vector_results(&v1, &v2);

    printf("Testing equality of v1 and v2 (Expected false): %s\n", v_equals(&v1, &v2) ? "true" : "false");
    printf("Testing equality v1 and v1 (Expected true): %s\n", v_equals(&v1, &v1) ? "true" : "false");
    printf("Initializing v3 a copy of v1... ");
    Vector v3;
    v_init(&v3, 3);
    v_set(&v3, 0, 1.23);
    v_set(&v3, 1, 4.56);
    v_set(&v3, 2, 7.89);
    printf("Done.\n");
    printf("Results: \n");
    printf("v3: ");
    v_full_print(&v3);
    printf("\n");
    printf("Testing equality v1 and v3 (Expected true): %s\n", v_equals(&v1, &v3) ? "true" : "false");
    printf("\n");

    printf("inverting v3... ");
    v_invert(&v3);
    printf("Done.\n");
    printf("Results: \n");
    printf("v3: ");
    v_full_print(&v3);
    printf("\n\n");

    printf("Adding v2 to v1... ");
    v_add(&v1, &v2);
    printf("Done.\n");
    print_test_vector_results(&v1, &v2);

    printf("Subtracting v1 from v2... ");
    v_subtract(&v2, &v1);
    printf("Done.\n");
    print_test_vector_results(&v1, &v2);

    printf("Multiplying v1 by 3... ");
    v_scalar_mult(&v1, 3);
    printf("Done.\n");
    print_test_vector_results(&v1, &v2);

    printf("Dividing v2 by 3... ");
    v_scalar_divide(&v2, 3);
    printf("Done.\n");
    print_test_vector_results(&v1, &v2);

    printf("Dot product of v1 and v2 (Expected: -145.9386): %f", v_dot(&v1, &v2));

    v_free_memory(&v1);
    v_free_memory(&v2);
    v_free_memory(&v2);

    printf("\n");
    printf("All tests for Vector module done.\n");
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Completed in %f seconds. \n", cpu_time_used);
}

void print_test_matrix_results(Matrix *a, Matrix *b, Matrix *c) {
    printf("Results.\n");
    printf("Matrix A:\n");
    m_full_print(a);
    printf("Matrix B:\n");
    m_full_print(b);
    printf("Matrix C:\n");
    m_full_print(c);
    printf("\n");
    printf("\n");
}

void test_Matrix() {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    printf("Initializing Matrices... ");
    Matrix a;
    Matrix b;
    Matrix c;
    Matrix mult_result;
    Matrix copy_result;
    m_identity(&a, 5);
    m_init(&b, 5, 6);
    m_init(&c, 6, 5);
    printf("Done.\n");

    print_test_matrix_results(&a, &b, &c);

    printf("Filling Matrix B and C... ");
    int p = 1;
    for (int i = 0; i < (&b)->rows; i++) {
        for (int j = 0; j < (&b)->cols; j++) {
            m_set(&b, i, j, p);
            p++;
        }
    }
    p = 1;
    for (int i = 0; i < (&c)->rows; i++) {
        for (int j = 0; j < (&c)->cols; j++) {
            m_set(&c, i, j, p);
            p++;
        }
    }
    printf("Done.\n");
    print_test_matrix_results(&a, &b, &c);

    printf("Multiplying B and C into mult_result... ");
    m_mult(&b, &c, &mult_result);
    printf("Done\n");

    printf("Result of mult_result:\n");
    m_full_print(&mult_result);
    printf("\n");

    printf("Copying mult_result into copy_result... ");
    m_copy(&mult_result, &copy_result);
    printf("Done\n");

    printf("Result of copy_result:\n");
    m_full_print(&copy_result);
    printf("\n");

    m_free_memory(&a);
    m_free_memory(&b);
    m_free_memory(&c);
    m_free_memory(&mult_result);
    m_free_memory(&copy_result);

    printf("All tests for Matrix module done.\n");
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Completed in %f seconds. \n", cpu_time_used);
}

void test_all()
{
    test_ArrayLists();
    test_Vectors();
    test_Matrix();
}

/* ACTUAL CODE FOR NEURAL NET BEGINS HERE. */

int main()
{
    //Clock stuff
    clock_t start, end;
    start = clock();

    //Neural network code

    static const int num_inputs = 2;
    static const int num_hidden = 2;
    static const int num_outputs = 1;

    Matrix hidden_layer;
    m_init(&hidden_layer, num_hidden, 1);

    Matrix output_layer;
    m_init(&output_layer, num_outputs, 1);

    Matrix hidden_bias;
    m_init(&hidden_bias, num_hidden, 1);

    Matrix output_bias;
    m_init(&output_bias, num_outputs, 1);

    Matrix hidden_weights;
    m_init(&hidden_weights, num_inputs, num_hidden);

    Matrix output_weights;
    m_init(&output_weights, num_hidden, num_outputs);

    static const int num_training_sets = 4;
    Matrix training_inputs;
    m_init(&training_inputs, 4, 2);
    m_set(&training_inputs, 1, 0, 1);
    m_set(&training_inputs, 2, 1, 1);
    m_set(&training_inputs, 3, 0, 1);
    m_set(&training_inputs, 3, 1, 1);

    m_full_print(&training_inputs);

    Matrix training_outputs;
    m_init(&training_outputs, 4, 1);
    m_set(&training_outputs, 1, 0, 1);
    m_set(&training_outputs, 2, 0, 1);

    m_full_print(&training_outputs);

    m_free_memory(&hidden_layer);
    m_free_memory(&output_layer);
    m_free_memory(&hidden_bias);
    m_free_memory(&output_bias);
    m_free_memory(&hidden_weights);
    m_free_memory(&output_weights);
    m_free_memory(&training_inputs);
    m_free_memory(&training_outputs);
    //End of Neural network code

    //Clean up and end clock stuff
    printf("main() finished.\n");
    end = clock();
    printf("Completed in %f seconds. \n", ((double)(end-start)) / CLOCKS_PER_SEC);
    return 0;
}