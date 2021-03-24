#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 2
#define ELEMENTOS 10000

// criando a estrutura de dados a ser utilizada pela thread
typedef struct {
	int idThread, nThreads;
	int vetor[ELEMENTOS/2];
} t_args;

// a tarefa a ser executada pelas threads
void* incrementa(void *arg){
	t_args *args = (t_args *) arg;
	printf("--Tarefa incrementa da thread %d\n", args->idThread);

	int	size = sizeof args->vetor / sizeof args->vetor[0];
	for(int i = 0; i < size; i++){
		// Sem imprimir os elementos
		args->vetor[i] += 1;	// incrementando...
		
		// Imprimindo cada elemento
		/*printf("Thread %d - posicao %d do vetor\n", args->idThread, i);
		printf("Antes: %d\n", args->vetor[i]);
		args->vetor[i] += 1;	// incrementando...
		printf("Depois: %d\n", args->vetor[i]); */
	}

	free(args);
	pthread_exit(NULL);
}

// funcao principal do programa
int main (void) {
	pthread_t tid_sistema[NTHREADS];	// identificadores das threads do sistema
	int thread;		// variavel auxiliar
	t_args *arg;	// estrutura de dados

	for(thread = 0; thread < NTHREADS; thread++){
		printf("--Alocando os recursos da thread %d\n", thread);
		arg = malloc(sizeof(t_args));
		if(arg == NULL){
			printf("--ERRO: malloc()\n"); exit(-1);
		}
		arg->idThread = thread;
		arg->nThreads = NTHREADS;

		printf("--Criando thread %d\n", thread);
		if(pthread_create(&tid_sistema[thread], NULL, incrementa, (void*) arg)){
			printf("--ERRO: pthread_create()\n"); exit(-1);
		}
	}

	// encerrando threads
	for(thread = 0; thread < NTHREADS; thread++){
		if(pthread_join(tid_sistema[thread], NULL)){
			printf("--ERRO: pthread_join()\n"); exit(-1);
		}
	}

	printf("--Thread principal terminou.\n");
	pthread_exit(NULL);
}
