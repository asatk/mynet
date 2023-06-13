#ifndef _types_h
#define _types_h

struct layer_t;
typedef double (*callfn)(struct layer_t *, double *);
typedef double (*gradfn)(struct layer_t *, double *);

// Structure defining a network layer
typedef struct layer_t {
    int in_dim;         // dimension of the input
    int out_dim;        // dimension of the output
    double *output      // output vector
    double *pars;       // list of learnable parameters
    callfn forward;     // forward call for the layer
    gradfn grad;        // gradient for the transformation in this layer
} layer;

#endif
