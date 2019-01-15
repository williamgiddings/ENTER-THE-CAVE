#pragma once
#include "WG_GameObject.h"
#include "Animation.h"


//Defines
#define WORLD_TILE_GROUND new ENTITY_GROUND_TILE(new Sprite("./assets/sprites/sheet.png", new WG_Vector2(168, 0), new WG_Vector2(32, 32), renderer))
#define WORLD_TILE_GROUNDFLIP new ENTITY_GROUND_TILE(new Sprite("./assets/sprites/sheet.png", new WG_Vector2(168, 0), new WG_Vector2(32, 32), renderer), true)
#define WORLD_TILE_SPIKEPIT new ENTITY_SPIKEPIT_TILE(new Sprite("./assets/sprites/spikes.png", new WG_Vector2(32, 0), new WG_Vector2(32, 30), renderer))
#define WORLD_TILE_SPIKEPITFLIP new ENTITY_SPIKEPIT_TILE(new Sprite("./assets/sprites/spikes.png", new WG_Vector2(32, 0), new WG_Vector2(32, 30), renderer), true)

#define ENTITIES_COIN new ENTITY_COIN(new Sprite("./assets/sprites/coin.png", new WG_Vector2(0, 0), new WG_Vector2(32, 32), renderer))
#define ENTITIES_PLAYER new Player(new Sprite("./assets/sprites/characters.png", new WG_Vector2(9, 42), new WG_Vector2(15, 22), renderer))


#define ENTITIES_BACKGROUNDBASE new BackGround(new Sprite("./assets/sprites/sheet.png", new WG_Vector2(144, 64), new WG_Vector2(32, 48), renderer), renderer)
#define ENTITIES_BACKGROUNDTILE new Sprite("./assets/sprites/sheet.png", new WG_Vector2(144, 64), new WG_Vector2(32, 48), renderer)
#define ENTITIES_BACKGROUNDVINE new Sprite("./assets/sprites/sheet.png", new WG_Vector2(1, 1), new WG_Vector2(30, 30), renderer)
#define ENTITIES_BACKGROUNDCAVE new Sprite("./assets/sprites/back_cave.png", new WG_Vector2(0, 0), new WG_Vector2(100, 100), renderer)
#define ENTITIES_CAVE new Sprite("./assets/sprites/caveBG.png", new WG_Vector2(0, 0), new WG_Vector2(512, 282), renderer)
#define CLUTTER_BASE new Sprite("./assets/sprites/sheet.png", new WG_Vector2(243, 92), new WG_Vector2(16, 16), renderer)

#define UI_BG new Sprite("./assets/sprites/sheet.png", new WG_Vector2(176, 64), new WG_Vector2(48, 48), r)
#define UI_BG_SCROLL new Sprite("./assets/sprites/scroll.png", new WG_Vector2(0, 0), new WG_Vector2(47, 64), r)
#define UI_HAND new Sprite("./assets/sprites/hand_cursor.png", new WG_Vector2(0, 0), new WG_Vector2(32, 32), r)
#define UI_SKULL new Sprite("./assets/sprites/goldskull.png", new WG_Vector2(0, 0), new WG_Vector2(32, 32), r)


//ALL the objects...
class Terrain;
enum ClutterType
{
	FLOWER_WHITE_SMALL,
	FLOWER_WHITE,
	FLOWER_RED_SMALL,
	FLOWER_RED,
	CHEST_CLOSED,
	SIGN_LIGHT,
	SIGN_DARK,
	GRASS_SMALL,
	ROCK_SMALL,
	ROCK
};

class ClutterObject
{
	Terrain *terrain;
public:
	Sprite *transform;
	int offset = 0;
	bool inUse = false;
	void SetNewTexture(ClutterType ctype);
	void Refresh();
	ClutterObject(Sprite *s, Terrain *t) : transform(s), terrain(t) {};
	~ClutterObject() 
	{
		delete transform;
	};
};


class ENTITY_GROUND_TILE : public GroundTile
{
	SDL_RendererFlip flip;

public:
	void Update() override;
	ENTITY_GROUND_TILE(Sprite *s);
	ENTITY_GROUND_TILE(Sprite *s, bool f);
	void Render(SDL_Renderer *r) override;
};

class ENTITY_SPIKEPIT_TILE : public GroundTile
{
	SDL_RendererFlip flip;
	bool triggered=false;

public:
	void Update() override;
	ENTITY_SPIKEPIT_TILE(Sprite *s);
	ENTITY_SPIKEPIT_TILE(Sprite *s, bool f);
	void Render(SDL_Renderer *r) override;
	void Interact() override;
};

class ENTITY_COIN : public Entity
{

public:
	void Update() override;
	Animator *animator;
	ENTITY_COIN(Sprite *s);
	~ENTITY_COIN()
	{
		delete animator;
		animator = NULL;
	};
	void Render(SDL_Renderer *r) override;
	void SetAnimator(Animator *a);
};