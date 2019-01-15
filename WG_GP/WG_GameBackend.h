#pragma once
#include <sdl.h>
#include "SDL_image.h"
#include <vector>
#include "Physics.h"
#include "WG_Vector.h"
#include <Windows.h>
#include "WG_Inputhandler.h"
#include "Terrain.h"
#include "UI.h"
#include "EndScreen.h"
#include "MainMenu.h"
#include "ScoreTracker.h"
#include "ScreenText.h"
#include "Audio.h"

static const float FRAME_DELAY = 1000 / 60;



class Game
{

public:
	//variables
	unsigned int SCREENX;
	unsigned int SCREENY;
	SDL_Window* window;
	SDL_Renderer* renderer;
	UI *gameUI;
	WG_GameObject *bg;
	bool running;
	std::vector<WG_GameObject*> gameObjects;
	WG_InputManager *input;
	static Game *thisGame;
	Player *player = NULL;
	AudioSystem *audio;
	WG_GameObject *world = NULL;
	Terrain *terrain = NULL;
	Physics *physics = NULL;
	ScoreTracker *scoreTracker;
	int frameRate = 0;
	int CollisionChunkSizeX;
	int CollisionChunkSizeY;
	float scrollMultiplyer = 1;
	int distanceTravelled = 0;
	int coinsCollected = 0;
	bool inMenu;
	bool showingEndScreen = false;
	int coinHS, scoreHS;
	bool paused = false;
	bool fullScreen = true;
	Uint32 lastPaused = 0;
	bool timerON = false;
	int timerStart = 0;
	float timePassed = 0;
	
	//Menus
	MainMenu *mainMenu = NULL;
	EndScreen *endScreen = NULL;

	//Functions
	void CleanUp();
	void Reset();
	void GoToMenu();
	void Start();
	void ExitGame();
	void Init();
	void showEndScreen(Uint8 type);
	void AddCoin(int a)
	{
		coinsCollected += a;
	};
	void Update();
	void CollisionTest();
	void Render();
	void InitPlayer();
	Game(const char *name, int x, int y)
	{
		thisGame = this;
		input = new WG_InputManager();
		physics = new Physics();
		scoreTracker = new ScoreTracker();
		audio = new AudioSystem();
		scoreHS = scoreTracker->GetHighScore();
		coinHS = scoreTracker->GetHighCoins();
		

		SCREENX = x;
		SCREENY = y;
		SDL_Init(SDL_INIT_VIDEO);
		IMG_Init(SDL_INIT_EVERYTHING);
		SDL_Init(SDL_INIT_AUDIO);
		TTF_Init();
		window = SDL_CreateWindow(name, (GetSystemMetrics(0) / 2) - (SCREENX / 2), (GetSystemMetrics(1) / 2) - (SCREENY / 2), SCREENX, SCREENY, SDL_WINDOW_RESIZABLE);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		SDL_RenderSetLogicalSize(renderer, SCREENX, SCREENY);
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
			

		gameUI = new UI(window, renderer);
		CollisionChunkSizeX = SCREENX / 5;
		CollisionChunkSizeY = SCREENY / 5;
		audio->LoadMusicTrack("./assets/sounds/music/mainloop.wav");
	}
	~Game()
	{
		delete audio;
		delete physics;
		delete scoreTracker;
		delete input;
	}

};