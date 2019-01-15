#pragma once
#include "ScreenText.h"
#include "Sprite.h"
#include "Color.h"
#include <vector>

class Menu;
class BGFADER;

class UI
{
	SDL_Renderer *renderer;
	bool handShow = false;
public:
	Menu *currentMenu = NULL;
	ScreenText *scoreText;
	ScreenText *coinsText;
	ScreenText *fpsCounter;
	ScreenText *paused;
	std::vector<ScreenText*> prompts;
	BGFADER *fader;
	Sprite *hand;
	bool showScore = false;

	UI(SDL_Window *w, SDL_Renderer *r);
	void SetFPSCounter(const int fps);
	~UI();

	void SetScore(int val);
	void SetCoins(int val);
	void Render(SDL_Renderer *r);
	void ShowHand(bool f);
};

class MenuButton
{

public:
	Menu *menu;
	ScreenText *text;
	Color24 defaultColor = Color24(0,0,0);
	bool active = false;
	virtual void Invoke() = 0;
	virtual void OnHover();
	void SetDefaultColor(Color24 c)
	{
		defaultColor = Color24(c.r, c.g, c.b);
	};
	void Reset();
	void Render()
	{
		text->render();
	};
	~MenuButton() {
		delete text;
	};
};


class Menu
{
protected:
	Uint32 lastPress;
	SDL_Renderer *renderer;
	Sprite *bg;
	int selected = 0;

public:
	std::vector<MenuButton*> menuItems;
	Sprite *hand;
	bool closing = false;
	Menu(){};
	virtual ~Menu()
	{
		delete bg;
		delete hand;
		for (auto &mi : menuItems)
		{
			delete mi;
			mi = NULL;
		}
	};
	virtual void Update() =0;
	virtual void Render() = 0;
	virtual void Close() = 0;


};


class StartGame : public MenuButton
{
public:
	void Invoke() override;
	StartGame(ScreenText *st, Menu *m)
	{
		text = st;
		menu = m;
	};
};

class QuitGame : public MenuButton
{
public:
	void Invoke() override;
	QuitGame(ScreenText *st, Menu *m)
	{
		text = st;
		menu = m;
	};
};

class BGFADER
{
public:
	SDL_Rect *fader;
	Color24 *color;
	unsigned int alpha = 127;
	

	BGFADER();

	~BGFADER()
	{
		delete color;
		delete fader;
	};

	void SetColor(Uint8 r, Uint8 g, Uint8 b)
	{
		color->r = r;
		color->g = g;
		color->b = b;
	};
	void Render();
};