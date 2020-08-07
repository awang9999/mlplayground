#include <stdio.h>
#include<stdlib.h>
#include "matrix.h"
#include "math_helper.h"

/* Constructor and Destructor */

void m_init(Matrix *a, int r, int c) {
    a->rows = r;
    a->cols = c;
    ArrayList arr;
    arr_init(&arr);
    arr_set(&arr, r*c, 0);
    a->data = arr;
}

void m_identity(Matrix *a, int size) {
    m_init(a, size, size);
    for (int i = 0; i < size; i++) {
        m_set(a, i, i, 1);
    }
}
void m_free_memory(Matrix *a) {
    arr_free_memory(&(a->data));
}

/* Mutators */

bool m_set(Matrix *a, int r, int c, double val) {
    arr_set(&(a->data), r*(a->cols) + c, val);
    return true;
}
void m_map_row(Matrix *a, int r, double (*f)(double)) {
    if (r >= a->rows) {
        printf("Cannot map over rows: index out of bounds");
        m_print(a);
        exit(1);
    }
    for (int j = 0; j < a->cols; j++) {
        double x = m_get(a, r, j);
        m_set(a, r, j, f(x));
    }
}

void m_map_col(Matrix *a, int c, double (*f)(double)) {
    if (c >= a->cols) {
        printf("Cannot map over rows: index out of bounds");
        m_print(a);
        exit(1);
    }
    for (int i = 0; i < a->rows; i++) {
        double x = m_get(a, i, c);
        m_set(a, i, c, f(x));
    }
}

void m_map(Matrix *a, double (*f)(double)) {
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            double x = m_get(a, i, j);
            m_set(a, i, j, f(x));
        }
    }
}

void m_add(Matrix *a, Matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols) {
        printf("Cannot add matrices: Mismatched dimensions.\n");
        m_full_print(a);
        m_full_print(b);
        exit(1);
    }
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            double x = m_get(a, i, j) + m_get(b, i, j);
            m_set(a, i, j, x);
        }
    }
}

void m_subtract(Matrix *a, Matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols) {
        printf("Cannot add matrices: Mismatched dimensions.\n");
        m_full_print(a);
        m_full_print(b);
        exit(1);
    }
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            double x = m_get(a, i, j) - m_get(b, i, j);
            m_set(a, i, j, x);
        }
    }
}

/* Accessors */

/* Naive matrix multiplication O(n^3) */
void m_mult(Matrix *a, Matrix *b, Matrix *dest) {
    if (a->cols != b->rows) {
        printf("Cannot multiply matrices: Mismatched dimensions.\n");
        m_full_print(a);
        m_full_print(b);
        exit(1);
    }
    m_init(dest, a->rows, b->cols);
    for (int i = 0; i < dest->rows; i++) {
        for (int j = 0; j < dest->cols; j++) {
            double sum = 0;
            for (int k = 0; k < a->rows; k++) {
                sum += m_get(a, i, k) * m_get(b, k, j);
            }
            m_set(dest, i, j, sum);
        }
    }
}

void m_transpose(Matrix *a, Matrix *dest) {
    m_init(dest, a->cols, a->rows);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            m_set(dest, j, i, m_get(a, i, j));
        }
    }
}

void m_copy(Matrix *src, Matrix *dest) {
    m_init(dest, src->rows, src->cols);
    for (int i = 0; i < src->rows; i++) {
        for (int j = 0; j < src->cols; j++) {
            m_set(dest, i, j, m_get(src, i, j));
        }
    }
}

double m_get(Matrix *a, int r, int c) {
    return arr_get(&(a->data), r*(a->cols) + c);
}

int m_rows(Matrix *a) {
    return a->rows;
}

int m_cols(Matrix *a) {
    return a->cols;
}

/* Ease of life */

void m_print(Matrix *a) {
    for (int i = 0; i < a->rows; i++) {
        printf("|");
        for (int j = 0; j < a->cols; j++) {
            printf(" %.4f ", m_get(a, i, j));
        }
        printf("|\n");
    }
}
void m_full_print(Matrix *a) {
    printf("Size: %d rows by %d columns\n", a->rows, a->cols);
    printf("___|");
    for (int i = 0; i < a->cols; i++) {
        printf("__[%d]___", i);
    }
    printf("_\n");
    for (int i = 0; i < a->rows; i++) {
        printf("[%d]|", i);
        for (int j = 0; j < a->cols; j++) {
            printf(" %.4f ", m_get(a, i, j));
        }
        printf("\n");
    }
}

bool m_equals(Matrix *a, Matrix *b) {
    if (!(a->rows == b->rows) || !(a->cols == b->cols)) {
        return false;
    }
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            if (!(double_equals(m_get(a, i, j), m_get(b, i, j)))) {
                return false;
            }
        }
    }
    return true;
}