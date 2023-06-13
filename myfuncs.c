#include <math.h>


/**                                           *
 * ---------- ACTIVATION FUNCTIONS ---------- *
 *                                            */

/**
 * Define the set of ReLU (Rectified Linear Unit) activation functions
 */

double relu_f(double a) {
    return (a < 0) ? 0 : a;
}

double relu_i(double v) {
    return v;
}

double relu_d(double a) {
    return (a < 0) ? 0 : 1;
}

/**
 * Define the set of Leaky ReLU activation functions
 */
double leakyrelu_f(double a) {
    return 0;
}

/**
 * Define the set of Parameterized ReLU activation functions
 */


/**
 * Define the set of Sigmoid activation functions
 */
double sigm_f(double a) {
    return 0.5 + 0.5 * tanh(a / 2);
}

double sigm_i(double v) {
    return 2 * atanh(2 * v - 1);
}

double sigm_d(double a) {
    return 0.25 * (1 - pow(tanh(a / 2), 2));
}

/**
 * Define the set of Tanh acitvation functions
 */
double tanh_f(double a) {
    return tanh(a);
}

double tanh_i(double v) {
    return atanh(v);
}

double tanh_d(double a) {
    return 1 - pow(tanh(a), 2);
}
