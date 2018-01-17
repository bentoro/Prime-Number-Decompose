#include "primedecompose.h"
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void decompose (mpz_t n){

	struct timeval stop, start;
	gettimeofday(&start, NULL);
	float end;
	FILE *fp;
		int i = 0;
  	mpz_t tmp, d;
  	mpz_t o[1024];

		mpz_init(tmp);
  	mpz_init(d);

  	while (mpz_cmp_si (n, 1)){
    		mpz_set_ui(d, 1);
    		do
		{
      			mpz_add_ui(tmp, d, 1);
      			mpz_swap(tmp, d);
    		} while(!mpz_divisible_p(n, d));
    		mpz_divexact(tmp, n, d);
    		mpz_swap(tmp, n);
    		mpz_init(o[i]);
    		mpz_set(o[i], d);
    		i++;
  	}
		gettimeofday(&stop,NULL);
		end = ((stop.tv_sec*1e6 + stop.tv_usec) - (start.tv_sec*1e6 + start.tv_usec));
		pthread_mutex_lock (&lock);
		fp = fopen("threads.txt","w+");
		printf("Time: %f",end);
		fprintf(fp, "Time: %f", end);
		printf("\n");
		fprintf(fp,"\n");
  	int k;
  	for(k = 0; k < i; k++){
        gmp_printf("%s%Zd", k?" * ":"",o[k]);
        gmp_fprintf(fp,"%s%Zd", k?" * ":"",o[k]);
        mpz_clear(o[k]);
    }
    printf("\n");
    fprintf(fp,"\n");
    fclose(fp);
	pthread_mutex_unlock (&lock);
}
