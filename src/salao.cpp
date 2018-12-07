#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <thread>
#include "salao.h"


Salao::Salao(unsigned int Num_cadeiras,Manager* man,GameEngine* g){
    N_CADEIRAS = Num_cadeiras;
    buffer = new unsigned int[Num_cadeiras];
    manager = man;
    mGame = g;
    sem_init(&clientes, 0, 0);
    sem_init(&mut, 0, 1);
}

void Salao::execucao_barbeiro(){
    sleep(2);
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


void Salao::gera_clientes(){
    sleep(2);
    while(1){
        updateScreenText();
        tC = std::thread(&Salao::execucao_clientes, this);
        tC.join();
        sleep(rand() % 1);         // intervalo de chegada dos clientes

    }
}

void Salao::execucao_clientes(){
    sem_wait(&mut);
    int id = i++;
    id = id % 19; //limitando os clientes, por causa de limitações da interface
    manager->clientArriving(id);
    sleep(1);//tempo que o cliente demora para chegar ao salao
    arrived(id);
    if(esperando < N_CADEIRAS){
        esperando++;
        sem_post(&clientes);
        unsigned int cadeiraCliente = posicao_buffer++ % N_CADEIRAS;
        buffer[cadeiraCliente] = id;
        waiting(id,cadeiraCliente);
    }
    else{
        give_up(id);
    }
    sem_post(&mut);
}



void Salao::inicializa_barbeiro(){
        tB = std::thread(&Salao::execucao_barbeiro, this);
        //tB.join();       --> se habilitar isso, os clientes não executam. Não sei por que...
}


void Salao::inicializa_clientes(){
    tD = std::thread(&Salao::gera_clientes, this);
}

void Salao::rest(){
    manager->barberSleep();
    printf("	Dormindo...\n");
}

void Salao::arrived(int id){
    printf("Cliente %i chegou...\n",id);
    manager->clientArrived(id);
    

}

void Salao::waiting(int id,int cadeira){
    printf("Cliente %i sentou na cadeira %i...\n",id,cadeira);
    manager->moveClientToChair(id,cadeira);
}

void Salao::give_up(int id){
    printf("Cliente %i desistiu, salao cheio...\n",id);
    manager->rejectClient(id); //move sprite para área cinza, fora do salao
}

void Salao::serving(int cliente_atual){
    printf("	Atendendo o cliente %i...\n",cliente_atual);
    manager->wakeBaber();
    manager->moveClientToBarberChair(cliente_atual); //move sprite pra cadeira do barbeiro
    sem_post(&mut);
    sleep(2);     	
    printf("	Terminei de atender o cliente %i\n",cliente_atual);
    manager->cutHair(cliente_atual);
    manager->moveClientOut(cliente_atual); //move sprite para fora do salao
}

void Salao::updateScreenText(){
    std::string text;
    text="Total: "+std::to_string(i)+"\n"+
        "Atendidos: "+std::to_string(cortados)+"\n"+
        "Rejeitados: "+std::to_string(rejeitados)+"\n";
    mGame->updateScreenText(text);
}