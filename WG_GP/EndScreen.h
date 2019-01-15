#pragma once
#include "Sprite.h"
#include "ScreenText.h"
#include "UI.h"
#include <vector>

class EndScreen : Menu
{
public:
	ScreenText *scoreText;
	ScreenText *coinsText;
	ScreenText *gameover;
	ScreenText *highScoreT;
	BGFADER *fader;
	Sprite *skull;
	bool highScore = false;
	bool highCoins = false;

	EndScreen(SDL_Renderer *r, SDL_Window *w, UI *gameUI, Uint8 typeOfEndGame);
	~EndScreen()
	{
		delete gameover;
		delete highScoreT;
		delete fader;
		delete skull;
		
	};
	void Update() override;
	void Render() override;
	void Close() override;
	void IsHighScore();

};

class RetryButton : public MenuButton
{
public:
	void Invoke() override;
	void OnHover() override;
	RetryButton(ScreenText *st, Menu *m)
	{
		text = st;
		menu = m;
	};
};

class ReturnToMenu : public MenuButton
{
public:
	void Invoke() override;
	void OnHover() override;
	ReturnToMenu(ScreenText *st, Menu *m)
	{
		text = st;
		menu = m;
	};
};