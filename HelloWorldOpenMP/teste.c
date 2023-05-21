#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 2
static long num_steps = 100000000;

int main(){
	int total_threads;
	double pi, sum[NUM_THREADS][8], soma,x;
	// , soma[NUM_THREADS][8], 
	// long nums_steps = num_steps / NUM_THREADS;
	double step = 1.0/(double) num_steps;

	#pragma omp parallel num_threads(NUM_THREADS) 
	{
		#pragma omp parallel for firstprivate(soma) firstprivate(x)
		for(int i = 0; i< num_steps; i++){
			x = (i * 0.5) * step; // Largura do retangulo ( pegando no meio)
			soma = soma + 4.0 / (1.0 + x*x); // Área do retangulo
		}
		sum[omp_get_thread_num()][0] = soma;
	}

	for (int i = 0; i < NUM_THREADS; ++i)
	{
		pi = step * sum[i][0];	
	}

	
	
	printf("O valor de pi é %lf\n", pi);
}