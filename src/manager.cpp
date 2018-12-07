#include "manager.h"

Manager::Manager(Entity* b,Entity* bc,std::vector<Entity*> cha,std::vector<Entity*> cli){
	mBarber = b;
	mChairs = cha;
	mClients = cli;

}

void Manager::setBarberChairPosition(float x,float y){
	mBarberChairX = x;
	mBarberChairY = y;
}

void Manager::setFirstChairPosition(float x,float y){
	mFirstChairX = x;
	mFirstChairY = y;
}

void Manager::setBarberPosition(float x,float y){
	mBarberStartX = x;
	mBarberStartY = y;
}

void Manager::clientArrived(uint32_t client){
	mClients[client]->clearInputBuffer(); //recycle previous client
	mClients[client]->setState(Entity::IDLE);
	mClients[client]->setPosition(64*2,64);
}

void Manager::moveClientToChair(uint32_t client,uint32_t chair){
	printf("%.f %.f\n",mFirstChairX*(chair+2),mFirstChairY);
	mClients[client]->setPosition(mFirstChairX*(chair+2),mFirstChairY);
}

void Manager::moveClientToBarberChair(uint32_t client){
	mClients[client]->setPosition(mBarberChairX,mBarberChairY);
}

void Manager::moveClientOut(uint32_t client){
	mClients[client]->setPosition(64*4,64); 
	mClients[client]->receiveInput(MOVE_RIGHT);//set walking animation
}

void Manager::rejectClient(uint32_t client){
	mClients[client]->setPosition(64*6,64);
	mClients[client]->receiveInput(MOVE_UP);//set walking animation
}


void Manager::cutHair(uint32_t client){
	mClients[client]->setState(Entity::HAIRCUT);
}



void Manager::barberSleep(){
	mBarber->setPosition(mBarberChairX,mBarberChairY);
}

void Manager::wakeBaber(){
	mBarber->setPosition(mBarberStartX,mBarberStartY);
}