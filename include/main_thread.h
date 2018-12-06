#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H

class Salao{
    private: 
        std :: thread tB, tC;   
    public:
        Salao(unsigned int);
        void inicializa_barbeiro();
        void inicializa_clientes();
        void rest();
        void arrived(int);
        void give_up(int);
        void serving(int);
};

#endif