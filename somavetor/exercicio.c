#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 8
#define vectorSize 134217728
// #define vectorSize 32

int A[vectorSize], B[vectorSize];
long double somas[NTHREADS];

void *integral(void *region_ptr) {
	int indice = (int) region_ptr;
	long double soma_parcial = 0;
	int bloco_soma = vectorSize / NTHREADS;
	for (size_t i = 0; i < bloco_soma; i++) {
		soma_parcial+= A[(indice * bloco_soma) + i] + B[(indice * bloco_soma) + i];
		// printf("O index é %d e o bloco+soma %d e i %d\n", indice,  bloco_soma , i );
		// printf("A soma parcial de %f em (index %d) %d\n", soma_parcial);
		// printf("A[%d] = %d\nB[%d] = %d\nSoma = %f\n", indice * bloco_soma + i,
		// 	A[indice * bloco_soma + i], indice * bloco_soma + i, B[indice * bloco_soma + i], soma_parcial);
	}
	somas[indice] = soma_parcial;
	return NULL;
}

int main() {
	pthread_t thread[NTHREADS];

	for (int j = 0; j < vectorSize; j++)
	{
		A[j] = B[j] = j;
	}
	long double soma; int i;
	for (i = 0; i < NTHREADS; i++){
		//I create de thread with ID, attr, void * function that where thread starts in,
		pthread_create(&thread[i], NULL, integral, (void *)i);
	}
	soma=0;
	for (i = 0; i < NTHREADS; i++){
		//I want to wait until my thread is done.
		pthread_join(thread[i], NULL);
		// printf("O valor de cada é %f \n", somas[i] );
		soma += somas[i];
	}
	printf("%Lf", soma );
}
