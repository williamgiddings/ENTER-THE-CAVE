#pragma once
#include "sdl_image.h"
#include "WG_Vector.h"
#include "SDL.h"
#include "Sprite.h"


Sprite::Sprite(const char* path, WG_Vector2 *position, WG_Vector2 *size, SDL_Renderer* r)
{
	scale = new WG_Vector2(1, 1);
	source = new SDL_Rect();
	source->x = position->x;
	source->y = position->y;
	source->w = size->x;
	source->h = size->y;

	
	transform.x = position->x;
	transform.y = position->y;
	transform.w = size->x;
	transform.h = size->y;
	
	surface = IMG_Load(path);
	texture = SDL_CreateTextureFromSurface(r, surface);
	SDL_FreeSurface(surface);

	delete position;
	delete size;

}


Sprite::~Sprite() 
{
	delete source;
	delete scale;
	SDL_DestroyTexture(texture);
};


void Sprite::Render(SDL_Renderer * r)
{
	SDL_RenderCopy(r, texture, this->source, &this->transform);
}

void Sprite::Render(SDL_Renderer * r, SDL_RendererFlip f)
{
	SDL_RenderCopyEx(r, texture, this->source, &this->transform, 0, NULL ,f);
}

void Sprite::SetTexture(WG_Vector2 * position, WG_Vector2 * size, SDL_Renderer * r)
{
	source->x = position->x;
	source->y = position->y;
	source->w = size->x;
	source->h = size->y; 
	transform.w = size->x * scale->x;
	transform.h = size->y * scale->y;
}

void Sprite::SetTexture(const char *path, WG_Vector2 * position, WG_Vector2 * size, SDL_Renderer * r)
{
	source = new SDL_Rect();
	source->x = position->x;
	source->y = position->y;
	source->w = size->x;
	source->h = size->y;


	surface = IMG_Load(path);
	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(r, surface);
	SDL_FreeSurface(surface);

}