#include "CoinSpawner.h"
#include "Objects.h"
#include "WG_GameBackend.h"
#include "WG_Collider.h"
#include <iostream>
#include <ctime>

CoinSpawner::CoinSpawner(SDL_Renderer *r)
{
	srand(time(NULL));
	renderer = r;
	coin = Instantiate(ENTITIES_COIN);
	coin->name = "coin";
	coin->SetScale(4, 4);
	coin->SetPosition(Game::thisGame->SCREENX+200, 240);
	coin->AddCollider(new WG_Collider(coin));
	coin->collider->trigger = true;
	grab = Mix_LoadWAV("./assets/sounds/effects/coin.wav");

}

void CoinSpawner::Update()
{
	coin->velocity->x = 0;
	if (coin->velocity->x < Game::thisGame->terrain->curScrollSpeed)
	{
		coin->velocity->x -= Game::thisGame->terrain->curScrollSpeed;
	}

	if (coin->sprite->transform.x <= 0 - coin->sprite->transform.w)
	{
		ResetCoin();
	}

}

void CoinSpawner::Grab()
{
	Game::thisGame->AddCoin(1);
	Mix_PlayChannel(-1, grab, 0);
	ResetCoin();
}

void CoinSpawner::ResetCoin()
{
	coin->SetPosition(Game::thisGame->SCREENX + (100 * rand() % 7), 240 + rand() % (Game::thisGame->SCREENY - 240));
}