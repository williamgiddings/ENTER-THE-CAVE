#include "BG.h"
#include "WG_GameBackend.h"
#include "Objects.h"
#include <iostream>


void BackGround::Update()
{
	if (Game::thisGame->player->alive)
	{
		Scroll(scrollSpeed*Game::thisGame->scrollMultiplyer);
	}
}

void BackGround::FillInit()
{
	
	vines = ENTITIES_BACKGROUNDVINE;
	vines->SetScale(15, 15);
	vines->SetPosition(Game::thisGame->SCREENX, 140);
	bgcave = std::vector<Sprite*>(4, NULL);
	cave = std::vector<Sprite*>(3, NULL);

	int x = 0;
	for (auto &elem : bgcave)
	{
		elem = ENTITIES_BACKGROUNDCAVE;
		elem->SetScale(10, 10);
		elem->SetPosition(elem->transform.w*x, 40);
		x++;
	}
	x = 0;
	for (auto &elem : cave)
	{
		elem = ENTITIES_CAVE;
		elem->SetScale(5, 5);
		elem->SetPosition(elem->transform.w*x, 40);
		x++;
	}

}

void BackGround::Render(SDL_Renderer *r)
{
	for (auto &elem : cave)
	{
		elem->Render(r);
	}
	for (auto &elem : bgcave)
	{
		elem->Render(r);
	}
	
	vines->Render(r);
}

void BackGround::Scroll(int s)
{
	vines->transform.x -= vinespeed * Game::thisGame->scrollMultiplyer;

	for (int x = 0; x < bgcave.size(); x++) //cave background
	{
		bgcave[x]->transform.x -= (s*3) * Game::thisGame->scrollMultiplyer;
		if (bgcave[x]->transform.x <= 0 - bgcave[x]->transform.w)
		{
			int index = x - 1;
			if (index < 0)
			{
				index = bgcave.size()-1;
			}
			Sprite *last = bgcave[index];
			
			bgcave[x]->transform.x = (bgcave[index]->transform.x+ bgcave[index]->transform.w) + scrollSpeed * Game::thisGame->scrollMultiplyer;
		}
	}
	for (int x = 0; x < cave.size(); x++) //cave background
	{
		cave[x]->transform.x -= (s * 1) * Game::thisGame->scrollMultiplyer;
		if (cave[x]->transform.x <= 0 - cave[x]->transform.w)
		{
			int index = x - 1;
			if (index < 0)
			{
				index = cave.size() - 1;
			}
			Sprite *last = cave[index];

			cave[x]->transform.x = (cave[index]->transform.x + cave[index]->transform.w) + scrollSpeed * Game::thisGame->scrollMultiplyer;
		}
	}
	if (vines->transform.x <= 0-vines->transform.w)
	{
		vinespeed = s* (3 + rand() % 5);
		vines->SetPosition(Game::thisGame->SCREENX + (100 * (rand() % 3)), 140);
	}
}


