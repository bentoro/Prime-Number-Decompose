#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <pthread.h>
#include <string.h>

void *Prime(void *arg);

typedef struct{
 int n;
 int div;
}ThreadInfo;

int main(int argc, char *argv[]){
    int i, k;
    pthread_t tid[6];
    ThreadInfo *primeinfo;

    if(argc!=2){
        perror("Usage: ./pdec <number to be factored>");
        exit(0);
    }

    if((primeinfo = malloc(sizeof(ThreadInfo))) == NULL){
      perror("malloc");
      exit(1);
    }

    for(i = 1; i <= argc; i++){
        primeinfo->n = atoi(argv[i]);
        primeinfo->div = 2;
        if(pthread_create(&tid[i], Prime,(void*) primeinfo) != 0){
            cout << "error creating thread" << endl;
        }
    }

    for(k = 1; k<=argc; k++){
        pthread_join(tid[k],NULL);
    }

    return 0;
}
void *Prime(void *primeinfo){
    ThreadInfo *primes = (ThreadInfo *)primeinfo;

    int number = primes->n;
    int div = primes->div;
    while (number != 0){
        if(number%div!=0){
            div = div + 1;
        } else {
            number = number / div;
            printf("%d ", div);
            if(number ==1){
                break;
            }
        }
    }
}
