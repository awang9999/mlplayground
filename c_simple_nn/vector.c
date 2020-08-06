#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "math_helper.h"

/* Constructor and Destructor */
void v_init(Vector *v, int dim)
{
    v->dim = dim;
    ArrayList a;
    arr_init(&a);
    for (int i = 0; i < dim; i++)
    {
        arr_append(&a, 0);
    }
    v->xs = a;
}

void v_free_memory(Vector *v)
{
    arr_free_memory(&(v->xs));
}

/* Mutators */
/* All mutators modify the first vector provided as an argument
  (and leaves the second vector unmodified if it exists). */

void v_add(Vector *v1, Vector *v2)
{
    if (v1->dim != v2->dim)
    {
        printf("Cannot add vectors: improper dimensions. (v1.dim: %d, v2.dim: %d)\n", v1->dim, v2->dim);
        printf("v1 is unmodified.\n");
        return;
    }
    for (int i = 0; i < v_dim(v1); i++)
    {
        double v1_x = v_get(v1, i);
        double v2_x = v_get(v2, i);
        v_set(v1, i, v1_x + v2_x);
    }
}
void v_subtract(Vector *v1, Vector *v2)
{
    if (v1->dim != v2->dim)
    {
        printf("Cannot subtract vectors: improper dimensions. (v1.dim: %d, v2.dim: %d)\n", v1->dim, v2->dim);
        printf("v1 is unmodified.\n");
        return;
    }
    for (int i = 0; i < v_dim(v1); i++)
    {
        double v1_x = v_get(v1, i);
        double v2_x = v_get(v2, i);
        v_set(v1, i, v1_x - v2_x);
    }
}

double d_invert(double a)
{
    return -a;
}

void v_invert(Vector *v)
{
    v_map(v, d_invert);
}

void v_scalar_mult(Vector *v, double s)
{
    for (int i = 0; i < v_dim(v); i++)
    {
        double x = v_get(v, i);
        v_set(v, i, x * s);
    }
}

void v_scalar_divide(Vector *v, double s)
{
    v_scalar_mult(v, 1 / s);
}

void v_map(Vector *v, double (*f)(double))
{
    for (int i = 0; i < v_dim(v); i++)
    {
        double x = v_get(v, i);
        v_set(v, i, f(x));
    }
}

bool v_set(Vector *v, int ind, double val)
{
    arr_set(&(v->xs), ind, val);
    return true;
}

/* Accessors */

double v_dot(Vector *v1, Vector *v2)
{
    if (v1->dim != v2->dim)
    {
        printf("Cannot dot vectors: improper dimensions. (v1.dim: %d, v2.dim: %d)\n", v1->dim, v2->dim);
        printf("returning 0.\n");
        return 0;
    }
    double total = 0;
    for (int i = 0; i < v1->dim; i++)
    {
        total += v_get(v1, i) * v_get(v2, i);
    }
    return total;
}

int v_dim(Vector *v)
{
    return v->dim;
}

double v_get(Vector *v, int ind)
{
    return arr_get(&(v->xs), ind);
}

/* Ease of life */

void v_print(Vector *v)
{
    arr_print(&(v->xs));
}

void v_full_print(Vector *v)
{
    printf("(Dimensions: %d) ", v->dim);
    v_print(v);
}

bool v_equals(Vector *v1, Vector *v2)
{
    if (v1->dim != v2->dim)
    {
        return false;
    }
    for (int i = 0; i < v_dim(v1); i++)
    {
        if (!(double_equals(v_get(v1, i), v_get(v2, i))))
        {
            return false;
        }
    }
    return true;
}