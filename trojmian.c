/* 
    kompilacja: Sun C: cc -Xc trojmian.c -lm
                GNU C: gcc -pedantic -Wall trojmian.c -lm*/
#include <stdio.h>
#include <math.h>

int main() {
  float a,b,c,delta;

  printf("Program oblicza pierwiastki rownania w postaci\n");
  printf("     2\n");
  printf("  a x + b x +c =0\n");
  printf("Podaj wartosc a:");
  scanf("%f",&a);
  printf("Podaj wartosc b:");
  scanf("%f",&b);
  printf("Podaj wartosc c:");
  scanf("%f",&c);
  
  if (a==0.0)    /*przypadek rownania liniowego */
    if (b!=0.0) 
      printf("Jest to równanie liniowe o rozwiazaniu x=%f\n",-c/b);
    else  if (c==0.0)  /* oraz a==b==0.0 */
      printf("Rozwiazaniem jest dowolne x\n");
    else              /* a==b==0.0 != c  */
      printf("Brak rozwiazan\n");
  else {   /*przypadek rownania kwadratowego */
    delta=pow(b,2)-4.0*a*c;
    if (delta<0) 
      printf("Brak rozwiazan rzeczywistych\n");
    else            /* delta>=0 */
      if (delta>0) 
	printf("Rozwiazaniem sa x1=%f i x2=%f\n",(-b-sqrt(delta))/(2*a),(-b+sqrt(delta))/(2*a));
      else
      	printf("Rozwiazaniem sa x1=x2=%f\n",-b/(2*a));
  }
  return 0;

}
    /* Remigiusz Mielcarz, temat: Kompilacja programu sprawdzjącego rozwiązania funkcji kwadratowej, kod programu, testy programu, wnioski,  data wykonania: 28 października 2019r.*/

    /* KOMPILOWANIE */

    /* 1 */

    /*po wpisaniu komendy do kompilacji trojmian.c (cc trojmian.c) kompilacja nie powiodła się. Kompilator sygnalizuje, że błąd znajduje się w funkcji main (trojmian.c: In function 'main' :)
      nie posiadamy zakończenia programu: return 0;. Dopisujemy ją.*/

    /* 2 */

    /*po wpisaniu komendy do kompilacji trojmian.c (gcc -Wall -pedantic trojmian.c -lm(-Wall = wszystkie możliwe warningi, -pedantic = kod jest ściśle sprawdzany przed standardy ANSI C, -lm dołączenie biblioteki matematycznej))
    okazuje się komunikat:

    trojmian.c:13:3: warning: implicit declaration of function ‘print’; did you mean ‘lrint’? [-Wimplicit-function-declaration]
    print("Podaj wartosc a:");
    ^~~~~
    lrint
    trojmian.c:20:7: warning: suggest parentheses around assignment used as truth value [-Wparentheses]
    if (a=0.0)
           ^     
    trojmian.c:23:5: error: expected ‘;’ before ‘else’
    else  if (c==0.0) */

    /* co oznacza, że mamy warning przy "print" w linii trzynastej, jest to oczywiście literówka. Poprawiamy ją poprzez dopisanie do "print" literkę "f" na koniec tego słowa. 
       Jeśli już wpisaliśmy, możemy zapisać program: Ctrl-X Ctrl-S i ponownie skompilować. */

    /* 3 */

    /*Błąd występuje w linii 20, jest to błąd w warunku funkcji if, warunek ma za zadanie sprawdzenie czy a==0.0. Niestety tutaj błąd pojawia się poprzez pomylenie przypisania z porównaniem.
      Kod jednak niezależnie od ustawionej wartości "a" zawsze wyświetla, że liczba została odgadnięta. Jest to związane z faktem, że do porównywania należy zastosować operator porównania "==", a nie przypisania '='. 
      W tym pierwszym przypadku wartości są porównywane i zwracana jest wartość logiczna czy obie strony są takie same. W drugim przypadku '=' lewej stronie zostaje przypisana prawa.
      Następnie operator przypisania zwraca nową wartość lewej strony, a to z kolei jest konwertowana na wartość logiczną, gdzie 0 oznacza fałsz, a każda inna wartość prawdę. Trzeba dopisać zatem jeden znak "=".*/

    /* 4 */

    /*Następny błąd:

    trojmian.c:23:5: error: expected ‘;’ before ‘else’
    else  if (c==0.0) */

    /*Polega na tym, że w linii 23, na końcu linii 23 nie dodaliśmy średnika po funkcji printf (poza nawiasem) */

    /* TESTY */

    /* Program testujemy wpisując komende ./a.out po odpowiedzim skompilowaniu go. Do przetestowania mamy: 

    1. gdy a=0 b!=0 c!=0,
    powinniśmy mieć jedno rozwiązanie x=-c/b.
    Podajemy przykładowo liczby a=0 b=4 c=2
   
    Jest to równanie liniowe o rozwiazaniu x=-0.500000 (wszystko się zgadza)

    2. gdy a=0 b=0 c=0,
    powinniśmy otrzymać komunikat, że x należy do rzeczywistych.
   
    Rozwiazaniem jest dowolne x (zgadza się)

    3. gdy a=0 b!=0 c=0
    Mamy wtedy postać bx=0, gdy podzielimy przez b otrzymujemy x=0
    Wpisujemy a=0 b=3 c=0
    powinniśmy otrzymać komunikat, że jest jedno rozwiązanie x=0

    Jest to równanie liniowe o rozwiazaniu x=-0.000000 (zgadza się)

    4. gdy a=0 b=0 c!=0
    Powinniśmy otrzymać komunikat o braku rozwiązań
    Wpisujemy a=0 b=0 c=4

    Brak rozwiazan (zgadza się)
    
    5. Gdy delta<0
    Powinniśmy otrzymać komunikat o braku rozwiązań rzeczywistych
    Wpiszemy np. a=3 b=6 c=9

    remigiusz@remigiusz-Precision-7510:~/PWR$ ./a.out
    Program oblicza pierwiastki rownania w postaci
        2
     a x + b x +c =0
     Podaj wartosc a:3
     Podaj wartosc b:6
     Podaj wartosc c:9
     Brak rozwiazan rzeczywistych (zgadza się)

     6. Gdy delta>0
     Wpiszmy np. a=1 b=6 c=5

     remigiusz@remigiusz-Precision-7510:~/PWR$ ./a.out
     Program oblicza pierwiastki rownania w postaci
        2
     a x + b x +c =0
     Podaj wartosc a:1
     Podaj wartosc b:6
     Podaj wartosc c:5
     Rozwiazaniem sa x1=-5.000000 i x2=-1.000000 (zgadza się)

     7. Gdy delta=0
     Wpiszmy np. a=1 b=6 c=9 (tak aby delta = 0)
     remigiusz@remigiusz-Precision-7510:~/PWR$ ./a.out
     Program oblicza pierwiastki rownania w postaci
        2
     a x + b x +c =0
     Podaj wartosc a:1
     Podaj wartosc b:6
     Podaj wartosc c:9
     Rozwiazaniem sa x1=x2=-3.000000 (zgadza się) */

     /* WNIOSKI */

     /* Program jest skompilowany poprawnie, brak komunikatów o błędach, kod uzupełniony, brak błędów w testach, wszystkie potrzebne 7 przypadków zostały przetestowane,
	jedyne zastrzeżenie to interpretacja w teście nr. 7 zdania "Rozwiazaniem sa x1=x2=-3.000000", moim zdaniem
	powinno być "Rozwiazaniem jest podwójny pierwiastek x = -3.000000".*/







    









