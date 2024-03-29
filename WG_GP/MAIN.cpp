#pragma once
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"
#undef main
#include <vector>
#include <random>
#include <windows.h>
#include "WG_GameBackend.h"
#include "Objects.h"
#include "Physics.h"
#include "BG.h"
#include "WG_Collider.h"
#include "WG_GameObject.h"
#include "Terrain.h"
#include "UI.h"
#include "MainMenu.h"
#include "EndScreen.h"
#include <vector>




void Game::CleanUp()
{
	std::vector<WG_GameObject*> removed;

	if (gameUI->currentMenu != NULL)
	{
		delete gameUI->currentMenu;
		gameUI->currentMenu = NULL;
	}
	delete terrain;
	for (auto &gameObject : gameObjects)
	{
		if (std::find(removed.begin(), removed.end(), gameObject) == removed.end())
		{
			removed.push_back(gameObject);
		}	
	}
	for (auto &gameObject : removed)
	{
		Destroy(gameObject);
	}
	
	terrain = NULL;

}


int main()
{
	Game *game = new Game("William Giddings, 15625956, CGP2011M, ENTER THE CAVE", 1920, 1080);
	game->GoToMenu();
	Mix_Quit(); 
	IMG_Quit(); 
	SDL_Quit();
	delete game;
}

void Game::GoToMenu()
{
	
	mainMenu = new MainMenu(renderer, window, gameUI);
	Uint32 frameStart;
	Uint32 frameTime;
	//Menu
	inMenu = true;
	while (running && inMenu)
	{
		frameStart = SDL_GetTicks();

		input->Update();
		mainMenu->Update();
		if (!inMenu || !running)return;
		mainMenu->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (FRAME_DELAY > frameTime)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}

	}
}

void Game::Start()
{
	Uint32 frameStart;
	Uint32 frameTime;
	float frameTimeF = 0;
	Init();
	timerStart = SDL_GetTicks();
	//Game
	while (running && !inMenu && !showingEndScreen)
	{
		frameStart = SDL_GetTicks();
		

		input->Update();
		if (running)
		{
			Update();
			CollisionTest();
			Render();
		}
		
		

		frameTime = SDL_GetTicks() - frameStart;
		

		if (FRAME_DELAY > frameTime)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}

		frameTimeF = SDL_GetTicks() - frameStart;
		frameRate = 1000/frameTimeF;

		if (timerON)
		{
			timePassed += frameTimeF / 1000;
			if ((int)timePassed % 1 == 0)
			{
				std::cout << "TIMER: " << timePassed << std::endl;
			}

			if (timePassed >= 60)
			{
				player->Die(TIME_EXPIRED);
			}
		}

	}
}


void Game::ExitGame()
{
	if (!gameUI->currentMenu->closing)
	{
		gameUI->currentMenu->Close();
	}
	inMenu = false;
	running = false;
	CleanUp();
}

void Game::Init()
{
	timerON = true; //TODO: TURN THIS OFF AFTER SUBMISSION!!
	timePassed = 0;
	bg = Instantiate(ENTITIES_BACKGROUNDBASE);
	terrain = new Terrain(renderer);
	InitPlayer();
	gameUI->showScore = true;
	scrollMultiplyer = 1;
	audio->PlayMusic();
}

void Game::Reset()
{
	distanceTravelled = 0;
	coinsCollected = 0;
	CleanUp();
}

void Game::showEndScreen(Uint8 type)
{
	endScreen = new EndScreen(renderer, window, gameUI, type);
	showingEndScreen = true;

	Uint32 frameStart;
	Uint32 frameTime;

	while (showingEndScreen)
	{
		frameStart = SDL_GetTicks();

		input->Update();
		Render();
		endScreen->Update();
		if (!showingEndScreen || !running)return;
		//Check in case we pressed quit during the update...
		endScreen->Render();



		frameTime = SDL_GetTicks() - frameStart;

		if (FRAME_DELAY > frameTime)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}

		

	}
}


void Game::InitPlayer()
{
	player = (Player*)Instantiate(ENTITIES_PLAYER);
	player->SetPosition(100, 540);
	player->SetScale(5, 5);
	player->AddCollider(new WG_Collider(player));
	player->useGravity = true;
}

void Game::Update()
{
	if (!paused)
	{
		terrain->Update();
		for (auto &gameObject : gameObjects)
		{
			if (running)
				gameObject->Update();
		}
		distanceTravelled += 1 * scrollMultiplyer;
		gameUI->SetScore(distanceTravelled);
		gameUI->SetCoins(coinsCollected);
		gameUI->SetFPSCounter(frameRate);

		
	}

	if (input->Get() == SDLK_m)
	{
		audio->ToggleMusic();
	}
	if (input->Get() == SDLK_ESCAPE && (lastPaused +500) < SDL_GetTicks())
	{
		paused = !paused;
		lastPaused = SDL_GetTicks();
	}
	if (input->Get() == SDLK_F10 && (lastPaused + 500) < SDL_GetTicks())
	{
		fullScreen = !fullScreen;
		lastPaused = SDL_GetTicks();
		if (fullScreen)
		{
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		}
		else
		{
			if (SDL_SetWindowFullscreen(window, SDL_WINDOW_RESIZABLE) == 0);
		}
	}

}

void Game::CollisionTest()
{
	if (running)
		player->TestCollisions();
}


void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	for (auto &gameObject : gameObjects)
	{
		gameObject->Render(renderer);
	}
	gameUI->Render(renderer);
	SDL_RenderPresent(renderer);
}