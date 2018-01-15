#include "primedecompose.h"
#include <iostream>

int decompose (mpz_t n){
	int i = 0;
  	mpz_t tmp, d, *o;
    //variables

	  mpz_init(tmp);
    //initialize tmp and set value to 0
  	mpz_init(d);
    //initialize d and set value to 0

  	while (mpz_cmp_si (n, 1))
    //set inital value of n to 1
	{
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
  	int k;
  	for(k = 0; k < i; k++){
        gmp_printf("%s%Zd", k?" * ":"",o[k]);
        mpz_clear(o[k]);
    }
    printf("\n");
  	return i;
}
