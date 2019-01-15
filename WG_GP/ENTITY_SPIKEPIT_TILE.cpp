#include "Objects.h"
#include "WG_Collider.h"
#include "WG_GameBackend.h"

void ENTITY_SPIKEPIT_TILE::Update()
{
	WG_GameObject::sprite->transform.y += WG_GameObject::velocity->y;
	WG_GameObject::sprite->transform.x += WG_GameObject::velocity->x;
}

ENTITY_SPIKEPIT_TILE::ENTITY_SPIKEPIT_TILE(Sprite *s)
{
	WG_GameObject::sprite = s;
	name = "spikes";
}

ENTITY_SPIKEPIT_TILE::ENTITY_SPIKEPIT_TILE(Sprite *s, bool f)
{
	WG_GameObject::sprite = s;
	if (f)
	{
		flip = SDL_FLIP_VERTICAL;
	}
	name = "spikes";
}

void ENTITY_SPIKEPIT_TILE::Interact()
{
	if (!triggered)
	{
		triggered = true;
		sprite->SetTexture(&WG_Vector2(0,0), &WG_Vector2(32, 30), Game::thisGame->renderer);
	}
	
}

void ENTITY_SPIKEPIT_TILE::Render(SDL_Renderer *r)
{
	WG_GameObject::sprite->Render(r, flip);

	if (WG_GameObject::collider != NULL)
	{
		WG_GameObject::collider->Render();
	}
}
