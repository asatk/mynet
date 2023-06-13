#ifndef _myfuncs_h
#define _myfuncs_h



struct fn {
    net_fn func;   // activation function
    net_fn inv;    // inverse of the activation function
    net_fn deriv;  // derivative of the activation function
};

double relu_f(double a);
double relu_i(double v);
double relu_d(double a);
double leakyrelu_f(double a);
double leakyrelu_i(double a);
double leakyrelu_d(double a);
double sigm_f(double a);
double sigm_i(double v);
double sigm_d(double a);
double tanh_f(double a);
double tanh_i(double v);
double tanh_d(double a);
#endif
