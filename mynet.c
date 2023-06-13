#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "myfuncs.h"

#define MAXLAYERNODES 1 << 10


struct nodelayer *mklayer(int *, int);
int backprop(struct node *);

/**
 * Make a layer with the dimensions provided in the list `dims`.
 */
struct nodelayer *mklayer(int *dims, int ndims) {

    int i, *ptr, size;
    struct node *nodes;
    struct nodelayer *layer;

    size = 1;
    for (i = 0; i < ndims; i++) {
        ptr = dims + i;
        size *= *ptr;
    }

    if (size == 0 || size > MAXLAYERNODES)
        return NULL;

    nodes = (struct node *) malloc(sizeof(struct node) * size);
    memset(nodes, 0, sizeof(struct node) * size);

    layer = (struct nodelayer *) malloc(sizeof(struct layer));

    layer->dims = dims;
    layer->ndims = ndims;
    layer->nodes = nodes;
    layer->next = NULL;

    // initialize layer values to small random numbers
    // - save this for init in net? but could also use seed and init whole net

    return layer;
}

int backprop(struct node *layer) {


}

