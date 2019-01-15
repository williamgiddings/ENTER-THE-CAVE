#pragma once
#include "WG_Vector.h"
#include <vector>
#include "WG_GameBackend.h"
#include "WG_GameObject.h"

class BackGround : public Entity
{
public:
	std::vector<Sprite*> bgcave;
	Sprite *vines;
	Sprite *background;
	std::vector<Sprite*> cave;
	int scrollSpeed = 1;
	SDL_Renderer *renderer;
	int vinespeed;
	int tileX = 18;
	int tileY = 9;

	BackGround(Sprite *s, SDL_Renderer *r)
	{
		renderer = r;
		background = s;
		FillInit();
	}

	void Update() override;
	void Scroll(int s);
	void FillInit();
	void Render(SDL_Renderer *r) override;
	~BackGround()
	{
		delete background;
		delete vines;
		for (auto &ctile : bgcave)
		{
			delete ctile;
			ctile = NULL;
		}
		background = NULL;
		vines = NULL;
	}
};