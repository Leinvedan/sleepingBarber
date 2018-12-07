#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <thread>
#include "salao.h"

void Salao::execucao_barbeiro(){
    while(1){
        sem_wait(&mut);
        if(esperando > 0){
            esperando--;
            sem_trywait(&clientes);   		
            unsigned int cliente_atual = buffer[atende_prox_cliente++ % N_CADEIRAS];
            serving(cliente_atual);
        }
        else{
            sem_post(&mut);
            rest();
            sem_wait(&clientes);
        }	
    }
}

void Salao::execucao_clientes(){
    sem_wait(&mut); 
    int id = i++;
    arrived(id);

    if(esperando < N_CADEIRAS){
        esperando++;
        sem_post(&clientes);
        buffer[posicao_buffer++ % N_CADEIRAS] = id;
    }
    else{
        give_up(id);
    }
    sem_post(&mut);
}


Salao::Salao(unsigned int Num_cadeiras,Manager* man){
    N_CADEIRAS = Num_cadeiras;
    buffer = new unsigned int[Num_cadeiras];
    manager = man;
           
    sem_init(&clientes, 0, 0);
	sem_init(&mut, 0, 1);
}

void Salao::inicializa_barbeiro(){
        tB = std::thread(&Salao::execucao_barbeiro, this);
        //tB.join();       --> se habilitar isso, os clientes não executam. Não sei por que...
}

void Salao::gera_clientes(){
    while(1){
        tC = std::thread(&Salao::execucao_clientes, this);
        tC.join();
        sleep(rand() % 4);         // intervalo de chegada dos clientes
    }
}

void Salao::inicializa_clientes(){
    /*
    while(1){
        tC = std::thread(execucao_clientes, this);
        tC.join();
        sleep(rand() % 4);         // intervalo de chegada dos clientes
	}
    */
    tD = std::thread(&Salao::gera_clientes, this);
}

void Salao::rest(){
    printf("	Dormindo...\n");
}

void Salao::arrived(int id){
    printf("Cliente %i chegou...\n",id);
    //manager->moveClientToChair(id,0);

}

void Salao::give_up(int id){
    printf("Cliente %i desistiu, salao cheio...\n",id);
    //manager->moveClientOut(id); //move sprite para área cinza, fora do salao
}

void Salao::serving(int cliente_atual){
    printf("	Atendendo o cliente %i...\n",cliente_atual);
    //manager->moveClientToBarberChair(cliente_atual); //move sprite pra cadeira do barbeiro
    sem_post(&mut);
    sleep(2);     	
    printf("	Terminei de atender o cliente %i\n",cliente_atual);
    //manager->moveClientOut(cliente_atual); //move sprite para fora do salao
}

/*
int main(){
    Salao S(10);
	
    S.inicializa_barbeiro();
    S.inicializa_clientes();
    sleep(10);
}
*/