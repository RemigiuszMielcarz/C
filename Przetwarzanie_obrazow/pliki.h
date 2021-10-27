#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "obraz.h"
#define MAX 512       /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024 /* Dlugosc buforow pomocniczych */
#define LINIE 70



int czytaj(FILE *plik_we, ob *obrazek);
int zapisz(FILE *plik_wy, ob obrazek);
void wyswietl(char *n_pliku);
