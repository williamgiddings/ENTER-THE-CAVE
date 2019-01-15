#include "Objects.h"
#include "WG_Collider.h"

void ENTITY_GROUND_TILE::Update()
{
	WG_GameObject::sprite->transform.y += WG_GameObject::velocity->y;
	WG_GameObject::sprite->transform.x += WG_GameObject::velocity->x;
}

ENTITY_GROUND_TILE::ENTITY_GROUND_TILE(Sprite *s)
{
	WG_GameObject::sprite = s;
	name = "terrain";
}

ENTITY_GROUND_TILE::ENTITY_GROUND_TILE(Sprite *s, bool f)
{
	WG_GameObject::sprite = s;
	name = "terrain";
	if (f)
	{
		 flip = SDL_FLIP_VERTICAL;
	}
}


void ENTITY_GROUND_TILE::Render(SDL_Renderer *r)
{
	WG_GameObject::sprite->Render(r, flip);

	if (WG_GameObject::collider != NULL)
	{
		WG_GameObject::collider->Render();
	}
	if (co != NULL)
	{
		co->transform->Render(r);
	}
}

