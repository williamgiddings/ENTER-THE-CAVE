#pragma once
#include <vector>
#include "WG_GameObject.h"
#include "CoinSpawner.h"
#include "Objects.h"

class CoinSpawner;
class ClutterObject;

class Terrain
{
	unsigned int defaultScrollSpeed = 10;
	int tileY = 12;
	SDL_Renderer *renderer;
	bool initialized = false;
	friend void Destroy(GroundTile *o);
	std::vector<ClutterObject*> clutterPool;
	
public:
	unsigned int curScrollSpeed;
	int useableClutter = 0;
	int clutterAmount = 20;
	std::vector<std::vector<GroundTile*>> terrainTiles;
	Terrain(SDL_Renderer *r);
	~Terrain();
	CoinSpawner *coinspawn;
	void Initialize();
	void Scroll();
	void Update();
	GroundTile *GetRandomTerrainPiece(bool flip, int x, int y);
	void CreateNewTile(int x, int y);
	void ReplaceTile(int x, int y, int xi, int yi);
	ClutterObject *GetTerrainClutter();
	bool AreaCheck(int y);
};

