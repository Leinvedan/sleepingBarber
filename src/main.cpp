#include <iostream>
#include "entity.h"
#include "gameEngine.h"
#include "spriteComponent.h"
#include "manager.h"
#include <vector>
using namespace std;

class BarberShop{
private:
	Entity* mBarber;
	Entity* mBarberChair;
	Entity* mShopIcon;
	Entity* mShopCenter;
	std::vector<Entity*> mChairs;
	std::vector<Entity*> mClients;
	Entity* man; //moves the clients and the barber in each iteration
public:
	BarberShop(){}
	void openShop(uint32_t); //Starts the main loop
};


void BarberShop::openShop(uint32_t _nChairs){
	//Initializing variables
	GameEngine* game = new GameEngine();

	std::string path;
	SpriteComponent* sprComp;

	Entity* mBarber = new Entity();
	mChairs.clear();
	mChairs.resize(_nChairs);
	Entity* mShopIcon = new Entity();
	Entity* mBarberChair = new Entity();
	Entity* mShopCenter = new Entity();


	//Sprite Components
	//barber
	path = "content/barber.png";
	sprComp = new SpriteComponent(game->getTexture(path));
	mBarber->addSpriteComponent(sprComp,Entity::IDLE);

	//barber shop icon
	path = "content/barberShop.png";
	sprComp = new SpriteComponent(game->getTexture(path));
	mShopIcon->addSpriteComponent(sprComp,Entity::IDLE);

	//chairs
	path = "content/waitChair.png";
	sprComp = new SpriteComponent(game->getTexture(path));
	for (int i = 0; i < _nChairs; ++i){
		mChairs[i] = new Entity();
		mChairs[i]->addSpriteComponent(sprComp,Entity::IDLE);
		mChairs[i]->setPosition(64*(i+2),64*3);
		game->addToScene(mChairs[i]);
	}

	//barber chair
	path = "content/barberChair.png";
	sprComp = new SpriteComponent(game->getTexture(path));
	mBarberChair->addSpriteComponent(sprComp,Entity::IDLE);

	//add entities to the scene
	game->addToScene(mBarber);
	game->addToScene(mShopIcon);
	game->addToScene(mBarberChair);

	//attach camera
	game->attachCameraTo(mShopCenter);// move the camera to the center

	//adjust positions
	mShopCenter->setPosition(64*4,64*3); //camera's position
	mBarber->setPosition(64*5,64*4); //barber initial position
	mShopIcon->setPosition(64*3,64); //barber shop icon
	mBarberChair->setPosition(64*4,64*5); //barber chair

	//Initialize manager:
	man = new Manager(mBarber,mBarberChair,mChairs,mClients);
	game->subscribeToActionKeys(man);// subscribe to receive input
	game->addToScene(man); //add manager to the scene

	//Create 20 invisible clients
	for (int i = 0; i < 20; ++i){
		Entity* client = new Entity();
		path = "content/clientBefore.png";
		sprComp = new SpriteComponent(game->getTexture(path));
		client->addSpriteComponent(sprComp,Entity::IDLE);
		path = "content/clientAfter.png";
		client->addSpriteComponent(sprComp,Entity::HAIRCUT);
		game->addToScene(client);
		//put out of the screen
		client->setPosition(-500,-500);
		//add to the vector
		mClients.push_back(client);
	}

	//start scene
	game->setScene("content/layout.map");
	game->mainLoop();
	game->quit();

}

int main(){
	BarberShop bs;
	bs.openShop(4);

	
}