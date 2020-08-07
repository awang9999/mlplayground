#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include "arraylist.h"

typedef struct
{
    int rows;
    int cols;
    ArrayList data;
} Matrix;

/* Constructor and Destructor */

void m_init(Matrix *a, int r, int c);
void m_identity(Matrix *a, int size);
void m_free_memory(Matrix *a);

/* Mutators */

bool m_set(Matrix *a, int r, int c, double val);
void m_map_row(Matrix *a, int r, double (*f)(double));
void m_map_col(Matrix *a, int c, double (*f)(double));
void m_map(Matrix *a, double (*f)(double));
void m_add(Matrix *a, Matrix *b);
void m_subtract(Matrix *a, Matrix *b);

/* Accessors */

void m_mult(Matrix *a, Matrix *b, Matrix *dest);
void m_transpose(Matrix *a, Matrix *dest);
void m_copy(Matrix *src, Matrix *dest);
double m_get(Matrix *a, int r, int c);
int m_rows(Matrix *a);
int m_cols(Matrix *a);

/* Ease of life */

void m_print(Matrix *a);
void m_full_print(Matrix *a);
bool m_equals(Matrix *a, Matrix *b);

#endif