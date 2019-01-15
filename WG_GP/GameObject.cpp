#include "WG_GameObject.h"
#include "WG_Collider.h"


void WG_GameObject::TestCollisions()
{
	if (collider != NULL)
	{
		collider->TestCollisions();
	}
};



WG_GameObject::~WG_GameObject()
{
	delete sprite;
	if (collider != NULL)
	{
		delete collider;
	}
	delete velocity;
	sprite = nullptr;
	velocity = nullptr;
	collider = nullptr;
}