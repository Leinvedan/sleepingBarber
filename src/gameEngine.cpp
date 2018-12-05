
#include "gameEngine.h"
#include "entity.h"
#include <SDL2/SDL.h>
#include <algorithm> //find algorithm

//static methods
double GameEngine::getCurrentTime(){
	//Get the current time in milliseconds
	auto current_time = std::chrono::system_clock::now();
	auto duration_in_seconds = std::chrono::duration<double>(current_time.time_since_epoch());
	return duration_in_seconds.count()/1000;
}

void GameEngine::getMouseXnY(float& x,float& y){
	int xMouse,yMouse;
	SDL_GetMouseState(&xMouse,&yMouse);
	x = xMouse;
	y = yMouse;
}

//other methods
GameEngine::GameEngine(){
	mGScreen = new GameScreen();
	mGScreen->initialize("Barber shop!");
}


GameEngine::~GameEngine(){
	delete mGScreen;
}

SDL_Texture* GameEngine::getTexture(std::string path){
	return (mGScreen->loadTexture(path));
}


void GameEngine::setScene(std::string path){
	mGScreen->setCurrentScene(path);
}

void GameEngine::mainLoop(){
	double previous = getCurrentTime();
	double lag = 0.0;
	bool quit = false;

	//Temp fps counter--------------------------------------
	uint32_t frames = 0;
	double startTime = getCurrentTime()*1000;
	double endTime;
	//Temp fps counter end----------------------------------
	while(!quit){
		double current = getCurrentTime();
		double elapsed = current - previous;
		previous = current;
		lag+= elapsed;
		quit = handleInput();//INPUT
		while (lag>= MS_PER_UPDATE){
			updateScene(lag/MS_PER_UPDATE);
			lag-=MS_PER_UPDATE;
			//temp----------------------------------
			frames++;
			endTime = getCurrentTime()*1000;
			if (endTime-startTime >=1){
				std::cout << "FPS: "<<frames << std::endl;
				startTime = getCurrentTime()*1000;
				frames = 0;
			}
			//temp end-----------------------------
		}
		handleRendering();//RENDERING
	}
}

void GameEngine::quit(){
	mGScreen->closeSDL();
}

bool GameEngine::handleInput(){
	SDL_Event e;
	bool quit = false;
	uint32_t mouseEvents = 0;
	while(SDL_PollEvent(&e)){
		//close screen
		if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
			quit = true;
		}
		//mouse events
		//Left and right mouse button
		if (e.type == SDL_MOUSEBUTTONDOWN){
			if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
				mouseEvents += ACTION_1;
			else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
				mouseEvents += ACTION_2;
		}
		//Mouse Wheel
		if (e.type == SDL_MOUSEWHEEL){
			if(e.wheel.y > 0) //up
				mouseEvents+=SWITCH_STANCE_NEXT;
			else if(e.wheel.y < 0) //down
				mouseEvents+=SWITCH_STANCE_PREV;
		}
	}
	
	//Keyboard keys
	const uint8_t *keyState = SDL_GetKeyboardState(NULL);
	sendEventToSubscribers(keyState,mouseEvents);

	return quit;
	
}

void GameEngine::subscribeToActionKeys(Entity* ent){
	mActionKeysSubscribe.push_back(ent);
}

void GameEngine::sendEventToSubscribers(const uint8_t* keyState,const uint32_t mouseEvents){
	uint32_t value = mouseEvents;
	double currentTime = getCurrentTime();

	//Read the keys
	if (keyState[SDL_SCANCODE_W]) // W
		value = value | MOVE_UP;

	if (keyState[SDL_SCANCODE_A]) // A
		value = value | MOVE_LEFT;

	if (keyState[SDL_SCANCODE_S]) // S
		value = value | MOVE_DOWN;

	if (keyState[SDL_SCANCODE_D]) // D
		value = value | MOVE_RIGHT;

	if (keyState[SDL_SCANCODE_SPACE])
		value = value | ACTION_3;

	if (keyState[SDL_SCANCODE_LSHIFT])
		value = value | RUN;

	//Send value to subscribers
	for(Entity* ent: mActionKeysSubscribe){
		ent->clearInputBuffer();  //clear the previous commands
		ent->receiveInput(value); //Add the new commands
	}
}


void GameEngine::addToScene(Entity* e){
	//add entity to update
	mSceneEntities.push_back(e);
}

void GameEngine::emptyBuffer(){
	for(Entity* ent: mSceneBuffer){
		addToScene(ent); //add entities to the scene
	}
	mSceneBuffer.clear();//clear the buffer
}
void GameEngine::updateScene(const double elapsed){
	for(std::vector<Entity*>::iterator it = mSceneEntities.begin(); it != mSceneEntities.end();){
		Entity* ent = (*it);
		if (ent->isMarkedToDestroy()){
			mSceneEntities.erase(it);//erase entity from vector
			delete ent;//this will delete the hitbox as well
		}
		else{
			ent->update(elapsed);
			it++;//advance to the next entity if it wasn't deleted
		}
	}
	emptyBuffer();
}

void GameEngine::handleRendering(){
	mGScreen->clearRenderer(); //prepare renderer

	//update camera Size (if window size changed)
	mGScreen->updateCameraSize();
	//render background
	mGScreen->renderBackground();
	//rendering entities
	for(Entity* ent: mSceneEntities){
		mGScreen->renderEntity(ent);
	}

	//clear renderer
	mGScreen->renderFinal();

}

void GameEngine::attachCameraTo(Entity* e){
	mGScreen->attachCameraTo(e);
}
