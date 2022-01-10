#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <openssl/evp.h>
#include <unistd.h>

#define NUMBER_OF_COLUMNS 6
#define MAX_ROWS_AMOUNT 5
#define MAX_LENGTH_OF_EXPRESSION 33 // WITH "\n"

pthread_mutex_t lock;
pthread_cond_t password_found;

// THREAD 1 GENERATES PASSWORDS IN LOWERCASE, THREAD 2 IN UPPERCASE

// Structure modeling the concept of a word
typedef struct {
    char buffer[MAX_LENGTH_OF_EXPRESSION];
}word;

char main_buff_1 [MAX_LENGTH_OF_EXPRESSION]; // BUFFER TO WHICH THREAD1 WRITES
char main_buff_2 [MAX_LENGTH_OF_EXPRESSION]; //            -||- THREAD2
int stop;                                    // A VARIABLE CORRESPONDING TO THE ACTIVITIES OF MUTEX
word (* array) [NUMBER_OF_COLUMNS];          // USERS AND THEIR DATA BOARD

void bytes2md5(const char *data, int len, char *md5buf)
{
	EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
	const EVP_MD *md = EVP_md5();
	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_len, i;
    EVP_DigestInit_ex(mdctx, md, NULL);
	EVP_DigestUpdate(mdctx, data, len);
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
	EVP_MD_CTX_free(mdctx);
	for (i = 0; i < md_len; i++)
    {
	    snprintf(&(md5buf[i * 2]), 16 * 2, "%02x", md_value[i]);
	}
}

void compare(void* amount_of_rows_void, word passwords[14], word passwords_hash[14])
{
    long amount_of_rows = (long) amount_of_rows_void;
    int compare;

    for (int i = 0; i < 14; i++) 
    {   
        for(int j = 0; j <= amount_of_rows; j++)
        {   
            compare = strcmp(passwords_hash[i].buffer, array[1][j].buffer); 

            if (compare == 0) // checking password
            {   
                // pthread_mutex_unlock(&lock);
                while(stop == 1) // another thread has not yet serviced the previous leak
                {
                    usleep(100);    
                }

                strcpy(main_buff_1, passwords[i].buffer);
                strcpy(main_buff_2, array[2][j].buffer);

                //pthread_cond_signal(&password_found);
                stop = 1; // select the leak to handle
                // pthread_mutex_unlock(&lock);        
            }
        }             
    }
}

void* Thread_1(void* amount_of_rows_void)
{   
    // long amount_of_rows = (long) amount_of_rows_void;
    word passwords[14];
    FILE *in_dictionary = fopen("dictionary.txt", "r"); 
    word passwords_hash[14];
    char md5[33];

    for(int i = 0; i< 14; i++)
    {
        fscanf(in_dictionary, "%s", passwords[i].buffer);

        //printf("%s\n", passwords[i].buffer);

    }    

    for (int i = 0; i < 14; i++) 
    {   
        bytes2md5(passwords[i].buffer, strlen(passwords[i].buffer), md5);
        //printf("%s ======================> %s\n", passwords[i].buffer, md5);
        strcpy(passwords_hash[i].buffer, md5);                              
    } 

    compare(amount_of_rows_void, passwords, passwords_hash);

    fclose(in_dictionary);                
    pthread_exit(NULL);
}

void* Thread_2(void* amount_of_rows_void)
{   
    char md5[33];
    word passwords[14];
    FILE *in_dictionary = fopen("dictionary.txt", "r"); 
    word passwords_hash[14];

    for(int i = 0; i< 14; i++)
    {
        fscanf(in_dictionary, "%s", passwords[i].buffer);
        for (int k = 0; passwords[i].buffer[k]!='\0'; k++)
        {
            if(passwords[i].buffer[k] >= 'a' && passwords[i].buffer[k] <= 'z')
            {
                passwords[i].buffer[k] = passwords[i].buffer[k] - 32;
            }
        }            
        //printf("%s\n", passwords[i].buffer);
    }    

    for (int i = 0; i < 14; i++)
    {   
        bytes2md5(passwords[i].buffer, strlen(passwords[i].buffer), md5);
        //printf("%s ======================> %s\n", passwords[i].buffer, md5);
        strcpy(passwords_hash[i].buffer, md5);                                
    } 

    compare(amount_of_rows_void, passwords, passwords_hash);

    fclose(in_dictionary);                
    pthread_exit(NULL);
}

int main()
{   
    stop = 0; 

    memset(main_buff_1, 0, sizeof main_buff_1); // Set sizeof main_buff_1 bytes of main_buff_1 to 0 (CLEAR)
    memset(main_buff_2, 0, sizeof main_buff_2);  

    FILE *in_passwords_to_brake = fopen("passwords_to_brake.txt", "r"); 
    array = (word(*)[NUMBER_OF_COLUMNS]) malloc(NUMBER_OF_COLUMNS * MAX_ROWS_AMOUNT * sizeof(word));

    if(array == NULL)
    {
        printf("Error! memory not allocated.\n");
        return -1;
    }

    printf("******************************************\n");
    printf("Loading data from passwords to be cracked: \n");
    printf("******************************************\n");

    char character;
    int columns = 0;
    int rows = 0;
    character = fgetc(in_passwords_to_brake);
    
    while(character != EOF) // Read an array with user data
    {
        ungetc(character,in_passwords_to_brake);
        fscanf(in_passwords_to_brake, "%s", array[columns][rows].buffer);
        printf("%s \n", array[columns][rows].buffer/*, columns, rows*/); //printf("%s %d %d\n", array[columns][rows].buffer/*, columns, rows*/);
        columns++;
        character = fgetc(in_passwords_to_brake);
        if(character == '\n')
        {
            rows++;
            columns = 0;
            printf("\n");
        } 
    }

    pthread_t threads_id[2];

    long j = (long) rows;

    printf("Creating_thread #1\n");
    pthread_create(&threads_id[0],NULL,Thread_1,(void *)j);
    printf("Creating_thread #2\n");
    pthread_create(&threads_id[1],NULL,Thread_2,(void *)j);
   
    for(int i = 1; i<10000000; i++) // Simulate waiting for an interrupt
    {
        if(stop == 1) // There is a leak
        {
            // pthread_mutex_lock(&lock);
            // pthread_cond_wait(&password_found, &lock);

            printf("Password for %s is %s\n", main_buff_2, main_buff_1);
            memset(main_buff_1, 0, sizeof main_buff_1); 
            memset(main_buff_2, 0, sizeof main_buff_2);

            // pthread_mutex_unlock(&lock);
            stop = 0;
            usleep(10);     
        }
    }

    for(long i = 0; i<2; i++) // Connection of threads
    {
        pthread_join(threads_id[i], NULL);
        printf("The thread has already ended\n");
    }    

    pthread_exit(NULL);

    free(array);
    fclose(in_passwords_to_brake);
    array = NULL;    
    return 0;

}