#pragma once
#include "SDL.h"

class WG_InputManager
{
private:
	SDL_Keycode EVENT;
	Uint32 lastPress = 500;
public:
	SDL_Keycode Get();
	SDL_Keycode Get(int ms);
	void Update();
};
