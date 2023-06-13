#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "myfuncs.h"
#include "mylayers.h"
#include "mynet.h"
#include "types.h"

int vlevel = 0;

void printhelp(void);

void printhelp(void) {

    printf("\t-h - prints help menu.\n\t-v - sets level of verbose output.\n"
            "\t-o some option.\n");

}

int main(int argc, char **argv) {

    char c, *optstr = "e:hv:o:", *endptr;

    while ((c = getopt(argc, argv, optstr)) != -1) {
        switch (c) {
            case 'e':   //echo
                printf("%s\n", optarg);
                break;
            case 'h':   //help
                printhelp();
                break;
            case 'v':   //verbose
                errno = 0;
                vlevel = strtol(optarg, &endptr, 10);

                if (errno != 0) {
                    printf("invalid argument to numeric option\n");
                    return 1;
                } else if (endptr == optarg) {
                    printf("no digits were found\n");
                    return 1;
                }

                printf("verbose output level set to %i\n", vlevel);
                break;
            case 'o':   //output
                printf("output: %s\n", optarg);
                break;
            case '?':   //unknown
                if (optopt == 'o')
                    printf("Option -o requires an argument.\n");
                else if (isprint(optopt))
                    printf("Unknown option -%c.\n", optopt);
                else
                    printf("Unknown option character -%c [#%i].\n",
                            optopt, optopt);
                return 1;
            default:    //other
                return 1;

        }
    }

    return 0;
}
