#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "primedecompose.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

// uses the GMP (GNU Multiple Precision Library for the computations
//gcc -Wall -o pdec primedec.c primedecompose.c -lgmp

#define MAX_FACTORS	1024
#define MAX_PROCESS 6

void Start(char *arg);

mpz_t dest[MAX_FACTORS]; // must be large enough to hold all the factors!

int main(int argc, char *argv[]){
    int i,k;
    pid_t pid[MAX_PROCESS];
	if(argc != 6){
			puts("Usage: ./pdec <number to be factored>");
			return EXIT_SUCCESS;
	}
	for(i = 1; i <= argc; i++){
	    if((pid[i] = fork()) < 0){
            perror("Fork error");
            exit(0);
        } else {
          if(pid[i] == 0){
          Start(argv[i]);
          //sleep(i);
          exit(0);
          }
        }
	}
  	for(k = 1; k <= argc; k++){
        wait(NULL);
    }
  	return 0;
    }

void Start(char *arg){
        mpz_t n;
    	mpz_init_set_str(n, arg, 10);
    	decompose(n);
    }
