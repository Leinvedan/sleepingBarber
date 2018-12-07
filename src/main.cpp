#include <iostream>
#include "entity.h"
#include "gameEngine.h"
#include "spriteComponent.h"
#include "manager.h"
#include "salao.h"
#include <vector>
using namespace std;

class BarberShop{
private:
	Entity* mBarber;
	Entity* mBarberChair;
	Entity* mShopIcon;
	Entity* mShopCenter;
	Entity* mSleepIcon;
	Entity* mCuttingIcon;
	std::vector<Entity*> mChairs;
	std::vector<Entity*> mClients;
	Manager* man; //moves the clients and the barber in each iteration
	GameEngine* mGame;
public:
	BarberShop(uint32_t);//create the sprites and add them to the scene
	void openShop();//Starts the main loop
	Manager* getManager();
	GameEngine* getGameEngine();
};

GameEngine* BarberShop::getGameEngine(){
	return mGame;
}

BarberShop::BarberShop(uint32_t _nChairs){
	//Initializing variables
	mGame = new GameEngine();

	std::string path;
	SpriteComponent* sprComp;

	Entity* mBarber = new Entity();
	mChairs.clear();
	mChairs.resize(_nChairs);
	Entity* mShopIcon = new Entity();
	Entity* mBarberChair = new Entity();
	Entity* mShopCenter = new Entity();
	Entity* mSleepIcon = new Entity();
	Entity* mCuttingIcon = new Entity();

	//Sprite Components
	//barber
	path = "content/barber.png";
	sprComp = new SpriteComponent(mGame->getTexture(path));
	mBarber->addSpriteComponent(sprComp,Entity::IDLE);

	//barber shop icon
	path = "content/barberShop.png";
	sprComp = new SpriteComponent(mGame->getTexture(path));
	mShopIcon->addSpriteComponent(sprComp,Entity::IDLE);

	//sleep icon
	path = "content/sleep.png" ;
	sprComp = new SpriteComponent(mGame->getTexture(path));
	mSleepIcon->addSpriteComponent(sprComp,Entity::IDLE);

	//cutting
	path = "content/cutting.png" ;
	sprComp = new SpriteComponent(mGame->getTexture(path));
	mCuttingIcon->addSpriteComponent(sprComp,Entity::IDLE);

	//chairs
	path = "content/waitChair.png";
	sprComp = new SpriteComponent(mGame->getTexture(path));
	for (int i = 0; i < _nChairs; ++i){
		mChairs[i] = new Entity();
		mChairs[i]->addSpriteComponent(sprComp,Entity::IDLE);
		mChairs[i]->setPosition(64*(i+2),64*3);
		mGame->addToScene(mChairs[i]);
	}

	//barber chair
	path = "content/barberChair.png";
	sprComp = new SpriteComponent(mGame->getTexture(path));
	mBarberChair->addSpriteComponent(sprComp,Entity::IDLE);

	//add entities to the scene
	
	mGame->addToScene(mShopIcon);
	mGame->addToScene(mBarberChair);
	mGame->addToScene(mBarber);


	//attach camera
	mGame->attachCameraTo(mShopCenter);// move the camera to the center

	//adjust positions
	mShopCenter->setPosition(64*4,64*3); //camera's position
	mBarber->setPosition(64*4,64*5); //barber initial position
	mShopIcon->setPosition(64*3,64); //barber shop icon
	mBarberChair->setPosition(64*4,64*5); //barber chair
	mSleepIcon->setPosition(64*4,64*4.3);
	mCuttingIcon->setPosition(64*4,64*4.3);

	

	//Create 20 invisible clients
	for (int i = 0; i < 20; ++i){
		Entity* client = new Entity();
		client->setSpeed(2);
		path = "content/clientBefore.png";
		sprComp = new SpriteComponent(mGame->getTexture(path));
		client->addSpriteComponent(sprComp,Entity::IDLE);
		path = "content/clientAfter.png";
		sprComp = new SpriteComponent(mGame->getTexture(path));
		client->addSpriteComponent(sprComp,Entity::HAIRCUT);
		mGame->addToScene(client);
		//put out of the screen
		client->setPosition(-500,-500);
		//add to the vector
		mClients.push_back(client);
	}

	//add icons
	mSleepIcon->setScale(0.5);
	mCuttingIcon->setScale(0.5);
	mGame->addToScene(mSleepIcon);
	mGame->addToScene(mCuttingIcon);
	//set default visibility
	mSleepIcon->setState(Entity::IDLE);
	mCuttingIcon->setState(Entity::INVISIBLE);

	//Initialize manager:
	man = new Manager(mBarber,mBarberChair,mSleepIcon,mCuttingIcon,mChairs,mClients);
	man->setFirstChairPosition(64,64*3);
	man->setBarberChairPosition(64*4,64*5);
	man->setBarberPosition(64*5-20,64*4+30);
	mGame->subscribeToActionKeys(man);// subscribe to receive input
	mGame->addToScene(man); //add manager to the scene

}

void BarberShop::openShop(){
	//start scene
	mGame->setScene("content/layout.map");
	mGame->mainLoop();
	mGame->quit();
}

Manager* BarberShop::getManager(){
	return man;
}

int main(){

	uint32_t nChairs = 5;

	
    

	//Initialize the shop
	BarberShop bs(nChairs);
	//get the manager
    Manager* manager = bs.getManager();

    //start threads
	Salao S(nChairs,manager,bs.getGameEngine());
    S.inicializa_barbeiro();
    S.inicializa_clientes();
    printf("acabou threads\n");
    //sleep(10);


    //start graphic interface
	bs.openShop();

	
}