#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "primedecompose.h"
#include <pthread.h>
#include <iostream>

using namespace std;


// uses the GMP (GNU Multiple Precision Library for the computations
//gcc -Wall -o pdec primedec.c primedecompose.c -lgmp

#define MAX_FACTORS	1024
#define MAX_THREADS 6
void *Start(void *arg);

mpz_t dest[MAX_FACTORS]; // must be large enough to hold all the factors!

int main(int argc, char *argv[]){
  int i,k;
  pthread_t tid[MAX_THREADS];
	if(argc != 6){
			puts("Usage: ./pdec <number to be factored>");
			return EXIT_SUCCESS;
	}
	for(i = 1; i < argc; i++){
	//cout << argv[i] << endl;
	    if(pthread_create(&tid[i], NULL, Start,(void*) argv[i]) != 0){
            cout << "Error making thread" << endl;
            break;
        }
	}
	for(k = 1; k < argc; k++){
        pthread_join(tid[k],NULL);
    }
    /*for(i=0; i < l; i++){
        gmp_printf("%s%Zd", i?" * ":"", dest[i]);
    	mpz_clear(dest[i]);
  	}
  	printf("\n");
    */
  	return EXIT_SUCCESS;

    }

void *Start(void *arg){
    mpz_t n;
	char* val;
	val = (char*)arg;
	mpz_init_set_str(n, val, 10);
	//if the base is correct return 0 otherwise returns -1
	decompose(n);

	return NULL;
}

