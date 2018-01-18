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

void Start(char *arg, FILE *fp);

int main(int argc, char *argv[]){
    int i,k;
    pid_t pid[MAX_PROCESS];

	if(argc != 6){
			puts("Usage: ./pdec <number to be factored>");
			return EXIT_SUCCESS;
	}
    FILE *fp;
    fp = fopen("process.txt","w");
	for(i = 1; i <= argc; i++){
        if((pid[i] = fork()) < 0){
            perror("Fork error");
            exit(0);
        } else {
            if(pid[i] == 0){
                Start(argv[i],fp);
                exit(0);
            }
        }
	}

  	for(k = 1; k <= argc; k++){
        wait(NULL);
    }

    fclose(fp);
  	return 0;
    }

void Start(char *arg, FILE *fp){
    mpz_t dest[MAX_FACTORS];
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    float end;
    int l;
    mpz_t n;
    mpz_init_set_str(n, arg, 10);
    l = decompose(n, dest);

    gettimeofday(&stop,NULL);
    end = ((stop.tv_sec*1e6 + stop.tv_usec) - (start.tv_sec*1e6 + start.tv_usec));
    printf("PID: %ld", (long)getpid());
    fprintf(fp, "PID: %ld", (long)getpid());
    printf("Time: %f",end);
    printf("\n");
    fprintf(fp, "\n");
    int k;
    for(k = 0; k < l; k++){
        gmp_printf("%s%Zd", k?" * ":"",dest[k]);
        gmp_fprintf(fp, "%s%Zd", k?" * ":"",dest[k]);
        mpz_clear(dest[k]);
    }
    printf("\n");
    fprintf(fp, "\n");
    }
