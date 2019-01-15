#pragma once
#include "SDL.h"
#include "WG_GameObject.h"
#include "SDL_mixer.h"

class CoinSpawner
{
	SDL_Renderer *renderer;

public:
	WG_GameObject *coin;
	Mix_Chunk *grab;

	void Update();
	void Grab();
	void ResetCoin();
	CoinSpawner(SDL_Renderer *r);


};