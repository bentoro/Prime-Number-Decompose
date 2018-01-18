#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "primedecompose.h"
#include <pthread.h>
#include <iostream>
#include <cstring>

using namespace std;

// uses the GMP (GNU Multiple Precision Library for the computations
//gcc -Wall -o pdec primedec.c primedecompose.c -lgmp

#define MAX_FACTORS	1024
#define MAX_THREADS 6

void *Start(void *arg);

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct{
    FILE* fd;
    char* val;
}ThreadInfo;

mpz_t dest[MAX_FACTORS]; // must be large enough to hold all the factors!

int main(int argc, char *argv[]){
  int i,k;
  pthread_t tid[MAX_THREADS];
  ThreadInfo *PrimeInfo;
	if(argc != 6){
			puts("Usage: ./pdec <number to be factored>");
			return EXIT_SUCCESS;
	}
    FILE *fp;
    fp = fopen("threads.txt","w");
    //PrimeInfo = (ThreadInfo *)malloc(sizeof(ThreadInfo));
	for(i = 1; i < argc; i++){
	      memset(&PrimeInfo, 0,sizeof(PrimeInfo));
        PrimeInfo->val = argv[i];
        PrimeInfo->fd = fp;
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

void *Start(void *arg){
    ThreadInfo *Prime = (ThreadInfo *)arg;
    mpz_t n;
    int i;
    struct timeval stop, start;
  	gettimeofday(&start, NULL);
  	float end;
	mpz_init_set_str(n, Prime->val, 10);
	//if the base is correct return 0 otherwise returns -1
	i = decompose(n, dest);

  gettimeofday(&stop,NULL);
  end = ((stop.tv_sec*1e6 + stop.tv_usec) - (start.tv_sec*1e6 + start.tv_usec));
  pthread_mutex_lock (&lock);
  fprintf(Prime->fd, "Time: %f", end);
  fprintf(Prime->fd,"\n");
  int k;
  for(k = 0; k < i; k++){
      gmp_fprintf(Prime->fd,"%s%Zd", k?" * ":"",dest[k]);
      mpz_clear(dest[k]);
  }
  fprintf(Prime->fd,"\n");
  pthread_mutex_unlock (&lock);

	return NULL;
}
