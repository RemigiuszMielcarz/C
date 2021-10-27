
#include <stdio.h>
#include <stdlib.h>

struct element
{
    struct element *next;
    int data;             //wartosc elementu stosu
};

typedef struct element element; /*typedef stara_nazwa  nowa_nazwa;   <-----------------(NOWA NAZWA TO TERAZ element, (pomocnicze)*/

/* funkcja ta odpowiada za umieszczanie elementu w stosie */
void push(int v, element **S)
{
    element *e = malloc(sizeof(element)); /*   pom = (t_elem *)malloc(sizeof(t_elem)); ... utworz element ... */
    e->data = v;                          /*   do komorki dane z elementu e zapisujemy nowa podana wartosc  */
    e->next = *S;                         /*   zapisujemy do nowo stworzonego elementu adres elementu poprzedniego    */
    *S = e;                               /*   szczyt S zapisujemy nowo utworzony element              */
}

/* funkcja ta odpowiada za zdejmowanie elementu ze stosu */
void pop(element **S)
{
    if (*S)
    {
        element *e = *S; 
        *S = (*S)->next; 
        free(e);         /*Ostateczne kasowanie elementu ze zwalnianiem pamięci dynamicznej*/
    }
}

/* Funkcja pozwala na wyświetlenie na standardowym wyjściu elementów znajdujących się na nim */
void print(element *S)
{
    element *e = S;
    while (e)
    {
        printf("%d ", e->data);
        e = e->next;
    }
}

/* Funkcja która polega na inicjowaniu pustego stosu */
void inicjuj(element **S)
{
    *S = NULL;
}

int main()
{

    element *S; 
    inicjuj(&S);
    int blad;
    int wart1, wart2;
    char dana[100];
    while (1)
    {

        blad = scanf("%s", dana);

        if (dana[0] >= 48 && dana[0] <= 57) // sprawdza czy pierwszym elementem jest liczba <0,9> tablica ascii
        {
            sscanf(dana, "%d", &wart1);
            push(wart1, &S);
        }
        else
        {

            switch (dana[0])
            {
            case '+':
            {

                wart1 = S->data; // przypisanie do zmiennej wart1 wartości ze szczytu stosu
                pop(&S);
                if (!S)
                {
                    printf("Blad, brak liczb na stosie \n");
                    break;
                }
                wart2 = S->data;
                pop(&S);
                printf("wynik dodawania to %d \n", wart1 + wart2);
                push(wart1 + wart2, &S);
            }

            break;
            case '-':
                wart1 = S->data;
                pop(&S);
                if (!S)
                {
                    printf("Blad brak liczb na stosie \n");
                    break;
                }
                wart2 = S->data;
                pop(&S);
                printf("wynik odejmowania to %d \n", wart1 - wart2);
                push(wart1 - wart2, &S);
                break;
            case '*':
                wart1 = S->data;
                pop(&S);
                if (!S)
                {
                    printf("Blad brak liczb na stosie \n");
                    break;
                }
                wart2 = S->data;
                pop(&S);
                printf("wynik mnozenia to %d \n", wart1 * wart2);
                push(wart1 * wart2, &S);
                break;
            case '/':
                wart1 = S->data;
                pop(&S);
                if (!S)
                {
                    printf("Blad brak liczb na stosie \n");
                    break;
                }
                wart2 = S->data;
                if (wart2 == 0)
                {
                    printf("Blad, nie mozna dzielic przez 0 \n");
                    break;
                }
                pop(&S);
                printf("wynik dzielenia to %d \n", wart1 / wart2);
                push(wart1 / wart2, &S);
                break;
            case 'P':
                pop(&S);
                break;
            case 'f':
                if (!S)
                {
                    printf("Blad brak liczb na stosie \n");
                    break;
                }
                print(S);
                break;
            case 'p':
                printf("%d \n", S->data);
                break;
            case 'r': 
                /*if (!S);
                {
                    printf("Blad brak liczb na stosie \n");
                    break;
                }
                */
                wart1 = S->data;
                pop(&S);
               
                wart2 = S->data;
                pop(&S);
                push(wart1, &S);
                push(wart2, &S);
                break;
            case 'd':
                wart1 = S->data;
                push(wart1, &S);
                break;
            case 'c':
                while (S)
                    pop(&S);
                break;
            case 'q':
                return 0;
                break;
            }
        }
    }
}

/* 
1. P, który będzie służył usunięciu ostatnio wprowadzonej liczby i odpowiadał operacji pop, to znaczy usuwaniu argumentu ze szczytu stosu JEST
2. c (clear), który będzie „czyścił stos'', to znaczy usuwał z niego wszystkie elementy (takie operatory mogą być przydatne dla korekcji błędów popełnionych przy wpisywaniu danych). JEST
3. r (reverse) i powinien on spowodować zamianę miejscami dwóch argumentów na szczycie stosu. JEST
4. d (duplicate) ma spowodować zduplikowanie argumentu znajdującego się na szczycie stosu JEST
5. p (print) i jeśli pojawi się w strumieniu wejściowym, powinien spowodować wydrukowanie szczytu stosu JEST
6. f (full print), którego pojawienie się spowoduje wydrukowanie zawartości całego stosu argumentów. JEST
7. q będzie służył zakończeniu pracy programu JEST
*/

/* Sprawozdanie */
/* Remigiusz Mielcarz 06.01.2020r. 252887 */
/* Zaczynamy od gcc kal.c w terminalu */
/* Testy */
/* Najpierw będziemy testować podstawowe funkcje bez specjalnych przypadków, wszystkie po kolei. Uruchamiamy ./a.out

1. Zacznijmy od przetestowania dodawania.
remigiusz@remigiusz-Precision-7510:~/Pulpit/kalkulator$ ./a.out
4
5
+
wynik dodawania to 9 
Jak widzimy program nie kończy działania.

2. Teraz spróbujmy wyświetlić naszą liczbę poprzez wpisanie "p". Wyświetliła nam się liczba "9". Funkcja "p" działa poprawnie.
3. Spróbujmy usunąć naszą liczbę ze stosu poprzez wpisanie "P" oraz wyświetlmy nasz stos.

P
f
Blad brak liczb na stosie.

Jak widzimy nie wyświetlimy nic, ponieważ nie ma nic do wyświetlenia.

4. Spróbujmy wpisać trzy liczby np. 1,2,3 i na końcu wpisać "+"

1
2
3
+
wynik dodawania to 5 

Jak widzimy program działa tylko na 2 ostatnie liczby. Ale czy "1" jest zachowana w pamięci? Spróbujmy wyświetlić jeszcze raz wszystkie liczby "f".

f
5 1 

Funkcja "f" (full print) działa poprawnie. Przetestujmy wyświetlanie samego szczytu "p"

p
5

Działa poprawnie.

5. Spróbujmy zduplikować szczyt stosu "d"

d
f
5 5 1 

Działa poprawnie.

6. Spróbujmy wyczyścić cały stos "c"

c
f
Blad brak liczb na stosie 

Działa poprawnie.

7. Spróbujmy zamienić miejscami dwa argumenty na szczycie stosu. 

4
5
f
5 4 r
f
4 5 

Działa poprawnie.

8. Wiadomo, że nie można dzielić przez "0". Co się stanie gdy tak będziemy chcieli zrobić? Pamiętajmy, że ostatnia wpisana liczba do programu będzie naszczym szczytem <- to bardzo ważne.

0 
4 
/             <---------- = 4/0
Blad, nie mozna dzielic przez 0 
f
0 
Program nie zapamiętuje nam już tej "4".

9. Test zakończenia programu "q"

q
remigiusz@remigiusz-Precision-7510:~/Pulpit/kalkulator$ 

Działa. */

