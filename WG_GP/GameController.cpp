#include "WG_GameBackend.h"
#include "WG_GameObject.h"
#include <algorithm>
#include "WG_Collider.h"
#include <iostream>
#include <vector>

Game *Game::thisGame;


WG_GameObject *Instantiate(WG_GameObject *object)
{
	std::cout << "INSTANTIATED: " << object->name << "(" << object << ")" << std::endl;
	Game::thisGame->gameObjects.push_back(object);
	return object;
}

GroundTile *Instantiate(GroundTile * object)
{
	object->WG_GameObject::ID = Game::thisGame->gameObjects.size();
	Game::thisGame->gameObjects.push_back(object);
	return object;
}



void Destroy(WG_GameObject *object)
{
	Game::thisGame->gameObjects.erase(std::remove(Game::thisGame->gameObjects.begin(), Game::thisGame->gameObjects.end(), object), Game::thisGame->gameObjects.end());
	if (object != NULL)
	{
		delete object;
		object = nullptr;
	}
	
		
}

void Destroy(GroundTile *object)
{
	Game::thisGame->gameObjects.erase(std::remove(Game::thisGame->gameObjects.begin(), Game::thisGame->gameObjects.end(), object), Game::thisGame->gameObjects.end());
	object->collider->alive = false;
	delete object;
	object = nullptr;

}


