#pragma once
#include "WG_Vector.h"
#include "SDL.h"
#include "Sprite.h"
#include "SDL_mixer.h"

class WG_Collider;
class GrappleLine;

class Hook
{
public:
	Hook(GrappleLine *g);
	~Hook()
	{
		delete velocity;
		delete hookCollider;
		delete hookSprite;
		velocity = NULL;
		transform = NULL;
		hookCollider = NULL;
		hookSprite = NULL;
	};
	void Render(SDL_Renderer *r);
	void Update();
	void Fire();
	void CheckCollisions();
	Sprite *hookSprite;
	
	bool firing = false;
	WG_Vector2 *velocity;
	SDL_Rect *transform;
	WG_Collider *hookCollider;
	GrappleLine *grapple;


};

class GrappleLine
{
public:
	Uint32 timeDeployed = 0;
	SDL_Rect *origin; //player
	Mix_Chunk *gsound;
	Hook *hook;
	int anchorX;
	int anchorY;
	int originX;
	int originY;
	float scale = 6;
	int hookspeed = 25;
	bool active = false;

	GrappleLine(SDL_Rect *o);
	~GrappleLine()
	{
		delete hook;
		hook = NULL;
	};
	void Update();
	void Fire();
	void Detatch();
	void Attatch(WG_Vector2 anchor);
	void Render(SDL_Renderer *r);

};