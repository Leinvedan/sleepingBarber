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
	uint32_t mType;
	float mX,mY;
	uint32_t mLastInput = 0; //Received from the last handleInput
	uint32_t mState = 0;
	float mScale = 1;
	//rendering and animation
	float mSpeedPerTick = 0;
	uint8_t mNumberOfAnimations = 7;
	std::vector<SpriteComponent*> mAnimations;
public:
	enum Type{
		ENTITY,
		CHARACTER,
		COMBATANT
	};
	enum State{
		IDLE,
		WALKING,
		RUNNING,
		DYING,
		SKILL_1,
		SKILL_2,
		SKILL_3
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
	uint32_t getType();
	~Entity();

	

};



//GAME CONSTANTS

//-----> [[HIT filters]] <-----
//Using the AND (&) operator
//Represents the bits [0,19]
const uint32_t DAMAGE_FILTER = 0x000FFFFF;
//Represents the bits [20,28]
const uint32_t STATS_FILTER  = 0x1FF00000;
//Represents the bits [29,30,31]
const uint32_t TYPE_FILTER   = 0xE0000000;
//-----> [[Type constants]] <-----
const uint32_t MELEE  = 0x20000000;
const uint32_t MAGIC  = 0x40000000;
const uint32_t RANGED = 0x80000000;

//-----> [[Stats constants]] <-----
//Stats with same number will overrite each other
//otherwise they'll stack, in a way... (trying to use OR(|) at the moment)
const uint32_t LIGHT_WOUND   = (50  << 20);
const uint32_t MEDIUM_WOUND  = (75  << 20);
const uint32_t HEAVY_WOUND   = (100  << 20);
const uint32_t FIRE          = (200  << 20);
const uint32_t ICE           = (200  << 20);
const uint32_t PARALYSIS     = (150  << 20);
const uint32_t COMMON_POISON = (300  << 20);
const uint32_t RARE_POISON   = (400  << 20);
const uint32_t LETAL_POISON  = (500 << 20);
const uint32_t DEATH         = (511 << 20);

//-----> [[Movement constants]] <-----
const uint32_t MOVE_UP    = 0x01; //0000 0001
const uint32_t MOVE_DOWN  = 0x02; //0000 0010
const uint32_t MOVE_RIGHT = 0x04; //0000 0100
const uint32_t MOVE_LEFT  = 0x08; //0000 1000

//-----> [[Combat constants]] <-----
const uint32_t RUN           = 0x10;   //0000 0001 0000
const uint32_t ACTION_1      = 0x20;   //0000 0100 0000
const uint32_t ACTION_2      = 0x40;   //0000 1000 0000
const uint32_t ACTION_3      = 0x80;   //0000 0010 0000
const uint32_t SWITCH_STANCE_NEXT = 0x100;  //0010 0000 0000
const uint32_t SWITCH_STANCE_PREV = 0x200;  //0010 0000 0000


#endif