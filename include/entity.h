#ifndef ENTITY_H
#define ENTITY_H


#include "spriteComponent.h"
#include <vector>

//Global Unique ID for all game's entities
static uint32_t ENTITY_ID_COUNTER = 0;


class Entity{
protected:
	bool mMarkedToDestroy = false;
	//Function that updates the ID
	uint32_t createID();
	uint32_t ID;
	float mX,mY;
	uint32_t mLastInput = 0; //Received from the last handleInput
	uint32_t mState = 0;
	float mScale = 1;
	//rendering and animation
	float mSpeedPerTick = 0;
	uint8_t mNumberOfAnimations = 7;
	std::vector<SpriteComponent*> mAnimations;
public:
	enum State{
		IDLE,
		HAIRCUT,
		INVISIBLE
	};
	Entity();
	//default methods
	uint32_t getID();
	uint32_t getScale();
	void getXnY(float&,float&);
	void getWnH(float&,float&);
	SpriteComponent* getCurrentSpriteComponent();
	void setSpeed(float);
	void setScale(float);
	void setPosition(float, float);
	void clearInputBuffer();
	void addSpriteComponent(SpriteComponent*, State);
	virtual void update(const double);
	virtual void receiveInput(const uint32_t);
	void markToDestroy();
	bool isMarkedToDestroy();
	void setState(State);
	~Entity();

	

};



//GAME CONSTANTS

//-----> [[HIT filters]] <-----
//Using the AND (&) operator
//-----> [[Movement constants]] <-----
const uint32_t MOVE_UP    = 0x01; //0000 0001
const uint32_t MOVE_DOWN  = 0x02; //0000 0010
const uint32_t MOVE_RIGHT = 0x04; //0000 0100
const uint32_t MOVE_LEFT  = 0x08; //0000 1000



#endif