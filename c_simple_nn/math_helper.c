#include <math.h>
#include "math_helper.h"

double abs_val(double a)
{
    if (a < 0)
    {
        return -a;
    }
    return a;
}

const double EPSILON = 0.00000001;

bool double_equals(double a, double b)
{
    if (abs_val(a - b) > EPSILON)
    {
        return false;
    }
    return true;
}

double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double d_sigmoid(double x) {
    return (exp(-x))/(pow((1+exp(-x)), 2));
}

double weird_d_sigmoid(double x) {
    return x * (1-x);
}

double rand_weight() {
    return ((double)rand())/((double)RAND_MAX);
}