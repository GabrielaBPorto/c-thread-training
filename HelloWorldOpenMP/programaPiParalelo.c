#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 3
static long num_steps = 10000000;

int main(){
	int total_threads;
	double pi, sum=0.0;
	// , soma[NUM_THREADS][8], 
	long nums_steps = num_steps / NUM_THREADS;
	double step = 1.0/(double) num_steps;

	// A paralela por BLOCOS. Ou seja, todos os blocos
	#pragma omp parallel num_threads(NUM_THREADS)
	{
		double x, soma= 0.0;
		int i;
		for(i = 0; i< nums_steps; i++){
			x = (i * 0.5) * step; // Largura do retangulo ( pegando no meio)
			soma = soma + 4.0 / (1.0 + x*x); // Área do retangulo
		}
	}

	// total_threads = NUM_THREADS;
	//Cada retangulo é pego por quem está na fila
	#pragma omp parallel num_threads(NUM_THREADS)
	{
		double x; double 
		int id = omp_get_thread_num();
		int num_threads = omp_get_num_threads();
		if(num_threads != NUM_THREADS && visitado == 0){
			total_threads = NUM_THREADS;
			visitado = 1;
		}
		for(int i = id; i< nums_steps; i+=id){
			x = (i * 0.5) * step; // Largura do retangulo ( pegando no meio)
			soma[id][0] += 4.0 / (1.0 + x*x); // Área do retangulo
		}
		#pragma omp critical
		{
			sum +=soma;
		}
	}
	// for (int j = 0; j < total_threads; j++)
	// {
	// }
	
	pi = step * sum;	
	printf("O valor de pi é %lf\n", pi);
}