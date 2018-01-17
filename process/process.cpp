#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "primedecompose.h"
#include <iostream>
#include <sys/types.h>

using namespace std;

// uses the GMP (GNU Multiple Precision Library for the computations
//gcc -Wall -o pdec primedec.c primedecompose.c -lgmp

#define MAX_FACTORS	1024
#define MAX_PROCESS 6

mpz_t dest[MAX_FACTORS]; // must be large enough to hold all the factors!

int main(int argc, char *argv[]){
    int i,k;
    mpz_t n;
    pid_t pid[MAX_PROCESS];
	if(argc != 2){
			puts("Usage: ./pdec <number to be factored>");
			return EXIT_SUCCESS;
	}

	for(i = 1; i < argc; i++){
	    if((pid[i] = fork()) < 0){
            perror("Fork error");
            exit(0);
        } else {
          mpz_init_set_str(n, argv[i], 10);
          decompose(n);
        }
	}
  	return 0;

    }
