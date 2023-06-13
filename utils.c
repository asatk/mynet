#include <stdlib.h>

// TEMPORARY uni
double randu(double a, double b) {
    return (double) rand() / (double) (RAND_MAX + 1) * (b - a) + a;
}


