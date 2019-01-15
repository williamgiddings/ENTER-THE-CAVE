#include "Objects.h"
#include "WG_GameBackend.h"


ENTITY_COIN::ENTITY_COIN(Sprite * s)
{
	WG_GameObject::sprite = s;
	SetAnimator(new Animator(s, Game::thisGame->renderer));
	animator->animations.push_back
	(
		new Animation("Idle", "./assets/sprites/coin.png", std::vector<AnimationFrame*>
		{
			new AnimationFrame(new WG_Vector2(0, 0), new WG_Vector2(32, 32), 100),
			new AnimationFrame(new WG_Vector2(32, 0), new WG_Vector2(32, 32), 100),
			new AnimationFrame(new WG_Vector2(64, 0), new WG_Vector2(32, 32), 100),
			new AnimationFrame(new WG_Vector2(96, 0), new WG_Vector2(32, 32), 100),
			new AnimationFrame(new WG_Vector2(128, 0), new WG_Vector2(32, 32), 100),
			new AnimationFrame(new WG_Vector2(160, 0), new WG_Vector2(32, 32), 100),
			new AnimationFrame(new WG_Vector2(192, 0), new WG_Vector2(32, 32), 100),
			new AnimationFrame(new WG_Vector2(224, 0), new WG_Vector2(32, 32), 100),
			new AnimationFrame(new WG_Vector2(256, 0), new WG_Vector2(32, 32), 100)
		}
	));
	name = "coin";
	animator->Play("Idle");
	animator->loop = true;
}

void ENTITY_COIN::Render(SDL_Renderer * r)
{
	sprite->Render(r);
}

void ENTITY_COIN::Update()
{
	sprite->transform.x += velocity->x;
	animator->Update();
}



void ENTITY_COIN::SetAnimator(Animator * a)
{
	animator = a;
}