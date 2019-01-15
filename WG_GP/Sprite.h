#pragma once
#include "SDL.h"
#include "WG_Vector.h"

struct WG_SurfaceTexture
{
	const char* texturePath;
	WG_Vector2 texturePosition;
	WG_Vector2 textureSize;

	WG_SurfaceTexture(const char* n, WG_Vector2 pos, WG_Vector2 size) : texturePath(n), texturePosition(pos), textureSize(size) {};
};


class Sprite
{
private:
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	SDL_Rect *source = NULL;
	WG_Vector2 *scale;
	

public:
	SDL_Rect transform;
	Sprite(const char* path, WG_Vector2 *position, WG_Vector2 *size, SDL_Renderer* r);
	void Render(SDL_Renderer *r);
	void Render(SDL_Renderer *r, SDL_RendererFlip f);
	void SetTexture(WG_Vector2 * position, WG_Vector2 * size, SDL_Renderer * r);
	void SetTexture(const char* path, WG_Vector2 *position, WG_Vector2 *size, SDL_Renderer* r);
	void SetScale(int x, int y)
	{
		scale->x = x;
		scale->y = y;
		transform.w *= scale->x;
		transform.h *= scale->y;

	}
	WG_Vector2 Scale() { return *scale; }

	void SetPosition(int x, int y)
	{
		transform.x = x;
		transform.y = y;
	}

	~Sprite();


};