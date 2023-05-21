#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000000;

int main(){
	int i; double x, pi, sum,step = 0.0;
	step = 1.0/(double) num_steps;
	for(i = 0; i< num_steps; i++){
		x = (i * 0.5) * step; // Largura do retangulo ( pegando no meio)
		sum = sum + 4.0 / (1.0 + x*x); // Área do retangulo
	}
	pi = step * sum;
	printf("O valor de pi é %lf\n", pi);
}