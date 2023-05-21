#include <omp.h>

static long num_steps = 10000; double step;

#define NUM_THREADS 2

void main () {
	int i, nthreads; double pi, sum[NUM_THREADS];
	step = 1.0/(double) num_steps;
	#pragma omp parallel num_threads(NUM_THREADS)
	{
		int i, id, nthrads; double x;
		id = omp_get_thread_num();
		nthrads = omp_get_num_threads();
		if(id == 0) nthreads = nthrads;
		for(i=id, sum[id] = 0.0; i<num_steps; i = i+nthrads){
			x = (i + 0.5) * step;
			sum[id] += 4.0/(1.0+x*x);
		}
	}
	for(i =0, pi=0.0; i< nthreads; i++)
		pi += sum[i] * step;
}