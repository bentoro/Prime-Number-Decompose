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

void *Start(void *arg);

mpz_t dest[MAX_FACTORS]; // must be large enough to hold all the factors!
mpz_t n;
int l;

int main(int argc, char *argv[]){
  int i;
  pthread_t tid;
	if(argc != 2){
			puts("Usage: ./pdec <number to be factored>");
			return EXIT_SUCCESS;
	}
	//for(i = 1; i <= argc; i++){
	//cout << &argv[1] << endl;
	pthread_create(&tid, NULL, Start,(void*) argv[1]);
	//}
    pthread_join(tid,NULL);

    for(i=0; i < l; i++){
        gmp_printf("%s%Zd", i?" * ":"", dest[i]);
    	mpz_clear(dest[i]);
  	}
  	printf("\n");

  	return EXIT_SUCCESS;

    }

void *Start(void *arg){
	char* val;
	val = (char*)arg;
	mpz_init_set_str(n, val, 10);
	//if the base is correct return 0 otherwise returns -1
	l = decompose(n, dest);

	return NULL;
}

