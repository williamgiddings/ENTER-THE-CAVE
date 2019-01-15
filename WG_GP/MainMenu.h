#pragma once
#include "ScreenText.h"
#include <vector>
#include "Sprite.h"
#include "Objects.h"
#include "Sprite.h"
#include "UI.h";
#include <vector>


class MainMenu;

class MainMenu : public Menu
{
public:
	Sprite *chest;
	MainMenu(SDL_Renderer *r, SDL_Window *w, UI *gui);
	std::vector<ScreenText*> prompts;
	ScreenText *saveGameLocator;

	~MainMenu()
	{
		delete chest;
		delete saveGameLocator;
		for (auto &item : prompts)
		{
			delete item;
		}
	};

	void Update() override;
	void Render() override;
	void Close() override;


};






