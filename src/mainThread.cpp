#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define N_CADEIRAS 5
#define N_CLIENTES 20

using namespace std;
sem_t finaliza;    // segura a thread main até o barbeiro terminar
sem_t clientes;
sem_t mutex;	

unsigned int* buffer;			// armazena o numero do cliente
unsigned int atende_prox_cliente = 0;   // indica ao barbeiro qual o próximo cliente a ser atendido
unsigned int posicao_buffer = 0;    // indica a posição no buffer em que será inserido o cliente que acabou de chegar

unsigned int esperando = 0;   
unsigned int i = 1;
         
unsigned int cont = 0;   // (clientes o barbeiro atendeu) + (clientes que desistiram) 

void* execucao_thread1_barbeiro(void* x){
	while(cont < N_CLIENTES){
		sem_wait(&mutex);
            if(esperando > 0){
				esperando--;
				sem_trywait(&clientes);   		 // somente decrementa o semáforo clientes, não adormece a thread caso clientes se torne zero
				unsigned int cliente_atual = buffer[atende_prox_cliente++ % N_CADEIRAS];
				printf("Atendendo o cliente %i...\n",cliente_atual);
                cont++;
				sem_post(&mutex);
				sleep(2);     	 // tempo que o barbeiro leva pra atender;
				printf("Terminei de atender o cliente %i\n",cliente_atual);
			}
			else{
				sem_post(&mutex);
				printf("Dormindo...\n");
				sem_wait(&clientes);
			}	
	}
    printf("Dormindo...\n");
	sem_post(&finaliza);  
	pthread_exit(NULL);
}

void* execucao_threadN_clientes(void* x){
	sem_wait(&mutex); 
		int id = i++;
		printf("Cliente %i chegou...\n",id);

		if(esperando < N_CADEIRAS){
			esperando++;
			sem_post(&clientes);
			buffer[posicao_buffer++ % N_CADEIRAS] = id;
		}
		else{
		    printf("Cliente %i desistiu, salao cheio...\n",id);
            cont++;              
        }
	sem_post(&mutex);
	pthread_exit(NULL);
}


int main(){
	buffer = new unsigned int[N_CADEIRAS];

	sem_init(&finaliza, 0, 0);  
	sem_init(&clientes, 0, 0);
	sem_init(&mutex, 0, 1);
	
	pthread_t barb;
	pthread_t* cli = new pthread_t[N_CLIENTES];
	
	pthread_create(&barb, NULL, &execucao_thread1_barbeiro, NULL);    
	
	for(int j=0 ; j < N_CLIENTES ; j++){   
		pthread_create(&cli[j], NULL, &execucao_threadN_clientes, NULL);   
		sleep(rand() % 3);         // intervalo de chegada dos clientes
	}
	sleep(1);

	sem_wait(&finaliza);   
}

