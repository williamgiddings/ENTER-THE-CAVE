#pragma once
#include <string>
#include "Color.h"
#include "Sprite.h"
#include "Animation.h"
#include "WG_Vector.h"
#include "GrappleHook.h"
#include "SDL_mixer.h"

#define TIME_EXPIRED 1
#define LIFE_EXPIRED 0


class WG_Collider;
class ClutterObject;


enum Anchor
{
	BOTTOM_LEFT,
	TOP_LEFT,
	CENTER,
	TOP_RIGHT,
	BOTTOM_RIGHT
};
class WG_GameObject 
{


protected:
	

	friend WG_GameObject *Instantiate(WG_GameObject *object);
	friend void Destroy(WG_GameObject *object);
	WG_Vector2 scale = WG_Vector2(1, 1);
	Anchor anchorLocation = TOP_LEFT;


public:
	int ID;
	std::string name;
	SDL_Rect transform;
	Sprite *sprite = NULL;
	WG_Collider *collider = NULL;
	bool alive;
	bool useGravity = false;
	WG_Vector2 *velocity = new WG_Vector2(0, 0);
	virtual void Render(SDL_Renderer *r) = 0;
	virtual void Update() = 0;
	virtual void Interact() {};
	virtual void TestCollisions();

	void AddCollider(WG_Collider *newCollider)
	{
		collider = newCollider;
	};

	WG_Vector2 Scale() { return scale; }
	void SetAnchor(Anchor anchor)
	{
		anchorLocation = anchor;
	};
	void SetPosition(int x, int y)
	{
		SDL_Rect *target;

		if (sprite != NULL)
		{
			target = &sprite->transform;
		}
		else
		{
			target = &transform;
		}

		WG_Vector2 diff = WG_Vector2(0, 0);
		switch (anchorLocation)
		{
		case BOTTOM_LEFT:
			diff = WG_Vector2(0, 0 - target->h);
			break;
		case BOTTOM_RIGHT:
			diff = WG_Vector2(0 - target->w, 0 - target->h);
			break;
		case TOP_LEFT: //default
			diff = WG_Vector2(0, 0);
			break;
		case TOP_RIGHT:
			diff = WG_Vector2(target->w, 0);
			break;
		case CENTER:
			diff = WG_Vector2(target->w / 2, target->h / 2);
			break;
		}
		target->x = x + diff.x;
		target->y = y + diff.y;
	};
	void SetScale(int x, int y)
	{
		scale = { x,y };
		if (sprite != NULL)
		{
			sprite->SetScale(x, y);
		}
		else
		{
			transform.w *= scale.x;
			transform.h *= scale.y;
		}

	};
	WG_GameObject()
	{

	};
	WG_GameObject(const WG_GameObject &other) {};
	int GetInstanceID()
	{
		return ID;
	};
	virtual ~WG_GameObject();

};

class Entity : public WG_GameObject
{
public:

	virtual void Render(SDL_Renderer *r) override;
	virtual void Update()override
	{
	};
	Entity() {}
	Entity(Sprite *s)
	{
		sprite = s;
	};
	
	virtual ~Entity() {
	
	};
};



class GroundTile : public Entity
{
	friend GroundTile *Instantiate(GroundTile *object);
	friend void Destroy(GroundTile *o);
public:
	int xIndex;
	int yIndex;
	ClutterObject *co = NULL;
	
	virtual void Render(SDL_Renderer *r) override
	{
		Entity::Render(r);
	};
	
	virtual void Update()override
	{
	};
	GroundTile() {};
	GroundTile(Sprite *s) { WG_GameObject::sprite = s; };
	~GroundTile() {};

};

class Player : public Entity
{
	float gravity;
	bool canFlipGrav;
	Animator* animator;
	Uint32 lastGrapple = 0;

	Mix_Chunk *death = NULL;

public:
	int speed = 1;
	bool isGrounded= false;
	bool gravtFlip;
	GrappleLine *grapple;

	Player(Sprite *s);
	void SetAnimator(Animator *a);
	void getInput();
	void Render(SDL_Renderer *r);
	void Update()override;
	void CheckCollision();
	void Die(Uint8 flag);
	void AddVelocity(WG_Vector2 vel);
	void gravFlip();
	~Player();
};