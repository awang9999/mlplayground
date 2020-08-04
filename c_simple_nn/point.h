#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Point Point;

Point *Point__create(int x, int y);
void Point__destroy(Point *self);
int Point__x(Point *self);
int Point__y(Point *self);

#endif