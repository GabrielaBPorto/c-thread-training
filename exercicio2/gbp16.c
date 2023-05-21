#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NTHREADS 4
#define vectorSize 26
#define lineSize 100

FILE *input;
long long alfabeto[NTHREADS][vectorSize+38];
long long alfabetoTrue[vectorSize];
pthread_mutex_t mutexes[vectorSize];

void *conta(void *id) {
	int meuId = (int) id;
	if ( input != NULL ){
		char line [lineSize]; /* or other suitable maximum line size */
		//Por ser thread safe não tem a necessidade de utilização de mutex de controle para garantir a leitura
		while ( fgets ( line, sizeof(line), input ) != NULL ) {/* read a line */
			for (int i = 0; i < strlen(line); i++){
				char c = line[i];
				if(c >= 'A' && c <= 'Z'){
					// pthread_mutex_lock(&mutexes[c-65]);
					alfabeto[meuId][c-65]++;
					// pthread_mutex_unlock(&mutexes[c-65]);
				}
				else if(c >= 'a' && c <= 'z'){
					// pthread_mutex_lock(&mutexes[c-97]);
					alfabeto[meuId][c-97]++;
					// pthread_mutex_unlock(&mutexes[c-97]);
				}
			}
			// fputs ( line, stdout ); /* write the line */
		}
	}
	else {
	}


	return NULL;
}

int main ( void ){
	static const char filename[] = "Pride.txt";
	pthread_t thread[NTHREADS];
	// for (int i = 0; i < vectorSize; i++){
	// 	pthread_mutex_init(&mutexes[i],NULL);
	// }
	memset(alfabeto,0,(NTHREADS*vectorSize)*sizeof(long long));
	input = fopen ( filename, "r" );
	for (int i = 0; i < NTHREADS; ++i){
		pthread_create(&thread[i], NULL, conta, (void *)i);
	}
	for (int i = 0; i < NTHREADS; i++){
		//I want to wait until my thread is done.
		pthread_join(thread[i], NULL);
	}
	for (int j = 0; j < NTHREADS; j++) {
		for (int i = 0; i < vectorSize; i++) {
			alfabetoTrue[i] = alfabeto[j][i];
		}
	}
	// for (int i = 0; i < vectorSize; i++)
	// {
	// 	printf(" %c: %d\n", i+65, alfabetoTrue[i]);
	// }
	fclose ( input );

	return 0;
}
