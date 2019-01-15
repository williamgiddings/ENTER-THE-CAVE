#pragma once
#include "GrappleHook.h"
#include "WG_GameBackend.h"
#include "WG_Collider.h"
#include "Sprite.h"


GrappleLine::GrappleLine(SDL_Rect *o)
{
	hook = new Hook(this);
	gsound = Mix_LoadWAV("./assets/sounds/effects/grapple.wav");
	origin = o;	
}

void GrappleLine::Fire()
{
	originX = origin->x + origin->w / 2;
	originY = origin->y + origin->h / 2;
	Mix_PlayChannel(-1, gsound, 0);
	if (!hook->firing)
	{
		hook->Fire();
	}
	
}


void GrappleLine::Attatch(WG_Vector2 anchor)
{
	hook->firing = false;
	active = true;
	anchorX = anchor.x;
	anchorY = anchor.y;
	timeDeployed = SDL_GetTicks();
}



void GrappleLine::Update()
{
	if (active)
	{
		originX = origin->x + origin->w / 2;
		originY = origin->y + origin->h / 2;

		if (abs(Game::thisGame->player->velocity->y) < 7)
		{
			Game::thisGame->player->velocity->y += -3;
		}
		
		if (SDL_GetTicks() >= (timeDeployed + 600))
		{
			Detatch();
		}
		
	}
	hook->Update();
}

void GrappleLine::Render(SDL_Renderer * r)
{
	if (active || hook->firing)
	{
		SDL_SetRenderDrawColor(r, 102, 51, 0, 0);
		SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_NONE);
		for (int i = 0; i < 10; i++)
		{
			SDL_RenderDrawLine(r, originX+i, originY + i, (hook->transform->x + hook->transform->w/2) + i, (hook->transform->y + hook->transform->h /2) + i);
		}
		
		hook->Render(r);
	}
}

Hook::Hook(GrappleLine *g)
{
	grapple = g;
	velocity = new WG_Vector2(0, 0);
	hookSprite = new Sprite("./assets/sprites/grapple.png", new WG_Vector2(0, 0), new WG_Vector2(12, 8), Game::thisGame->renderer);
	hookSprite->SetScale(3, 3);
	transform = &hookSprite->transform;
	transform->x = grapple->originX;
	transform->y = grapple->originY;
	hookCollider = new WG_Collider(transform);
	hookCollider->trigger = true;
	hookCollider->HookVelocity(velocity);
}

void Hook::Render(SDL_Renderer * r)
{
	hookCollider->Render();
	hookSprite->Render(r);
}

void Hook::Fire()
{
	firing = true;
	transform->x = grapple->origin->x;
	transform->y = grapple->origin->y;
}

void Hook::Update()
{
	velocity->y = 0;
	if (firing)
	{
		velocity->y = grapple->hookspeed;
		velocity->x = 5;
		hookCollider->TestCollisions();
		CheckCollisions();
	}
	transform->x += velocity->x;
	transform->y += velocity->y;
}

void Hook::CheckCollisions()
{
	for (auto& other : hookCollider->collidingObjects)
	{
		if (other->collider->gameObject->name == "terrain")
		{
			grapple->Attatch(WG_Vector2(transform->x, transform->y));
			velocity->x = other->collider->gameObject->velocity->x;
		}
		else if (other->collider->gameObject->name == "spikes")
		{
			grapple->Detatch();
		}
	}
}

void GrappleLine::Detatch()
{
	hook->firing = false;
	active = false;

}