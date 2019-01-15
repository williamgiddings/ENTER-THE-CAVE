#pragma once
#include "Terrain.h"
#include "WG_GameBackend.h"
#include "WG_Collider.h"
#include "WG_GameObject.h"
#include "CoinSpawner.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <ctime>


Terrain::Terrain(SDL_Renderer *r)
{
	srand(time(NULL));
	renderer = r;
	coinspawn = new CoinSpawner(r);
	terrainTiles = std::vector<std::vector<GroundTile*>>(2, std::vector<GroundTile*>(tileY, NULL));
	curScrollSpeed = defaultScrollSpeed * Game::thisGame->scrollMultiplyer;
	Initialize();
}

Terrain::~Terrain()
{
	for (auto& clut : clutterPool) //delete clutter;
	{
		delete clut;
		clut = NULL;
	}
	delete coinspawn;
}

void Terrain::Initialize()
{
	for (int x = 0; x < 2; x++)
	{
		for (int y = 0; y < tileY; y++)
		{
			CreateNewTile(x, y);
		}
	}
	for (int i = 0; i < clutterAmount; i++)//fill clutter pool
	{
		clutterPool.push_back(new ClutterObject(CLUTTER_BASE, this));
		clutterPool[i]->transform->SetPosition(0, Game::thisGame->SCREENY + 100);
		clutterPool[i]->transform->SetScale(8, 8);
		clutterPool[i]->Refresh();
	}

	initialized = true;
	
}

void Terrain::Scroll()
{
	int ttLenX = 2;
	int ttLenY = tileY;
	
	for (int x = 0; x < ttLenX; x++)
	{
		for (int y = 0; y < ttLenY; y++)
		{
			GroundTile *gt = terrainTiles[x][y];
			gt->WG_GameObject::velocity->x = 0;
			if (gt->WG_GameObject::velocity->x < curScrollSpeed)
			{
				gt->WG_GameObject::velocity->x -= curScrollSpeed;
				
			}
			if (gt->co != NULL)
			{
				gt->co->transform->SetPosition(gt->WG_GameObject::sprite->transform.x + gt->co->offset , gt->WG_GameObject::sprite->transform.y - gt->co->transform->transform.h);
			}
			
			if (gt->WG_GameObject::sprite->transform.x <= 0 - gt->WG_GameObject::sprite->transform.w)
			{
				if (gt->co != NULL)
				{
					gt->co->Refresh();
					gt->co = NULL;
				}

				Destroy((WG_GameObject*)gt);
				gt = nullptr;
				int i = y - 1;
				if (i < 0)
				{
					i = terrainTiles[x].size() - 1;
				}
				ReplaceTile(terrainTiles[x][i]->WG_GameObject::sprite->transform.x + (terrainTiles[x][i]->WG_GameObject::sprite->transform.w/2)+ terrainTiles[x][i]->WG_GameObject::velocity->x, terrainTiles[x][i]->WG_GameObject::sprite->transform.y, x, y);
			}
		}
	}
}

void Terrain::Update()
{
	if (initialized)
	{
		Scroll();
	}
	coinspawn->Update();
	curScrollSpeed = defaultScrollSpeed * Game::thisGame->scrollMultiplyer;
}

GroundTile *Terrain::GetRandomTerrainPiece(bool flip, int xIndex, int yIndex)
{
	int value = rand() % 100;
	if (initialized)
	{
		if (value < 20 && AreaCheck(yIndex))//20
		{
			if (flip)
			{
				return Instantiate(WORLD_TILE_SPIKEPITFLIP);
			}
			return Instantiate(WORLD_TILE_SPIKEPIT);
		}
	}
	if (flip)
	{
		return Instantiate(WORLD_TILE_GROUNDFLIP);
	}
	return Instantiate(WORLD_TILE_GROUND);

}
bool Terrain::AreaCheck(int y)
{
	bool check = false;
	if (y < 2 || y > terrainTiles[0].size() -3) return true;

	if (!(terrainTiles[0][y - 1]->name == "spikes" && terrainTiles[0][y - 2]->name == "spikes"))
	{
		if (!(terrainTiles[0][y + 1]->name == "spikes" && terrainTiles[0][y + 2]->name == "spikes"))
		{
			check = true;
		}
	}


	return check;

}


void Terrain::ReplaceTile(int x, int y, int indexX, int indexY)
{
	bool f = false;
	if (indexX == 0)f = true;

	GroundTile *tile = GetRandomTerrainPiece(f, indexX, indexY);

	if (!f && tile->name != "spikes" && useableClutter > 0)
	{
		//we can place clutter
		if (rand() % 100 < 60)
		{
			tile->co = GetTerrainClutter();
		}
	}

	
	if (indexX == 0)
	{
		tile->WG_GameObject::SetAnchor(TOP_LEFT);
		tile->WG_GameObject::SetScale(7, 7);
		tile->WG_GameObject::SetPosition(x, 0 - tile->WG_GameObject::sprite->transform.h / 2);
		tile->WG_GameObject::AddCollider(new WG_Collider(tile));
		tile->xIndex = x;
		tile->yIndex = y;
		terrainTiles[indexX][indexY] = tile;
	}
	else
	{
		tile->WG_GameObject::SetAnchor(BOTTOM_LEFT);
		tile->WG_GameObject::SetScale(7, 7);
		tile->WG_GameObject::SetPosition(x, 1080 - tile->WG_GameObject::sprite->transform.h / 2);
		tile->WG_GameObject::AddCollider(new WG_Collider(tile));
		tile->xIndex = x;
		tile->yIndex = y;
		terrainTiles[indexX][indexY] = tile;
	}

}

void Terrain::CreateNewTile(int x, int y)
{
	bool f = false;
	if (x == 0)f = true;
	GroundTile *tile = GetRandomTerrainPiece(f, x, y);

	if (x == 0)
	{
		tile->WG_GameObject::SetAnchor(TOP_LEFT);
		tile->WG_GameObject::SetScale(7, 7);
		tile->WG_GameObject::SetPosition(0 - tile->WG_GameObject::sprite->transform.w + (tile->WG_GameObject::sprite->transform.w*y), 0 - tile->WG_GameObject::sprite->transform.h / 2);
		tile->WG_GameObject::AddCollider(new WG_Collider(tile));
		tile->xIndex = x;
		tile->yIndex = y;
		terrainTiles[x][y] = tile;
	}
	else
	{
		tile->WG_GameObject::SetAnchor(BOTTOM_LEFT);
		tile->WG_GameObject::SetScale(7, 7);
		tile->WG_GameObject::SetPosition(0 - tile->WG_GameObject::sprite->transform.w + (tile->WG_GameObject::sprite->transform.w*y), 1080 - tile->WG_GameObject::sprite->transform.h / 2);
		tile->WG_GameObject::AddCollider(new WG_Collider(tile));
		tile->xIndex = x;
		tile->yIndex = y;
		terrainTiles[x][y] = tile;
		
	}
}


void ClutterObject::Refresh()
{
	int index = rand() % 10;
	offset = -50 + (rand() % 100);
	SetNewTexture((ClutterType)index);
	transform->SetPosition(0, Game::thisGame->SCREENY + 100);
	inUse = false;
	terrain->useableClutter++;
}

void ClutterObject::SetNewTexture(ClutterType ctype)
{
	switch (ctype)
	{
	case FLOWER_WHITE_SMALL:
		transform->SetTexture(&WG_Vector2(243,91), &WG_Vector2(10,5), Game::thisGame->renderer);
		break;
	case FLOWER_WHITE:
		transform->SetTexture(&WG_Vector2(227, 90), &WG_Vector2(10, 6), Game::thisGame->renderer);
		break;
	case FLOWER_RED_SMALL:
		transform->SetTexture(&WG_Vector2(227, 106), &WG_Vector2(10, 6), Game::thisGame->renderer);
		break;
	case FLOWER_RED:
		transform->SetTexture(&WG_Vector2(243, 107), &WG_Vector2(10, 5), Game::thisGame->renderer);
		break;
	case CHEST_CLOSED:
		transform->SetTexture(&WG_Vector2(225, 69), &WG_Vector2(14, 11), Game::thisGame->renderer);
		break;
	case SIGN_LIGHT:
		transform->SetTexture(&WG_Vector2(258, 2), &WG_Vector2(13, 14), Game::thisGame->renderer);
		break;
	case SIGN_DARK:
		transform->SetTexture(&WG_Vector2(242, 20), &WG_Vector2(13, 12), Game::thisGame->renderer);
		break;
	case GRASS_SMALL:
		transform->SetTexture(&WG_Vector2(178, 61), &WG_Vector2(11, 3), Game::thisGame->renderer);
		break;
	case ROCK_SMALL:
		transform->SetTexture(&WG_Vector2(259, 88), &WG_Vector2(11, 8), Game::thisGame->renderer);
		break;
	case ROCK:
		transform->SetTexture(&WG_Vector2(257, 103), &WG_Vector2(13, 9), Game::thisGame->renderer);
		break;
	default:
		break;
	}
}

ClutterObject *Terrain::GetTerrainClutter()
{
	for (auto& tc : clutterPool)
	{
		if (!tc->inUse)
		{
			tc->inUse = true;
			useableClutter--;
			return tc;
		}
	}
}
