#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <chrono>
#include <cstdint>
#include <SDL2/SDL.h>
#include <list>
#include <vector>

#include "gameScreen.h"
#include "gameScene.h"
#include "entity.h"


//Handles the main game loop and events

class GameEngine{
private:
	//event subscriptions
	std::list<Entity*> mActionKeysSubscribe;
	std::vector<Entity*> mSceneEntities;
	std::vector<Entity*> mSceneBuffer; //used to keep the newly created entities and send them all
									  //to the mSceneEntities

public:
	GameScreen* mGScreen;
	const double MS_PER_UPDATE = 0.000016;
	GameEngine();
	~GameEngine();
	static double getCurrentTime();
	static void getMouseXnY(float&,float&);
	void mainLoop();
	void setScene(std::string);
	bool handleInput();
	void emptyBuffer();
	void updateScene(const double);
	void handleRendering();
	void subscribeToActionKeys(Entity*);
	void sendEventToSubscribers(const uint8_t*,const uint32_t);
	void addToScene(Entity*);
	void quit();
	void attachCameraTo(Entity*);
	SDL_Texture* getTexture(std::string);
	

};




#endif