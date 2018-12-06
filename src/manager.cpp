#include "manager.h"


Manager::Manager(Entity* b,Entity* bc,std::vector<Entity*> cha,std::vector<Entity*> cli){
	mBarber = b;
	mBarberChair = bc;
	mChairs = cha;
	mClients = cli;
}

void Manager::update(const double elapsed){
	//Update the client and barber positions

}


void Manager::moveClientToChair(uint32_t client,uint32_t chair){
	mClients[client]->setPosition(mFirstChairX*chair,mFirstChairY);
}

void Manager::moveClientToBarberChair(uint32_t client){
	float x,y;
	mBarberChair->getXnY(x,y);
	mClients[client]->setPosition(x,y);
}

void Manager::moveClientOut(uint32_t client){
	mClients[client]->setPosition(64*5,64); //change this
	//check if the are clients 
}


void Manager::cutHair(uint32_t client){
	mClients[client]->setState(Entity::HAIRCUT);
}