#include<stdio.h>
#include<omp.h>


static long num_steps= 10000000;
double step;
int total_threads_ativas;

int main() {
	double pi , soma = 0.0;
	step= 1.0/(double) num_steps;

	#pragma omp parallel num_threads(4)
	{
		double x,  sum = 0.0;
		int ID = omp_get_thread_num();
		total_threads_ativas = omp_get_num_threads();
		int num_steps2 = num_steps/omp_get_num_threads();
		for (int i=0;i< num_steps2; i++){
			x = (i + 0.5) * step; // Largura do retângulo
			sum = sum + 4.0 / (1.0 + x*x); // Sum += Área do retângulo}
		}
		#pragma omp atomic
		soma += sum;
	}

	pi = step* soma;
	
	printf("O valor de pi é %f\n", pi);
}