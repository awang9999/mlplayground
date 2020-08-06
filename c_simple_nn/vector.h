#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include "arraylist.h"

/* Declarations for Structs*/

typedef struct
{
    int dim;
    ArrayList xs;
} Vector;

/* Constructor and Destructor */

void v_init(Vector *v, int dim);
void v_free_memory(Vector *v);

/* Mutators */

void v_add(Vector *v1, Vector *v2);
void v_scalar_mult(Vector *v, double s);
void v_invert(Vector *v);
void v_subtract(Vector *v1, Vector *v2);
void v_scalar_divide(Vector *v, double s);
void v_map(Vector *v, double (*f)(double));
bool v_set(Vector *v, int ind, double val);

/* Accessors */

double v_dot(Vector *v1, Vector *v2);
int v_dim(Vector *v);
double v_get(Vector *v, int ind);

/* Ease of life */

void v_print(Vector *v);
void v_full_print(Vector *v);
bool v_equals(Vector *v1, Vector *v2);

#endif