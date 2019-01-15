#include <sdl.h>
#include"WG_GameBackend.h"

SDL_Keycode WG_InputManager::Get()
{
	return EVENT;
}


SDL_Keycode WG_InputManager::Get(int ms)
{
	if (SDL_GetTicks() > lastPress+ms)
		lastPress = SDL_GetTicks();
		return EVENT;
}




void WG_InputManager::Update()
{
	SDL_Event kbevent;
	while (SDL_PollEvent(&kbevent))
	{
		if (kbevent.type == SDL_QUIT)
		{
			Game::thisGame->ExitGame();
		}
		else if (kbevent.type == SDL_KEYDOWN)
		{
			EVENT = kbevent.key.keysym.sym;
		}
		if (kbevent.type == SDL_KEYUP)
		{
			EVENT = NULL;
		}

	}
}

