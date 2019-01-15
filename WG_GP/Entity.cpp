#include "WG_GameObject.h"
#include "SDL.h"
#include "WG_Collider.h"


void Entity::Render(SDL_Renderer *r)
{
	if (sprite != NULL)
	{
		sprite->Render(r);
	}
	
	if (collider != NULL)
	{
		collider->Render();
	}
}

