#include "pliki.h"

int czytaj(FILE *plik_we, ob *obrazek)
{
  char buf[DL_LINII]; /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;           /* zmienna pomocnicza do czytania komentarzy */
  int koniec = 0;     /* czy napotkano koniec danych w pliku */
  int i, j;

  /*Sprawdzenie czy podano prawidlowy uchwyt pliku */
  if (plik_we == NULL)
  {
    fprintf(stderr, "Blad: Nie podano uchwytu do pliku\n");
    return (0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien byæ P2 */
  if (fgets(buf, DL_LINII, plik_we) == NULL) /* Wczytanie pierwszej linii pliku do bufora */
    koniec = 1;                              /* Nie udalo sie? Koniec danych! */

  if ((buf[0] != 'P') || (buf[1] != '2' && buf[1] != '3') || koniec)
  { /* Czy jest magiczne "P2" lub "P3"? */
    fprintf(stderr, "Blad: To nie jest plik PGM ani PPM\n");
    return (0);
  }

  obrazek->znak = buf[1];

  /* Pominiecie komentarzy */
  do
  {
    if ((znak = fgetc(plik_we)) == '#')
    {                                            /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf, DL_LINII, plik_we) == NULL) /* Przeczytaj ja do bufora                */
        koniec = 1;                              /* Zapamietaj ewentualny koniec danych */
    }
    else
    {
      ungetc(znak, plik_we);        /* Gdy przeczytany znak z poczatku linii */
    }                               /* nie jest '#' zwroc go                 */
  } while (znak == '#' && !koniec); /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we, "%d %d %d", &obrazek->wymx, &obrazek->wymy, &obrazek->szarosci) != 3)
  {
    fprintf(stderr, "Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return (0);
  }
  if (obrazek->znak == '2')
  {
    obrazek->obraz_pgm = (int**)malloc(obrazek->wymy * sizeof(int *));
    for (i = 0; i < obrazek->wymy; i++)
      obrazek->obraz_pgm[i] = (int*)malloc(obrazek->wymx * sizeof(int));

    /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
    for (i = 0; i < obrazek->wymy; i++)
    {
      for (j = 0; j < obrazek->wymx; j++)
      {
        if (fscanf(plik_we, "%d", &(obrazek->obraz_pgm[i][j])) != 1)
        {
          fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\n");
          return (0);
        }
      }
    }
  }else
  {
        obrazek->obrazr = malloc(obrazek->wymy * sizeof(int *));
    for (i = 0; i < obrazek->wymy; i++)
      obrazek->obrazr[i] = malloc(obrazek->wymx * sizeof(int));

       obrazek->obrazg = malloc(obrazek->wymy * sizeof(int *));
    for (i = 0; i < obrazek->wymy; i++)
      obrazek->obrazg[i] = malloc(obrazek->wymx * sizeof(int));

        obrazek->obrazb = malloc(obrazek->wymy * sizeof(int *));
    for (i = 0; i < obrazek->wymy; i++)
      obrazek->obrazb[i] = malloc(obrazek->wymx * sizeof(int));

    /* Pobranie obrazu i zapisanie w tablicy*/
    for (i = 0; i < obrazek->wymy; i++)
    {
      for (j = 0; j < obrazek->wymx; j++)
      {
        if (fscanf(plik_we, "%d %d %d", &(obrazek->obrazr[i][j]), &(obrazek->obrazg[i][j]), &(obrazek->obrazb[i][j])) != 3)
        {
          fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\n");
          return (0);
        }
      }
    }
  }
  
  return obrazek->wymx * obrazek->wymy; /* Czytanie zakonczone sukcesem    */
} /* Zwroc liczbe wczytanych pikseli */

/* Zapisz */

int zapisz(FILE *plik_wy, ob obrazek)
{
  int i;
  int j;

  int n = 0; /* Licznik znakow w linii */
if (obrazek.znak == '2')
{
  fprintf(plik_wy, "P2\n%d %d\n%d\n", obrazek.wymx, obrazek.wymy, obrazek.szarosci);

  for (i = 0; i < obrazek.wymy; i++)
  {
    for (j = 0; j < obrazek.wymx; j++)
    {
      fprintf(plik_wy, "%d\t", obrazek.obraz_pgm[i][j]); /* Przepisywanie wartosci z tablicy w programie do pliku */
      n++;
      if (n % LINIE == 0)
      {
        fprintf(plik_wy, "\n"); /* Nowa linia pomocnicza - wygoda */
        n = 0;
      }
    }
  }
}
else
{
    fprintf(plik_wy, "P3\n%d %d\n%d\n", obrazek.wymx, obrazek.wymy, obrazek.szarosci);

  for (i = 0; i < obrazek.wymy; i++)
  {
    for (j = 0; j < obrazek.wymx; j++)
    {
      fprintf(plik_wy, "%d\t%d\t%d\t", obrazek.obrazr[i][j], obrazek.obrazg[i][j], obrazek.obrazb[i][j]); /* Przepisywanie wartosci z tablicy w programie do pliku */
      n++;
      if (n % LINIE == 0)
      {
        fprintf(plik_wy, "\n"); /* Nowa linia pomocnicza - wygoda */
        n = 0;
      }
    }
  }
}

  return 0;
}

/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku)
{
  char polecenie[DL_LINII]; /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie, "display "); /* konstrukcja polecenia postaci */
  strcat(polecenie, n_pliku);    /* display "nazwa_pliku" &       */
  strcat(polecenie, " &");
  printf("%s\n", polecenie); /* wydruk kontrolny polecenia */
  system(polecenie);         /* wykonanie polecenia        */
}
