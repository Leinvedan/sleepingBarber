#include "entity.h"
#include "spriteComponent.h"

Entity::Entity(): ID(createID()){
	mAnimations.resize(mNumberOfAnimations);
}

Entity::~Entity(){
}

uint32_t Entity::createID(){ 
	ENTITY_ID_COUNTER++; 
	return ENTITY_ID_COUNTER;
}

uint32_t Entity::getID(){
	return ID;
}

void Entity::setSpeed(float speed){
	mSpeedPerTick = speed;
}

void Entity::clearInputBuffer(){
	mLastInput = 0;
}

SpriteComponent* Entity::getCurrentSpriteComponent(){
	return mAnimations[mState];
}

void Entity::addSpriteComponent(SpriteComponent* sc, State state){
	mAnimations[state] = sc;
}

void Entity::setScale(float newScale){
	mScale = newScale;
}

uint32_t Entity::getScale(){
	return mScale;
}

void Entity::setPosition(float x,float y){
	float w,h;
	getWnH(w,h);
	mX = x-w/2;
	mY = y-h/2;
}

void Entity::getXnY(float& x,float& y){
	x = mX;
	y = mY;
}

void Entity::getWnH(float& w,float& h){
	int wid = 1;
	int hei = 1;
	SpriteComponent* sc = getCurrentSpriteComponent();
	if (sc != nullptr){
		sc->getWnH(wid,hei);
	}
	w = wid*mScale;
	h = hei*mScale;
}

void Entity::markToDestroy(){
	mMarkedToDestroy = true;
}

bool Entity::isMarkedToDestroy(){
	return mMarkedToDestroy;
}


void Entity::receiveInput(const uint32_t input){
	mLastInput = mLastInput | input;
}

void Entity::update(const double elapsed){
	if (mLastInput & MOVE_UP){
		mY-=mSpeedPerTick*elapsed;
	}
	else if (mLastInput & MOVE_DOWN){
		mY+=mSpeedPerTick*elapsed;
	}
	if (mLastInput & MOVE_RIGHT){
		mX+=mSpeedPerTick*elapsed;
	}
	else if (mLastInput & MOVE_LEFT){
		mX-=mSpeedPerTick*elapsed;
	}

}

void Entity::setState(State e){
	mState = e;
}