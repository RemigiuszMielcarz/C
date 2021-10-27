/*Remigiusz Mielcarz, 252887, Przeciecia zera, 29.10.2019r.*/
#include <stdio.h>

#define DATA_END       99 /*Koniec danych*/
#define VALUE_MINIMUM -10 /*Wartosc minimalna danych*/
#define VALUE_MAXIMUM  10 /*Wartosc maksymalna danych*/
#define FREQ_MIN       8  /*Dolna granica czestotliwosci przeciec*/
#define FREQ_MAX       14 /*Gorna granica czestotliwosci przeciec*/

int main()
{
  float aktualna=0;
  float poprzednia=0;
  int l_przeciec=0;
  int l_danych=0;
  while(aktualna != DATA_END) //dopóki aktualna nie jest końcem danych
    {
      while (!(aktualna == DATA_END || l_danych == DATA_END)) //dopóki aktualna nie równa się końcowi danych i liczba danych nie jest końcem danych
	{
	  scanf("%f",&aktualna); //pobieranie wartosci aktualnej
	  l_danych++;            //zwiekszenie o 1 liczby danych
	  if ((aktualna >= VALUE_MINIMUM) && (aktualna <= VALUE_MAXIMUM) && (aktualna != 0)) //jesli aktualna zawiera sie w przedziale wartosci danych <-10,10> i aktualna jest różna od 0
	    {
	      if(aktualna*poprzednia<0) //jeśli aktualna*poprzednia jest liczba ujemna
		{
		  l_przeciec++;         //zwiekszenie liczby przeciec o 1
		}
	      poprzednia=aktualna;
	    }
	}

  

      if(l_przeciec >= FREQ_MIN && l_przeciec <= FREQ_MAX) //jesli l_przeciec znajduje sie w przedziale <-8,14>
	printf("\n%d OK\n", l_przeciec);                   //wyswietla liczbe przeciec, komunikat OK z przejsciem do nowej linii
      else                                                 //jesli nie znajduje sie w przedziale <-8,14> 
	printf("\n%d Nie OK\n", l_przeciec);               //wyswietla l_przeciec i komunikat Nie OK z przejsciem do nowej linii

      l_danych=0; //wyzerowanie liczby danych i liczby przeciec, poprzedniej liczby
      l_przeciec=0;

      poprzednia=0;

	

    }
  
}

/* Kompilacja powiodła się, brak błęðw, możemy przejść do testów.*/

/* TESTY */

/* Po skompilowaniu programu gcc zera.c możemy uruchomić nasz program komendą ./a.out. Ciągłe dopisywanie kolejnych komentarzy zostało zastosowane dla czytelności (dostrzegania kolejnych testów) */

/* Test nr: 1; zwykłe wartości:

   1.00 -1.00 1.00 -1.00 99 

   Komunikat: 3 Nie OK
   Jest to prawda, przecięcie następuje między 1.00 a -1.00, następnie między -1.00 a 1.00, potem miedzy 1.00 a -1.00. Komunikat 3 Nie OK oznacza 3 przecięcia zera, Nie OK dlatego, że l. przeciec nie zawiera się między <-8,14>
   Program nie zalicza przecięcia zera między -1.00 a 99*/

/*  Test nr: 2; sprawdzenie częstotliwości

    remigiusz@remigiusz-Precision-7510:~/PWR$ ./a.out
    -1 1 -1 1 -1 1 -1 1 -1 1 99                         

    9 OK

    Poprawnie przebiegł test. /*

/* Test nr: 3; jak zachowuje się gdy jest 0 pomiędzy liczbą ujemną i dodatnią

   remigiusz@remigiusz-Precision-7510:~/PWR$ ./a.out
   1 0 -1 -1 0 1 99

   2 Nie OK

   Poprawnie przebiegł test. /*

 /* Test nr: 4; Co się stanie jeśli napiszemy tylko liczbę 99?

    0 Nie OK

    Prawda, nie ma przecięć, program kończy działanie*/

/* Test nr: 5; Co jesli strumien danych nie jest zakonczony 99?

    remigiusz@remigiusz-Precision-7510:~/PWR$ ./a.out
    1.00 -1.00 1.00 1.00

    2 Nie OK

    Brak zakończenia pracy programu, żeby otrzymać wynik przytrzymujemy Ctrl+D i wtedy program stopuje lub koniec programu następuje po wciśnięciu Ctrl+C*/

/* Test nr: 6; Litery jako dane

   a b c d 99                                                                                                                                   
   (program nie konczy dzialania(pętla w nieskończoność), zachowuje sie jak przy braku "99" na koncu pliku)                                                             
   Brak uwzglednienia takiego przypadku w algorytmie*/

/* Test nr. 7; Znaki specjalne

   Ten sam wynik jak w teście nr: 6*/

/* Test nr. 8; sprawdzenie pliku przeciecia_zera1.txt (po wpisaniu komend:
   1. cat przeciecia_zera1.txt | cut -d ' ' -f 2 >dane.txt
   2. Sprawdzamy: cat dane.txt
   3. gcc zera.c
   4. ./a.out <dane.txt

   remigiusz@remigiusz-Precision-7510:~/PWR$ ./a.out <dane.txt

   11 OK

   5 Nie OK

   10 OK

   12 OK

   12 OK

   12 OK

   12 OK

   13 OK

   18 Nie OK

   11 OK

   1 Nie OK

   Test przebiegł poprawnie.*/

/* Test nr. 9; sprawdzenie odbicia względem 0

   Sprawdźmy odbicie wpisując cyfry -1.00 0.00 -2.00

   -1.00 0.00 -2.00

   0 Nie OK

   Prawda, następuje tylko odbicie, przecięcia nie ma.*/

/* Test nr. 10; Co się stanie gdy są dwa zera pomiędzy wartościa ujemną i dodatnią

   remigiusz@remigiusz-Precision-7510:~/PWR$ ./a.out
   
   -1.00 0.00 0.00 2.00

   1 Nie OK

   Prawda, następuje przecięcie, 0 jest pomijane.*/

/* Wnioski: Program działa tak jak powinien, wszystkie warunki zostały poprawnie zrealizowane. Brak w specyfikacji przypadków liter / znaków specjalnych, wtedy program wykonuje się w nieskończoność, kończymy działanie Ctrl+C*/







    

   




  
   









