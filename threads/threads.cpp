/*-----------------------------------------------------------------------------------------------
-- FUNCTION:   Main
--
-- DATE:       January 17 2018
--
-- DESIGNER:   Benedict Lo
--
-- PROGRAMMER: Benedict Lo
--
-- INTERFACE:  main()
--
-- PARAMETER:  int argc, char *argv[]
--
-- RETURNS:    int
--
-- Notes:      Creates threads per argument that is added and decomposes each
               Prime number
--
----------------------------------------------------------------------------------------------- */
#include "primedecompose.h"
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


using namespace std;

// uses the GMP (GNU Multiple Precision Library for the computations
//gcc -Wall -o pdec primedec.c primedecompose.c -lgmp

#define MAX_FACTORS	1024
#define MAX_THREADS 6

void *Start(void *arg);

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct{
    FILE* fd;
    int a;
    char **val;
}ThreadInfo;

int main(int argc, char *argv[]){
    int i,k;
    pthread_t tid[MAX_THREADS];
    ThreadInfo *PrimeInfo = (ThreadInfo*)malloc(sizeof(ThreadInfo));
    if(argc != 6){
			puts("Usage: ./pdec <number to be factored>");
			return EXIT_SUCCESS;
	}
    FILE *fp;
    fp = fopen("threads.txt","w");
	for(i = 1; i < argc; i++){
        PrimeInfo->a = i;
        PrimeInfo->fd = fp;
        PrimeInfo->val = argv;
	    if(pthread_create(&tid[i], NULL, Start,(void*) PrimeInfo) != 0){
            cout << "Error making thread" << endl;
            break;
        }
	}
	for(k = 1; k < argc; k++){
        pthread_join(tid[k],NULL);
    }
  	return EXIT_SUCCESS;

    }
    /*-----------------------------------------------------------------------------------------------
    -- FUNCTION:   *Start
    --
    -- DATE:       January 17 2018
    --
    -- DESIGNER:   Benedict Lo
    --
    -- PROGRAMMER: Benedict Lo
    --
    -- INTERFACE:  main()
    --
    -- PARAMETER:  void*arg
    --
    -- RETURNS:    void
    --
    -- Notes:      Starts each prime decompostion and creates a new thread per call
    --
    ----------------------------------------------------------------------------------------------- */
void *Start(void *arg){
    mpz_t dest[MAX_FACTORS];
    ThreadInfo *Prime = (ThreadInfo *)arg;
    mpz_t n;
    int i, k;
    struct timeval stop, start;
  	gettimeofday(&start, NULL);
  	float end;

	mpz_init_set_str(n, Prime->val[Prime->a], 10);
	i = decompose(n, dest);

    gettimeofday(&stop,NULL);
    end = ((stop.tv_sec*1e6 + stop.tv_usec) - (start.tv_sec*1e6 + start.tv_usec));
    pthread_mutex_lock (&lock);
    fprintf(Prime->fd, "PID: %d", getpid());
    fprintf(Prime->fd, "Time: %f", end);
    fprintf(Prime->fd,"\n");

    for(k = 0; k < i; k++){
        gmp_fprintf(Prime->fd,"%s%Zd", k?" * ":"",dest[k]);
        mpz_clear(dest[k]);
    }
    fprintf(Prime->fd,"\n");
    pthread_mutex_unlock (&lock);
	return NULL;
}
