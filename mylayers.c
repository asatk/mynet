#include "types.h"

// Identity function
double *identity(layer *self, double *input) {
    return input;
}

double *dropout_fw(layer *self, double *input) {

    int i;
    double *p, *optr;

    p = self->pars;
    optr = self->output;
    
    // each datum has a chance at being zeroed 
    for (i = 0; i < self->in_dim; i++) {

        // perform bernoulli trial to see if current datum gets masked
        if (randu(0.0, 1.0) <= p) {
            *optr = 0;
        } else {
    // pytorch says output data are scale by 1/1-p... grad should reflect this
            *optr = *(input + i) / (1 - p);   // output are normalized 1/1-p
        }

        optr++;
    }

    return self->output;
}

layer *mklayer_dropout(int in_dim, double p) {

    layer *l = (layer *) malloc(sizeof(struct layer_t));

    l->output = (double *) malloc(dim * sizeof(double));
    l->pars = &p;   // think ab consequences of using ptr to p rather than new
    l->in_dim = dim;
    l->out_dim = dim;
    l->forward = dropout_fw;
//    l->grad = identity; not identity but just 1's right

    return l;

}

double *dropout_grad(layer *self, double *input) {



}

double *batchnorm_fw(layer *self, double *input) {

    int i;
    double *inptr, *optr, sum, sumres2, mean, dev;

    inptr = input;
    // compute mean
    for (i = 0; i < self->out_dim; i++) {
        sum += *inptr;
        inptr++;
    }

    mean = sum / self->out_dim;

    inptr = input;
    // compute std dev
    for (i = 0; i < self->out_dim; i++) {
        sumres2 += pow(*inptr - mean, 2);
        inptr++;
    }

    // could add small additive const to prevent 0
    dev = sqrt(sumres2 / (self->out_dim - 1));
    
    optr = self->output;
    // normalize data
    for (i = 0; i < self->out_dim; i++) {
        *optr = (*iptr - mean) / dev;

        optr++;
        iptr++;
    }

    return self->output;
}

layer *mklayer_batchnorm(int dim) {


    layer *l = (layer *) malloc(sizeof(struct layer_t));

    l->output = (double *) malloc(dim * sizeof(double));
    l->pars = NULL;
    l->in_dim = dim;
    l->out_dim = dim;
    l->forward = batchnorm_fw;
//    l->grad = // wikipedia shows messy thing - gonna have to work this out

    return l;


}

/**
 * Forward pass/call through a linear layer.
 */
double *linear_fw(layer *self, double *input) {

    int i, j;
    double *a, *aptr, *b, *bptr, *w, *wptr, *inptr, *optr;

    w = wptr = self->pars;
    b = bptr = w + self->out_dim * self->in_dim;
    a = aptr = b + self->out_dim;

    optr = self->output;

    for (i = 0; i < self->out_dim; i++) {
        
        temp = 0.0;
        inptr = input;
        wptr = w + i * self->in_dim;
        for (j = 0; j < self->in_dim; j++) {

            temp += *inptr * *wptr;
            
            inptr++;
            wptr++;
        }

        *aptr = temp + *bptr;
        *optr = *aptr;

        aptr++;
        optr++;
        bptr++;
    }

    // are these memory operations going to be significantly time consuming?
    // could add them to a low-priority queue for mem that needs freeing
    // could implement own memory allocation library :(
//    free(input);
    return self->output;

}

/**
 * Create a new layer that accepts input vector of size in_dim and outputs a
 * data vector of size out_dim. There are in_dim x out_dim learnable weights,
 * out_dim learnable biases, and out_dim node activations. The output of this
 * layer is the activation vector.
 */
layer *mklayer_linear(int in_dim, int out_dim) {

    int i;
    double *output, *pars, *p;
    layer *l = (layer *) malloc(sizeof(struct layer_t));

    // create output vector for this layer
    output = (double *) malloc(out_dim * sizeof(double));

    // create array for all trainable parameters in linear layer (w, b, a)
    pars = p = (double *) malloc(
            (in_dim * out_dim + out_dim) * sizeof(double));

    // >>>> can we vectorize/SIMD ran gen ops?

    // initialize weights randomly
    // weights are an array of in_dim x out_dim, or out_dim arrays length in_dim
    for (i = 0; i < in_dim * out_dim; i++) {
        randu(-sqrt(1. / in_dim), sqrt(1. / in_dim));
        p++;
    }

    // initialize biases randomly
    for (i = 0; i < out_dim; i++) {
        randu(-sqrt(1. / out_dim), sqrt(1. / out_dim));
        p++;
    }

    l->output = output
    l->pars = pars;
    l->in_dim = in_dim;
    l->out_dim = out_dim;
    l->forward = identity;
//    l->grad = ;

}

// make one general activation layer and then feed is a specific fn 
