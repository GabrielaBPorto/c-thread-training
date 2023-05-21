#include<stdio.h>
#include<omp.h>


static long num_steps= 10000000;
double step;

int main() {
	double pi, soma = 0.0;
	step= 1.0/(double) num_steps;

	#pragma omp parallel num_threads(4)
	{
		int i; 
		double x, sum = 0.0;
		#pragma omp for
		for (i=0;i< num_steps; i++){
			x = (i + 0.5) * step; // Largura do retângulo
			sum = sum + 4.0 / (1.0 + x*x); // Sum += Área do retângulo}
		}
		#pragma omp atomic
		soma += sum;
	}
	pi = step* soma;
	printf("O valor de pi é %f\n", pi);
}