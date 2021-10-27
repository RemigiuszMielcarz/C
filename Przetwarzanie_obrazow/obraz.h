#ifndef OBRAZ_H
#define OBRAZ_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


#define MAX 512       /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024 /* Dlugosc buforow pomocniczych */
#define LINIE 70

struct obraz 
{
    char znak;
    int wymx;
    int wymy;
    int szarosci;
    int **obraz_pgm;
    int **obrazr;
    int **obrazg;
    int **obrazb;
};

typedef struct obraz ob;

#endif

