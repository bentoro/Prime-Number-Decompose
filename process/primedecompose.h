#ifndef _PRIMEDECOMPOSE_H_
#define _PRIMEDECOMPOSE_H_
#include <gmp.h>
#include <iostream>
//#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int decompose(mpz_t n, mpz_t *o);
#endif
