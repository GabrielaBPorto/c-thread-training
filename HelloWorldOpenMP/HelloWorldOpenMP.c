#include <stdio.h>
#include <omp.h>

int main(){
	// int ID=0;

	#pragma omp parallel
	//Cada variavel definida dentro é privada
	//criação de condição de corrida em acesso a memória em ID
	{
		int ID = omp_get_thread_num();
		// ID++;
		printf("hello(%d) ", ID);
		printf("world(%d)\n", ID);
		// ID++;
	}
}