
#include "przetwarzanie.h"

/* Negatyw */
void negatyw(ob *obrazek)
{
  int i;
  int j;
  for (i = 0; i < obrazek->wymy; i++)
    for (j = 0; j < obrazek->wymx; j++)
      obrazek->obraz_pgm[i][j] = obrazek->szarosci - obrazek->obraz_pgm[i][j];
}

/* Progowanie */
int progowanie(ob *obrazek, int prog)
{

  int i;
  int j;
  if (prog < 0 || prog > 100)
  {
    fprintf(stderr, "Prog musi byc w zakresie (0,100)\n");
    return 0;
  }
  else
  {
    prog = obrazek->szarosci * prog / 100.0;
    for (i = 0; i < obrazek->wymy; i++)
      for (j = 0; j < obrazek->wymx; j++)
        if (obrazek->obraz_pgm[i][j] <= prog)
          obrazek->obraz_pgm[i][j] = 0;
        else
          obrazek->obraz_pgm[i][j] = obrazek->szarosci;
  }
  return 1;
}

/* Konturowanie */
void konturowanie(ob *obrazek)
{
  int i;
  int j;

  for (i = 0; i < obrazek->wymy - 1; i++)
    for (j = 0; j < obrazek->wymx - 1; j++)
      obrazek->obraz_pgm[i][j] = abs(obrazek->obraz_pgm[i + 1][j] - obrazek->obraz_pgm[i][j]) + abs(obrazek->obraz_pgm[i][j + 1] - obrazek->obraz_pgm[i][j]);
}

/* Rozmycie poziome */
void rozmycie(ob *obrazek)
{
  int i;
  int j;
  int tab_tmp[MAX][MAX];

  for (i = 0; i < obrazek->wymy; i++)
    for (j = 0; j < obrazek->wymx; j++)
    {
      tab_tmp[i][j] = obrazek->obraz_pgm[i][j];
    }

  for (i = 1; i < obrazek->wymy - 1; i++)
    for (j = 0; j < obrazek->wymx; j++)
    {
      obrazek->obraz_pgm[i][j] = ((tab_tmp[i - 1][j] + tab_tmp[i][j] + tab_tmp[i + 1][j])) / 3.0;
    }
}

/* Zmiana */
int zmiana(ob *obrazek, int biel, int czern)
{

  int i;
  int j;
  if (czern < biel && czern >= 0 && biel <= 100)
  {
    fprintf(stderr, "Nieprawidlowe dane!\n");
    return 0;
  }
  else
  {
    czern = obrazek->szarosci * czern / 100.0;
    biel = obrazek->szarosci * biel / 100.0;
    for (i = 0; i < obrazek->wymy; i++)
      for (j = 0; j < obrazek->wymx; j++)
        if (obrazek->obraz_pgm[i][j] <= czern)
          obrazek->obraz_pgm[i][j] = 0;
        else if (czern < obrazek->obraz_pgm[i][j] && obrazek->obraz_pgm[i][j] < biel)
          obrazek->obraz_pgm[i][j] = (obrazek->obraz_pgm[i][j] - czern) * obrazek->szarosci / (biel - czern);
        else
          obrazek->obraz_pgm[i][j] = obrazek->szarosci;
  }
  return 1;
}

/* Konwersja */
void konwersja(ob *obrazek)
{
  int i;
  int j;

  obrazek->obraz_pgm = (int**)malloc(obrazek->wymy * sizeof(int *));
  for (i = 0; i < obrazek->wymy; i++)
    obrazek->obraz_pgm[i] = (int*)malloc(obrazek->wymx * sizeof(int));

  obrazek->znak = '2';

  for (i = 0; i < obrazek->wymy; i++)
    for (j = 0; j < obrazek->wymx; j++)
      obrazek->obraz_pgm[i][j] = (obrazek->obrazr[i][j] + obrazek->obrazg[i][j] + obrazek->obrazb[i][j]) / 3.0;
}