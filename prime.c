#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <pthread.h>

void *Prime(void *arg);

int main(int argc, char *argv[]){
    int i, k;
    pthread_t tid[6];
    if(argc!=2){
        perror("Usage: ./pdec <number to be factored>");
        exit(0);
    }
    for(i = 1; i <= argc; i++){
        if(pthread_create(&tid[i], Prime,(void*) argv[i]) != 0){
            cout << "error creating thread" << endl;
        }
    }

    for(k = 1; k<=argc; k++){
        pthread_join(tid[k],NULL);
    }

    return 0;
}
void *Prime(void *arg){
    int number;
    number = (int)arg;
    int div = 2;
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
