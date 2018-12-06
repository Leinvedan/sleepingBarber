
#include "gameScreen.h"

int GameScreen::initialize(std::string windowName){
	
	//Start SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		logSDLError(std::cout,"SDL_Init");
		return 1;
	}

	//Loading SDL_Image (Enable loading png files)
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;
	}

	//Create window
	mWindow = SDL_CreateWindow(windowName.c_str(),100,100,SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (mWindow == nullptr){
		logSDLError(std::cout,"SDL_Create window");
		SDL_Quit();
		return 1;
	}
	SDL_SetWindowResizable(mWindow,SDL_TRUE);

	//Create renderer
	mRenderer = SDL_CreateRenderer(mWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr){
		SDL_DestroyWindow(mWindow);
		logSDLError(std::cout,"SDL_CreateRenderer");
		return 1;
	}


	//set window icon
	SDL_Surface* icon = SDL_LoadBMP("content/icon.bmp");
	if (icon == NULL) printf("deu ruim\n");
	SDL_SetWindowIcon(mWindow,icon);
	SDL_FreeSurface(icon);

	return 0;
}

void GameScreen::setCurrentScene(std::string scenePath){
	//clear the old scene object
	if (mCurrentScene != nullptr){
		delete mCurrentScene;
	}

	//create scene
	mCurrentScene = new GameScene(scenePath);
	//clear the texture array of the previous scene
	for(SDL_Texture* tex : mSceneTilesTex){
		SDL_DestroyTexture(tex);
	}
	mSceneTilesTex.clear();
	mSceneTilesTex.resize(mCurrentScene->getTotalTileVariants());

	//load images in the renderer and the textures array
	for (int i = 0; i < mCurrentScene->getTotalTileVariants(); ++i){
		std::string path = mCurrentScene->getTileTexFilePath(i);
		mSceneTilesTex[i] = loadTexture(path.c_str());
	}
}



void GameScreen::logSDLError(std::ostream &os, const std::string & msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* GameScreen::loadTexture(const std::string &file){
	//--> Loads a BMP/PNG image into the renderer
	SDL_Texture *texture = nullptr;
	texture = IMG_LoadTexture(mRenderer,file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}

void GameScreen::renderTexture(SDL_Texture *tex,SDL_Rect dst,SDL_Rect *clip = nullptr){
	//* Draw an SDL_Texture to an SDL_Renderer at some destination rect
	//* taking a clip of the texture if desired
	SDL_RenderCopy(mRenderer,tex,clip,&dst);
}

void GameScreen::renderTexture(SDL_Texture *tex, int x, int y,SDL_Rect *clip = nullptr){
	//Draw an SDL_Texture to an SDL_Renderer at position x,y preserving
	//the texture width and height and TAKING A CLIP OF THE TEXTURE if desired
	//if a clip is passed, the CLIP'S WIDTH AND HEIGHT WILL BE USED INSTEAD.
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr){
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else{
		SDL_QueryTexture(tex,NULL,NULL,&dst.w,&dst.h);
	}
	renderTexture(tex,dst,clip);
}

void GameScreen::renderTexture(SDL_Texture * tex,int x,int y,int w,int h){
	//Draw an texture to an renderer at position x,y changing
	//the proportions
	SDL_Rect dst;//destination position as an rectangle
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(mRenderer,tex,NULL,&dst);
}

void GameScreen::renderTexture(SDL_Texture * tex,int x,int y){
	//Draw an texture to an renderer at position x,y preserving
	//the proportions
	int w,h;
	//get texture original width and height
	SDL_QueryTexture(tex,NULL,NULL,&w,&h);
	renderTexture(tex,x,y,w,h);
}

void GameScreen::closeSDL(){
	SDL_DestroyRenderer(mRenderer);
	//destroy textures
	SDL_DestroyWindow(mWindow);
	IMG_Quit();
	SDL_Quit();
}

void GameScreen::getWindowWidthHeight(int& w, int& h){
	SDL_GetWindowSize(mWindow,&w,&h);
}


void GameScreen::attachCameraTo(Entity* e){
	mCamera.attachTo(e);
}

void GameScreen::updateCameraSize(){
	int32_t w,h;
	getWindowWidthHeight(w,h);
	mCamera.setCameraSize(w,h);
}

void GameScreen::fillBackgroundTiles(){
	uint32_t tileW,tileH;
	mCurrentScene->getTilesWnH(tileW,tileH); 
	//camera position
	float camX,camY;
	uint32_t camScale = mCamera.getScale();
	mCamera.getXnY(camX,camY);
	//tile number and size (*2 is TEMP!!!!!!!!)
	float tileWidth = tileW*camScale;
	float tileHeight = tileH*camScale;
	int lineTiles = mCurrentScene->getTotalLineTiles();
	int columnTiles = mCurrentScene->getTotalColumnTiles();
	
	//drawning the tiles
	for (uint32_t l = 0; l < lineTiles; l++){
		for (uint32_t c = 0; c < columnTiles; c++){
			float posX = tileHeight*c;
			float posY = tileWidth*l;
			if (isVisible(posX,posY)){
				uint32_t targetTile = mCurrentScene->getTileReferenceFromMap(l,c);
				renderTexture(mSceneTilesTex[targetTile],posX-camX,posY-camY,tileHeight,tileWidth);
			}
		}
	}
}

bool GameScreen::isVisible(float x,float y){
	return mCamera.checkVisible(x,y);
}

//scene rendering
void GameScreen::clearRenderer(){
	SDL_RenderClear(mRenderer);
}
void GameScreen::renderBackground(){
	fillBackgroundTiles();
	//fill the props()
}

void GameScreen::renderEntity(Entity* ent){
	SpriteComponent* sc = ent->getCurrentSpriteComponent();
	if (sc != nullptr){
		float entX,entY,entW,entH;
		ent->getXnY(entX,entY);
		ent->getWnH(entW,entH);
		SDL_Rect target;
		//camera position
		float camX,camY;
		uint32_t camScale = mCamera.getScale();
		mCamera.getXnY(camX,camY);
		//entity position
		target.w = entW * camScale;
		target.h = entH * camScale;
		target.x =  entX - target.w /2 - camX;
		target.y =  entY - target.h/2 - camY;

		SDL_Rect clip = sc->getNextFrameRect();
		renderTexture(sc->getTexture(),target,&clip);

	}
	/*
	else{
		printf("Error: entity[%d] state's animation doesn't exist!!\n",ent->getID());
	}
	*/
}
void GameScreen::renderFinal(){
	SDL_RenderPresent(mRenderer);
}

void GameScreen::getCameraXnY(float& x,float& y){
	mCamera.getXnY(x,y);
}

Camera* GameScreen::getCamera(){
	return &mCamera;
}