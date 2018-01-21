/*-----------------------------------------------------------------------------------------------
-- FUNCTION:   decompose
--
-- DATE:       January 17 2018
--
-- DESIGNER:   Taken from your example on milliways
--
-- PROGRAMMER: Taken from your example on milliways
--
-- INTERFACE:  int decompose(mpz_t n, mpz_t *o)
--
-- PARAMATER:  mpz_t n - value to be decomposed
--						 mpz_t o* - array holding the deomposed values
--
-- RETURNS:    returns number of values in the array
--
-- NOTES:      Decomposes the prime number and adds it to the array and returns
--						 number of values in the array
----------------------------------------------------------------------------------------------- */
#include "primedecompose.h"
 	int decompose (mpz_t n, mpz_t *o){
	int i = 0;
  	mpz_t tmp, d;

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

		return i;
}
