#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <list>
#include <vector>
#include "entity.h"
#include "gameScene.h"
#include "camera.h"

//Handles the render system

class GameScreen{
private:
	SDL_Renderer* mRenderer = nullptr;
	SDL_Window* mWindow = nullptr;
	std::list<Entity*> mSceneEntities;
	GameScene* mCurrentScene = nullptr;
	std::vector<SDL_Texture*> mSceneTilesTex;
	Camera mCamera;
	TTF_Font* mFont;
	std::string mDisplayText;

	void logSDLError(std::ostream &, const std::string&);
	void renderTexture(SDL_Texture*, SDL_Rect, SDL_Rect*);
	void renderTexture(SDL_Texture*, int, int, SDL_Rect*);
	void renderTexture(SDL_Texture*, int, int, int, int);
	void renderTexture(SDL_Texture*, int, int);
public:
	//default screen initialization values
	const int SCREEN_WIDTH  = 640;
	const int SCREEN_HEIGHT = 480;


	GameScreen(){};
	int initialize(std::string);
	void setCurrentScene(std::string);
	void fillBackgroundTiles();
	SDL_Texture* loadTexture(const std::string&);
	void loadScene();
	//ratio
	void getWindowWidthHeight(int&,int&);
	//rendering the game
	void clearRenderer();
	void renderBackground();
	void renderEntity(Entity*);
	void renderFinal();
	void closeSDL();
	void attachCameraTo(Entity*);
	void updateCameraSize();
	bool isVisible(float,float);
	void getCameraXnY(float&,float&);
	Camera* getCamera();
	void changeText(std::string);

};


#endif