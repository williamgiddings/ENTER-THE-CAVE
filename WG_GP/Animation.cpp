#include "Animation.h"
#include <iostream>
#include "SDL.h"
#include "WG_GameBackend.h"





void Animator::playAnimation(Animation *a)
{
	currentAnimation = a;
	isPlaying = true;
	
}

void Animator::Stop()
{
	if (Game::thisGame-> running)
		currentAnimation = nullptr;
}

void Animator::Update()
{
	if (currentAnimation != nullptr)
	{
		unsigned int ticks = SDL_GetTicks();
		frameIndex = (ticks / (int)currentAnimation->frames[frameIndex]->endDelay) % currentAnimation->frames.size();

		sprite->SetTexture(currentAnimation->frames[frameIndex]->position, currentAnimation->frames[frameIndex]->size, renderer);

		if (!loop && frameIndex == currentAnimation->frames.size()-1)
		{
			currentAnimation = NULL;
			isPlaying = false;
		}
	}
}


void Animator::Play(const char * n)
{
	for (auto& a : animations)
	{
		if (a->name == n)
		{
			playAnimation(a);
			frameIndex = 0;
			break;
		}
	}
	std::cout << "Unable to find animation '" << n << "'" << std::endl;

}
