#include<stdio.h>
#include<omp.h>

int main(){
	

//Setar não quer dizer que o SO irá dar
	#pragma omp parallel num_threads(4)
	{
		int threads_ativas = omp_get_num_threads();
		int ID = omp_get_thread_num();
		printf("São %d de threads ativas\n", threads_ativas);
		printf("(%d)Hello ",ID);
		printf("(%d)World\n",ID);
	}
}