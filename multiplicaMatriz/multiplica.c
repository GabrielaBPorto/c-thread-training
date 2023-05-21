#include <stdio.h>
#include <omp.h>
#include <string.h>
#include <stdlib.h>

#define N 2000


int main()
{
	double *A = malloc(N*N*sizeof(double));
	double *B = malloc(N*N*sizeof(double));
	double *C = malloc(N*N*sizeof(double));

	#pragma omp parallel for
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			A[i*j+N] = i/(j+1);
			B[i*j+N] = i*j;
			C[i*j+N] = 0;
		}
	}

//for ii < N e for jj < N ii+=BlockSize ij+=BlockSize
//for kk= 0
//for int i = ii i<ii+BlockSize&&i<N i++ e int j = jj j<jj+BlockSize j++
//for k =kk k++ )k+=4


	double soma;
	#pragma omp parallel firstprivate(soma)
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				for (int k = 0; k < N; ++k)
				{
					soma+= A[k*i+N] + B[j*k+N];
				}
			}
		}
	}

	printf("%g\n", C[(N-1)*(N-1)]);
	return 0;
}