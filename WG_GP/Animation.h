#pragma once
#include <vector>
#include "Sprite.h"


struct AnimationFrame;


class Animation
{
public:
	const char* name;
	const char* path;
	std::vector<AnimationFrame*> frames;
	Animation(const char* n, const char* p, std::vector<AnimationFrame*> fs) : name(n), path(p), frames(fs) {};
};


struct AnimationFrame
{
	WG_Vector2 *position;
	WG_Vector2 *size;
	float endDelay;

	AnimationFrame(WG_Vector2 *pos, WG_Vector2 *s, float end) : position(pos), size(s), endDelay(end)  {};
	~AnimationFrame()
	{
		delete position;
		delete size;
	}
};

class Animator
{
	void playAnimation(Animation *a);
	Sprite *sprite;
	SDL_Renderer *renderer;
	float frameTime;
	unsigned int frameIndex = 0;
public:
	std::vector<Animation*> animations;
	Animation *currentAnimation;
	bool isPlaying = false;
	bool loop = false;
	void Play(const char* n);
	void Stop();
	void Update();
	Animator(Sprite *s, SDL_Renderer *r) : sprite(s), renderer(r) {};
};
