#include <iostream>
#include "entity.h"
#include "gameEngine.h"
#include "spriteComponent.h"
using namespace std;

int main(){

	//Initializing variables
	GameEngine* game = new GameEngine();

	std::string path;
	SpriteComponent* sprComp;

	uint32_t nChairs = 5;//!!!limit the number of chairs to 5

	Entity* charlie = new Entity();
	Entity* chairs[nChairs];
	Entity* barberShop = new Entity();
	Entity* barberChair = new Entity();
	Entity* shopCenter = new Entity();


	//Sprite Components
	//barber
	path = "content/barber.png";
	sprComp = new SpriteComponent(game->getTexture(path));
	charlie->addSpriteComponent(sprComp,Entity::IDLE);

	//barber shop icon
	path = "content/barberShop.png";
	sprComp = new SpriteComponent(game->getTexture(path));
	barberShop->addSpriteComponent(sprComp,Entity::IDLE);

	//chairs
	path = "content/waitChair.png";
	sprComp = new SpriteComponent(game->getTexture(path));
	for (int i = 0; i < nChairs; ++i){
		chairs[i] = new Entity();
		chairs[i]->addSpriteComponent(sprComp,Entity::IDLE);
		chairs[i]->setPosition(64*(i+2),64*3);
		game->addToScene(chairs[i]);
	}

	//barber chair
	path = "content/barberChair.png";
	sprComp = new SpriteComponent(game->getTexture(path));
	barberChair->addSpriteComponent(sprComp,Entity::IDLE);


	game->subscribeToActionKeys(charlie);
	//add entities to the scene
	game->addToScene(charlie);
	game->addToScene(barberShop);
	game->addToScene(barberChair);

	//attach camera
	game->attachCameraTo(shopCenter);// move the camera to the center

	//adjust positions
	shopCenter->setPosition(64*4,64*3); //camera's position
	charlie->setPosition(64*5,64*4); //barber initial position
	barberShop->setPosition(64*3,64); //barber shop icon
	barberChair->setPosition(64*4,64*5); //barber chair

	game->setScene("content/layout.map");
	game->mainLoop();
	game->quit();

	return 0;
	
}