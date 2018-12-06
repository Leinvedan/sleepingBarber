#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <thread>
#include "main_thread.h"

namespace EXEC{
    unsigned int* buffer;			// armazena o numero do cliente
    unsigned int atende_prox_cliente = 0;   // indica ao barbeiro qual o próximo cliente a ser atendido
    unsigned int posicao_buffer = 0;    // indica a posição no buffer em que será inserido o cliente que acabou de chegar

    unsigned int esperando = 0;   
    unsigned int i = 1;
    unsigned int N_CADEIRAS;
    sem_t clientes, mut;

    void execucao_barbeiro(Salao* S){
        while(1){
            sem_wait(&mut);
            if(esperando > 0){
                esperando--;
                sem_trywait(&clientes);   		
                unsigned int cliente_atual = buffer[atende_prox_cliente++ % N_CADEIRAS];
                S->serving(cliente_atual);
            }
            else{
                sem_post(&mut);
                S->rest();
                sem_wait(&clientes);
            }	
        }
    }

    void execucao_clientes(Salao* S){
        sem_wait(&mut); 
        int id = i++;
        S->arrived(id);

        if(esperando < N_CADEIRAS){
            esperando++;
            sem_post(&clientes);
            buffer[posicao_buffer++ % N_CADEIRAS] = id;
        }
        else{
            S->give_up(id);
        }
        sem_post(&mut);
    }
}













using namespace EXEC;

Salao::Salao(unsigned int Num_cadeiras){
    N_CADEIRAS = Num_cadeiras;
    buffer = new unsigned int[Num_cadeiras];
           
    sem_init(&clientes, 0, 0);
	sem_init(&mut, 0, 1);
}

void Salao::inicializa_barbeiro(){
        tB = std::thread(execucao_barbeiro, this);
        //tB.join();       --> se habilitar isso, os clientes não executam. Não sei por que...
}

void Salao::inicializa_clientes(){
    while(1){
        tC = std::thread(execucao_clientes, this);
        tC.join();
        sleep(rand() % 4);         // intervalo de chegada dos clientes
	}
}

void Salao::rest(){
    printf("	Dormindo...\n");
}

void Salao::arrived(int id){
    printf("Cliente %i chegou...\n",id);
}

void Salao::give_up(int id){
    printf("Cliente %i desistiu, salao cheio...\n",id);
}

void Salao::serving(int cliente_atual){
    printf("	Atendendo o cliente %i...\n",cliente_atual);
    sem_post(&mut);
    sleep(2);     	
    printf("	Terminei de atender o cliente %i\n",cliente_atual);
}

int main(){
    Salao S(10);
	
    S.inicializa_barbeiro();
    S.inicializa_clientes();
    sleep(10);
}


