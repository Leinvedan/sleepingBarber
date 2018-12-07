#ifndef MANAGER_H
#define MANAGER_H

#include "entity.h"



class Manager: public Entity{ //temp??
private:
	Entity* mBarber;
	Entity* mBarberChair;
	std::vector<Entity*> mChairs;
	std::vector<Entity*> mClients;
	float mFirstChairX,mFirstChairY;
public:
	Manager(Entity*,Entity*,std::vector<Entity*>,std::vector<Entity*>);
	void update(const double);
	void moveClientToChair(uint32_t,uint32_t);
	void moveClientToBarberChair(uint32_t);
	void moveClientOut(uint32_t);
	void cutHair(uint32_t);
};




#endif