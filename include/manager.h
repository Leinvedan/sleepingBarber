#ifndef MANAGER_H
#define MANAGER_H

#include "entity.h"



class Manager: public Entity{ //temp??
private:
	Entity* mBarber;
	Entity* mCut;
	Entity* mSleep;
	std::vector<Entity*> mChairs;
	std::vector<Entity*> mClients;
	float mFirstChairX,mFirstChairY;
	float mBarberStartX,mBarberStartY;
	float mBarberChairX,mBarberChairY;
public:
	Manager(Entity*,Entity*,Entity*,Entity*,std::vector<Entity*>,std::vector<Entity*>);
	void clientArrived(uint32_t);
	void moveClientToChair(uint32_t,uint32_t);
	void moveClientToBarberChair(uint32_t);
	void moveClientOut(uint32_t);
	void rejectClient(uint32_t);
	void cutHair(uint32_t);
	void barberSleep();
	void wakeBaber();
	void clientArriving(uint32_t);

	void setFirstChairPosition(float,float);
	void setBarberPosition(float,float);
	void setBarberChairPosition(float,float);
};




#endif