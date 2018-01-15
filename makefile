pdec: threads.c primedecompose.c
	g++ -pthread -g -Wall -o pdec threads.c primedecompose.c -lgmp
