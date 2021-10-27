#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "pliki.h"
#include "przetwarzanie.h"
#include <assert.h>
#define W_OK 0                /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1 /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY -2
#define B_BRAKWARTOSCI -3
#define B_BRAKPLIKU -4
#define MAX 512       /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024 /* Dlugosc buforow pomocniczych */
#define LINIE 70

/* Czytaj */

/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	     *
 *										                                             *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			             *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		             *
 * \param[out] obrazek->wymx szerokosc obrazka						                 *
 * \param[out] obrazek->wymy wysokosc obrazka						                 *
 * \param[out] obrazek->szarosci liczba odcieni obrazek->szarosci					 *
 * \return liczba wczytanych pikseli						                         *
 ************************************************************************************/

int przetwarzaj_opcje(int argc, char **argv)
{
  int i, prog, biel, czern;
  ob obrazek;
  char *nazwa_pliku_we, *nazwa_pliku_wy;

  FILE *plik;
  char nazwa[100];

  for (i = 1; i < argc; i++)
  {
    switch (argv[i][1]) //konkretny znak ze slowa
    {
    case 'h':
    {
      printf(" komenda musi zaiwerac opcje -o oraz - i \n");
      printf(" -i [nazwa] -wczytaj : \n");
      printf(" -o [nazwa]-zapisz : \n");
      printf(" -p [prog] -progowanie : \n");
      printf(" -n -negatyw : \n");
      printf(" -k -konturowanie : \n");
      printf(" -r -rozmycie : \n");
      printf(" -d -wyświetl : \n");
      printf(" -z [czern] [biel] -zmiana poziomów : \n");
    }
    }
  }

  for (i = 1; i < argc; i++)
  {
    switch (argv[i][1])
    {
    case 'i':
    {
      if (++i < argc)
      {
        nazwa_pliku_we = argv[i];
        if (nazwa_pliku_we[0] == '-')
        {

          printf("Podaj nazwe pliku:\n");
          scanf("%s", nazwa); /// nazwa   ===== &nazwa[0]
          plik = fopen(nazwa, "r");

          if (plik != NULL)
          {
            czytaj(plik, &obrazek);
            fclose(plik);
          }
        }
        else
        {
          plik = fopen(nazwa_pliku_we, "r");
          if (plik != NULL)
          {
            czytaj(plik, &obrazek);
            fclose(plik);
          }
          else
          {
            return B_BRAKNAZWY;
          }
        }
      }
      else
        return B_BRAKNAZWY;
      break;
    }
    }
  }

  //na pocztaku konwertujemy na szarosci zanim zrobimy inne opcje ///
  for (i = 1; i < argc; i++)
  {
    switch (argv[i][1])
    {
    case 's':
    {
      konwersja(&obrazek);
    }
    }
  }

  for (i = 1; i < argc; i++)
  {
    if (argv[i][0] != '-')
      return B_NIEPOPRAWNAOPCJA;
    switch (argv[i][1])
    {

    case 'i':
    {
      if (++i < argc) // -n -i
      {
        nazwa_pliku_we = argv[i];
        if (nazwa_pliku_we[0] == '-')
        {

          i--;
        }
      }
    }

    break;

    case 'o':
    {
      if (++i < argc)
      {
        nazwa_pliku_we = argv[i];
        if (nazwa_pliku_we[0] == '-')
        {

          i--;
        }
      }
    }

    break;

    case 'p':
    {
      if (obrazek.znak == '2')
      {
        if (++i < argc)
        {
          if (sscanf(argv[i], "%d", &prog) == 1)
          {
            progowanie(&obrazek, prog);
          }
          else
            return B_BRAKWARTOSCI;
        }
        else
          return B_BRAKWARTOSCI;
      }
      break;
    }
    case 'z':
    {
      if (obrazek.znak == '2')
      {
        if (++i < argc)
        {
          if (sscanf(argv[i], "%d", &biel) == 1)
          {
            if (++i < argc)
            {
              if (sscanf(argv[i], "%d", &czern) == 1)
              {
                zmiana(&obrazek, czern, biel);
              }
              else
                return B_BRAKWARTOSCI;
            }
            else
              return B_BRAKWARTOSCI;
          }
        }
        else
          return B_BRAKWARTOSCI;
      }
      else
        return B_BRAKWARTOSCI;
    }
    break;

    case 'n':
    {
      if (obrazek.znak == '2')
        negatyw(&obrazek);
      break;
    }
    case 'k':
    {
      if (obrazek.znak == '2')
        konturowanie(&obrazek);
      break;
    }
    case 'r':
    {
      if (obrazek.znak == '2')
        rozmycie(&obrazek);
      break;
    }
    case 'd':
    {
      wyswietl(nazwa);
      break;
    }
    }
  }

  for (i = 1; i < argc; i++)
  {
    switch (argv[i][1])
    {
    case 'o':
    {
      if (++i < argc)
      {
        nazwa_pliku_wy = argv[i];
        if (nazwa_pliku_we[0] == '-')
        {
          printf("Podaj nazwe pliku:\n");
          scanf("%s", nazwa); /// nazwa   ===== &nazwa[0]
          plik = fopen(nazwa, "w");
          zapisz(plik, obrazek);

          fclose(plik);
        }
        else
        {
          plik = fopen(nazwa_pliku_wy, "w");
          if (plik != NULL)
          {
            zapisz(plik, obrazek);
            fclose(plik);
          }
          else
            return B_BRAKNAZWY;
        }
      }
      else
        return B_BRAKNAZWY;
      break;
    }
    }
  }

  if (plik != NULL)
    return W_OK;
  else
    return B_BRAKPLIKU; /* blad:  nie otwarto pliku wejsciowego  */
}
/*
./a.out -n  -o xcvvvvvvv -s -i 3.ppm 
argv  ./a.out -i 3.ppm -s -o xcvvvvvvv
argv[1] -i
argv[1][1] i
*/
int main(int argc, char **argv)
{

  int odczytano = 0;
  odczytano = przetwarzaj_opcje(argc, argv);
  if (odczytano != 0)
  {
    printf(" komenda musi zawierac opcje -o oraz - i \n");
    printf(" -i [nazwa] -wczytaj : \n");
    printf(" -o [nazwa]-zapisz : \n");
    printf(" -p [prog] -progowanie : \n");
    printf(" -n -negatyw : \n");
    printf(" -k -konturowanie : \n");
    printf(" -r -rozmycie : \n");
    printf(" -d -wyświetl : \n");
    printf(" -z [czern] [biel] -zmiana poziomów : \n");
    printf(" -s -konwersja : \n");
  }
  printf("%d \n", odczytano);
  return odczytano;
}

/* Sprawozdanie
/* Remigiusz Mielcarz 252887 24.12.2019r. Przetwarzanie obrazów 2.
/* Zaczynamy od kompilowania: gcc obraz.h pliki.c pliki.h przetwarzanie.c przetwarzanie.h przetwobraz2.c
Będziemy operować na dwóch małych obrazach aby pokazać część wyników:
------------------------------------------------------------------
Pierwszy z nich to feep.pgm:
P2
# feep.ascii.pgm
24 7
15
0 0  0  0  0  0  0  0  0 0  0  0  0  0  0  0  0 0  0  0  0  0  0  0
0 3  3  3  3  0  0  7  7 7  7  0  0 11 11 11 11 0  0 15 15 15 15  0
0 3  0  0  0  0  0  7  0 0  0  0  0 11  0  0  0 0  0 15  0  0 15  0
0 3  3  3  0  0  0  7  7 7  0  0  0 11 11 11  0 0  0 15 15 15 15  0
0 3  0  0  0  0  0  7  0 0  0  0  0 11  0  0  0 0  0 15  0  0  0  0
0 3  0  0  0  0  0  7  7 7  7  0  0 11 11 11 11 0  0 15  0  0  0  0
0 0  0  0  0  0  0  0  0 0  0  0  0  0  0  0  0 0  0  0  0  0  0  0
-------------------------------------------------------------------
Drugi z nich to 4.ppm:
P3
# example from the man page
4 4
15
 0  0  0    0  0  0    0  0  0   15  0 15
 0  0  0    0 15  7    0  0  0    0  0  0
 0  0  0    0  0  0    0 15  7    0  0  0
15  0 15    0  0  0    0  0  0    0  0  0
-------------------------------------------------------------------
Aby sprawdzić poprawność programu możemy przeprowadzić testy dla obu obrazów
1. Wczytywanie.
Wpisujemy w konsolę ./a.out -i feep.pgm lub ./a.out -i 4.ppm
Okazuje nam się komunikat 0, jest on równoznaczny z brakiem błędów, tak jak na początku pliku przetwobraz2.c zostało to zdefiniowane.
Obraz wczytał się poprawnie.
Jest także inny sposób na wczytanie obrazu. Gdy wpiszemy "./a.out -i -" wyświetla nam się:

remigiusz@remigiusz-Precision-7510:~/Pulpit/przetwobraz2$ ./a.out -i -
Podaj nazwe pliku:
feep.pgm
0 

Musieliśmy podać ręcznie nazwę pliku.

Co się stanie gdy wpiszemy samo ./a.out -i?

remigiusz@remigiusz-Precision-7510:~/Pulpit/przetwobraz2$ ./a.out -i
 komenda musi zaiwerac opcje -o oraz - i 
 -i [nazwa] -wczytaj : 
 -o [nazwa]-zapisz : 
 -p [prog] -progowanie : 
 -n -negatyw : `
 -k -konturowanie : 
 -r -rozmycie : 
 -d -wyświetl : 
 -z [czern] [biel] -zmiana poziomów :
 -s -konwersja :

-2 

Jest to bardzo przydatne. Na końcu zostało wyświetlone "-2" co oznacza brak nazwy. Powinniśmy wpisać nazwę obrazu po -i.

2. Pomoc
Żeby ukazała nam się pomoc wpisujemy ./a.out -h

3. Wczytanie i zapisanie pod inną nazwą:
./a.out -i feep.pgm -o cokolwiek.pgm
Działa

4. Progowanie
./a.out -i feep.pgm -p 20 -o cokolwiek1.pgm

P2
24 7
15
0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	15	15	15	15	0	0	15	15	15	15	0	0	15	15	15	15	0	0	0	0	0	0	0	0	15	0	0	0	0	0	15	0	0	0	0	0	15	0	0	
15	0	0	0	0	0	0	0	0	15	15	15	0	0	0	15	15	15	0	0	0	15	15	15	15	0	0	0	0	0	0	0	0	15	0	0	0	0	0	15	0	0	0	0	0	15	0	0	0	0	0	0	0	0	0	0	0	15	15	15	15	0	0	15	15	15	15	0	0	15	
0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	
Działa

5. Negatyw
./a.out -i feep.pgm -n -o cokolwiek2.pgm
P2
24 7
15
15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	12	12	12	12	15	15	8	8	8	8	15	15	4	4	4	4	15	15	0	0	0	0	15	15	12	15	15	15	15	15	8	15	15	15	15	15	4	15	15	15	15	15	0	15	15	
0	15	15	12	12	12	15	15	15	8	8	8	15	15	15	4	4	4	15	15	15	0	0	0	0	15	15	12	15	15	15	15	15	8	15	15	15	15	15	4	15	15	15	15	15	0	15	15	15	15	15	12	15	15	15	15	15	8	8	8	8	15	15	4	4	4	4	15	15	0	
15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	
Działa

6. Konturowanie
./a.out -i feep.pgm -k -o cokolwiek3.pgm
P2
24 7
15
0	3	3	3	3	0	0	7	7	7	7	0	0	11	11	11	11	0	0	15	15	15	15	0	3	0	3	3	6	0	7	0	7	7	14	0	11	0	11	11	22	0	15	0	15	15	15	0	3	3	3	3	0	0	7	7	7	7	0	0	11	11	11	11	0	0	15	15	15	30	
15	0	3	0	3	6	0	0	7	0	7	14	0	0	11	0	11	22	0	0	15	0	15	15	30	0	3	3	0	0	0	0	7	7	7	7	7	0	11	11	11	11	11	0	15	15	0	0	0	0	3	6	0	0	0	0	7	7	7	7	14	0	11	11	11	11	22	0	15	30	
0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	
Działa

7. Rozmycie
./a.out -i feep.pgm -r -o cokolwiek4.pgm
Działą

8. Wyswietlenie
./a.out -i feep.pgm -d
Działa

9. Zmiana poziomów
./a.out -i feep.pgm -z 90 20 -o cokolwiek5.pgm
P2
24 7
15
0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	15	15	15	15	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	15	0	0	
15	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	15	15	15	15	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	15	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	15	
0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	
Działa

10. Kilka operacji naraz

remigiusz@remigiusz-Precision-7510:~/Pulpit/przetwobraz2$ ./a.out -i feep.pgm -p 20 -n -k -o cokolwiek7.pgm
0 

P2
24 7
15
0	0	0	0	0	0	0	15	15	15	15	0	0	15	15	15	15	0	0	15	15	15	15	15	0	0	0	0	0	0	15	0	15	15	30	0	15	0	15	15	30	0	15	0	15	15	15	15	0	0	0	0	0	0	15	15	15	15	0	0	15	15	15	15	0	0	15	15	15	30	
15	15	0	0	0	0	0	0	15	0	15	30	0	0	15	0	15	30	0	0	15	0	15	15	30	15	0	0	0	0	0	0	15	15	15	15	15	0	15	15	15	15	15	0	15	15	0	0	0	15	0	0	0	0	0	0	15	15	15	15	30	0	15	15	15	15	30	0	15	30	
0	0	0	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	15	
Działa.

11. Konwersja
./a.out -i 4.ppm -s -o nowy.ppm
P2
4 4
15
0	0	0	10	0	7	0	0	0	0	7	0	10	0	0	0	
Działa

12. Konwersja na końcu, a na początku negatyw - co się stanie?

P2
4 4
15
15	15	15	5	15	8	15	15	15	15	8	15	5	15	15	15	

Na początku wykonała się konwersja, potem negatyw
*/


