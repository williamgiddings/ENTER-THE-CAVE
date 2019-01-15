#pragma once
#include "Physics.h"
#include "WG_Collider.h"
#include "WG_Gamebackend.h"
#include <iostream>
#include "WG_GameObject.h"

void WG_Collider::HookVelocity(WG_Vector2 * vhook)
{
	velocity = vhook;
}

CollisionData *WG_Collider::GetCollision(WG_GameObject *go)
{
	WG_Vector2 *colData = NULL;

	if (go->collider != NULL && go->collider != this)
	{
		SDL_Rect* colRect = go->collider->boundingbox;


		leftA = colRect->x;
		rightA = colRect->x + colRect->w;
		topA = colRect->y;
		bottomA = colRect->y + colRect->h;

		leftB = this->boundingbox->x;
		rightB = this->boundingbox->x + this->boundingbox->w;
		topB = this->boundingbox->y;
		bottomB = this->boundingbox->y + this->boundingbox->h;

		WG_Vector2 v = WG_Vector2(0,0);
		if (gameObject != NULL)
		{
			v = *gameObject->velocity;
		}
		else if (velocity != NULL)
		{
			v = *velocity;
		}


		if (bottomA >= topB + v.y && topB >= topA) {
			//hit head on object
			if (rightA >= leftB && leftB >= leftA)
			{
				if (colData == NULL)
				{
					colData = new WG_Vector2(0, 0);
				}
				colData->y = -1;
			}
			
		}
		if (topA <= bottomB + v.y && bottomB <= bottomA) {
			//on top
			if (rightA >= leftB && leftB >= leftA)
			{
				if (colData == NULL)
				{
					colData = new WG_Vector2(0, 0);
				}
				colData->y = 1;
			}
			
		}
		if (rightA >= leftB && leftB >= leftA) {
			//left
			if (topA < bottomB && topB + -v.y < bottomA || bottomA > topB + -v.y &&  topA < bottomB)
			{ 
				if (colData == NULL)
				{
					colData = new WG_Vector2(0, 0);
				}
				colData->x = -1;

			}				
		}
		if (leftA <= rightB && rightB <= rightA) {
			//right
	
			if (topA < bottomB && topB < bottomA || bottomA > topB  &&  topA < bottomB) /*topA < bottomB && bottomB < bottomA || bottomA > topB  &&  topA < bottomB*/
			{
				if (colData == NULL)
				{
					colData = new WG_Vector2(0, 0);
				}
				colData->x = 1;
			}
		}
		if (colData != NULL)
		{
			if (gameObject != NULL)
			{
				std::cout << "COLLISION: " << gameObject->name << std::endl;
			}
			
		}
	}

	return new CollisionData(go->collider, colData);
}


void WG_Collider::TestCollisions()
{

	collidingObjects.erase(collidingObjects.begin(), collidingObjects.end());
	/*int XMin = boundingbox->x / Game::thisGame->CollisionChunkSizeX;
	int YMin = boundingbox->y / Game::thisGame->CollisionChunkSizeY;
	int XMax = boundingbox->x+ boundingbox->w / Game::thisGame->CollisionChunkSizeX;
	int YMax = boundingbox->y + boundingbox->h / Game::thisGame->CollisionChunkSizeY;

	std::vector<std::string> coordinates = {};

	int xDiff = abs(XMin - XMax)/ Game::thisGame->CollisionChunkSizeX;
	int yDiff = abs(YMin - YMax)/ Game::thisGame->CollisionChunkSizeY;
	for (int x = 0; x <= xDiff; x++)
	{
		for (int y = 0; y <= yDiff; y++)
		{
			std::string coords = std::to_string(XMin + x) + "," + std::to_string(YMin + y);
			coordinates.push_back(coords);
		}
	}
	

	for (auto& coord : coordinates)
	{
		for (auto &gameObject : Game::thisGame->physics->collisionMap[coord])
		{

			CollisionData cd = this->GetCollision(gameObject);

			if (cd.collisionVector != NULL)
			{
				collidingObjects.push_back(cd);
			}

		}
	}*/

	for (auto &gameObject :  Game::thisGame->gameObjects)
	{

		CollisionData *cd = this->GetCollision(gameObject);

		if (cd->collisionVector != NULL)
		{
			collidingObjects.push_back(cd);
			gameObject->collider->collisionTables.push_back(&collidingObjects);
		}

	}

	
	
}

void WG_Collider::Render()
{
	if (drawCollider)
	{
		SDL_SetRenderDrawColor(Game::thisGame->renderer, 0, 255, 0, 0);
		SDL_RenderDrawRect(Game::thisGame->renderer, boundingbox);
	}
}

WG_Collider::WG_Collider(SDL_Rect *r)
{
	boundingbox = r;
}

WG_Collider::WG_Collider(WG_GameObject *gm) : boundingbox(&gm->sprite->transform), trigger(false), colliderType(DYNAMIC) {
	gameObject = gm;
	boundingbox->y += boundingbox->h / 2;
	boundingbox->x += boundingbox->w / 2;

};
WG_Collider::WG_Collider(WG_GameObject *gm, WG_Vector2 &vel) : boundingbox(&gm->sprite->transform), trigger(false), colliderType(DYNAMIC), velocity(&vel) {
	gameObject = gm;
	boundingbox->y += boundingbox->h / 2;
	boundingbox->x += boundingbox->w / 2;

};
WG_Collider::WG_Collider(WG_GameObject *gm, WG_Vector2 &vel, bool t) : boundingbox(&gm->sprite->transform), velocity(&vel), trigger(t), colliderType(DYNAMIC) {
	gameObject = gm;
	boundingbox->y += boundingbox->h / 2;
	boundingbox->x += boundingbox->w / 2;

};
WG_Collider::WG_Collider(WG_GameObject *gm, WG_Vector2 &vel, bool t, ColliderType type) : boundingbox(&gm->sprite->transform), velocity(&vel), trigger(t), colliderType(type) {
	gameObject = gm;
	boundingbox->y += boundingbox->h / 2;
	boundingbox->x += boundingbox->w / 2;

};