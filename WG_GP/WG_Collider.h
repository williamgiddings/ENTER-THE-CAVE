#pragma once
#include "SDL.h"
#include <vector>
#include "WG_GameObject.h"
#include <algorithm>

class WG_Collider;

struct CollisionData
{
	WG_Collider *collider;
	WG_Vector2 *collisionVector;

	CollisionData(WG_Collider *c, WG_Vector2 *v) : collider(c), collisionVector(v) {};
};


class WG_Collider
{
private:
	bool drawCollider = false;
	bool debug = false;
public:
	enum ColliderType {
		STATIC,
		DYNAMIC
	};

	
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	SDL_Rect *boundingbox;
	WG_Vector2 *velocity = NULL;
	bool trigger;
	ColliderType colliderType;
	std::vector<CollisionData*> collidingObjects;
	std::vector <std::vector<CollisionData*>*> collisionTables;
	WG_GameObject *gameObject = NULL;
	bool alive;
	
	WG_Collider(SDL_Rect *r);
	WG_Collider(WG_GameObject *gm);
	WG_Collider(WG_GameObject *gm, WG_Vector2 &vel);
	WG_Collider(WG_GameObject *gm, WG_Vector2 &vel, bool t);
	WG_Collider(WG_GameObject *gm, WG_Vector2 &vel, bool t, ColliderType type);
	~WG_Collider()
	{
		if (collisionTables.size() > 0)
		{
			for (auto &cdt : collisionTables)
			{
				for (auto &element : *cdt)
				{
					if (element->collider == this)
					{
						cdt->erase(std::remove(cdt->begin(), cdt->end(), element), cdt->end());
					}
				}
			}
		}
		
	};
	void Render();
	void HookVelocity(WG_Vector2 *vhook);
	void DebugConsole(bool t)
	{
		debug = t;
	};
	void DrawCollider(bool t)
	{
		if (t)
		{
			drawCollider = true;
		}
		else
		{
			drawCollider = false;
		}
	};
	CollisionData *GetCollision(WG_GameObject * go);
	void TestCollisions();


};



