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
-- Notes:      Creates processes per argument that is added and decomposes each
               Prime number
--
----------------------------------------------------------------------------------------------- */

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

int main(int argc, char *argv[]){
    struct timeval sp, st;
    int i,k;
    pid_t pid;

	if(argc != 6){
			puts("Usage: ./pdec <number to be factored>");
			return EXIT_SUCCESS;
	}
  gettimeofday(&st, NULL);
	for(i = 1; i <= argc; i++){
        if((pid = fork()) < 0){
            perror("Fork error");
            exit(0);
        } else {
            if(pid == 0){
                Start(argv[i]);
                exit(0);
            }
        }
	     }
       long end;
  	for(k = 1; k <= argc; k++){
        wait(NULL);
    }
    gettimeofday(&sp, NULL);
    end = ((sp.tv_sec) - (st.tv_sec));
    cout << end << endl;
  	return 0;
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
    -- Notes:      Starts each prime decompostion and creates a new process per call
    --
    ----------------------------------------------------------------------------------------------- */

void Start(char *arg){
    mpz_t dest[MAX_FACTORS];
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    float end;
    int i, k;
    FILE *fp;
    mpz_t n;
    mpz_init_set_str(n, arg, 10);
    i = decompose(n, dest);
    cout << "value: " << arg << endl;
    fp = fopen("process.txt","a+");
    fprintf(fp, "PID: %d", getpid());
    printf("PID: %d", getpid());
    fprintf(fp,"\n");
    printf("\n");
    for(k = 0; k < i; k++){
        gmp_fprintf(fp,"%s%Zd", k?" * ":"",dest[k]);
        gmp_printf("%s%Zd", k?" * ":"",dest[k]);
        mpz_clear(dest[k]);
    }
    fprintf(fp,"\n");
    printf("\n");
    gettimeofday(&stop,NULL);
    end = ((stop.tv_sec*1e6 + stop.tv_usec) - (start.tv_sec*1e6 + start.tv_usec));
    fprintf(fp, "Time: %f\n", end);
    printf("Time: %f\n", end);
}
