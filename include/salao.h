#ifndef SALAO_H
#define SALAO_H

#include "manager.h"
#include <thread>
#include <unistd.h>
#include <semaphore.h>
//classe que controla as threads
class Salao{
    private: 
        std :: thread tB, tC, tD;   
        Manager* manager;
        unsigned int* buffer;           // armazena o numero do cliente
        unsigned int atende_prox_cliente = 0;   // indica ao barbeiro qual o próximo cliente a ser atendido
        unsigned int posicao_buffer = 0;    // indica a posição no buffer em que será inserido o cliente que acabou de chegar
        unsigned int esperando = 0;   
        unsigned int i = 1;
        unsigned int N_CADEIRAS;
        sem_t clientes, mut;
    public:
        Salao(unsigned int,Manager* man);
        void atrasoGeral();
        void execucao_barbeiro();
        void execucao_clientes();
        void inicializa_barbeiro();
        void gera_clientes();
        void inicializa_clientes();
        void rest();
        void arrived(int);
        void give_up(int);
        void serving(int);
        void waiting(int,int);

};

#endif