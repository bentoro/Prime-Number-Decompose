#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "primedecompose.h"
#include <pthread.h>
#include <cstring>
#include <iostream>
#include <sys/time.h>

using namespace std;

// uses the GMP (GNU Multiple Precision Library for the computations
//gcc -Wall -o pdec primedec.c primedecompose.c -lgmp

#define MAX_FACTORS	1024
#define MAX_THREADS 6

void* Start(void *);

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

char *values[1024];
int count;

int main(int argc, char *argv[]){
  int i,k;
  pthread_t tid[MAX_THREADS];
	if(argc != 6){
			puts("Usage: ./pdec <number to be factored>");
			return EXIT_SUCCESS;
	}
  int j;
  for(j = 1; j<=argc; j++){
    values[j] = argv[j];
    cout << values[i] << endl;
  }
    FILE *fp;
    fp = fopen("threads.txt","w");
	for(i = 1; i < argc; i++){
    count = i;
	    if(pthread_create(&tid[i], NULL, Start,(void*) fp) != 0){
            cout << "Error making thread" << endl;
            break;
        }
	}
	for(k = 1; k < argc; k++){
        pthread_join(tid[k],NULL);
    }
  	return EXIT_SUCCESS;

    }

void* Start(void* fp){
    mpz_t dest[MAX_FACTORS];
    char *val = values[count];
    mpz_t n;
    int i;
    struct timeval stop, start;
  	gettimeofday(&start, NULL);
  	float end;
	mpz_init_set_str(n, val, 10);
	i = decompose(n, dest);

  gettimeofday(&stop,NULL);
  end = ((stop.tv_sec*1e6 + stop.tv_usec) - (start.tv_sec*1e6 + start.tv_usec));
  pthread_mutex_lock (&lock);
  fprintf(fp, "Time: %f", end);
  fprintf(fp,"\n");
  int k;
  for(k = 0; k < i; k++){
      gmp_fprintf(fp,"%s%Zd", k?" * ":"",dest[k]);
      mpz_clear(dest[k]);
  }
  fprintf(fp,"\n");
  pthread_mutex_unlock (&lock);

	return NULL;
}
