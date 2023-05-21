#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 2
static long num_steps = 1000000000;

int main(){
	double pi, sum=0.0, soma;
	double step = 1.0/(double) num_steps;


	#pragma omp parallel num_threads(NUM_THREADS)
	{
		double x;
		// int id = omp_get_thread_num();
		// long numTotal = num_steps/omp_get_num_threads();;
		// #pragma omp for

		#pragma omp for reduction (+:soma)
		for(int i = 0; i< num_steps; i++){
			x = (i * 0.5) * step; // Largura do retangulo ( pegando no meio)
			soma = soma + 4.0 / (1.0 + x*x); // Área do retangulo
		}
	}

	pi = step * soma;
	
	
	printf("O valor de pi é %lf\n", pi);
}