#include "MainMenu.h"
#include "SDL.h"
#include "Objects.h"
#include "WG_GameBackend.h"
#include "Animation.h"
#include "Sprite.h"

MainMenu::MainMenu(SDL_Renderer *r, SDL_Window *w, UI *gameUI)
{
	lastPress = SDL_GetTicks() + 500; //stops 'auto seleceting through menus'
	renderer = r;
	bg = UI_BG;
	bg->SetScale(18, 18);
	bg->SetPosition((Game::thisGame->SCREENX / 2) - bg->transform.w / 2, (Game::thisGame->SCREENY / 2) - bg->transform.h / 2);
	chest = new Sprite("./assets/sprites/sheet.png", new WG_Vector2(226, 67), new WG_Vector2(14, 13), r);
	chest->SetScale(15, 15);
	chest->SetPosition((Game::thisGame->SCREENX / 2) - chest->transform.w / 2, (Game::thisGame->SCREENY / 2) - (chest->transform.h / 2)*1.5);

	hand = UI_HAND;
	hand->SetScale(3, 3);
	
	prompts.push_back(new ScreenText(w, "./assets/fonts/eboy.ttf"));
	prompts.push_back(new ScreenText(w, "./assets/fonts/eboy.ttf"));
	prompts.push_back(new ScreenText(w, "./assets/fonts/eboy.ttf"));
	prompts.push_back(new ScreenText(w, "./assets/fonts/eboy.ttf"));
	prompts.push_back(new ScreenText(w, "./assets/fonts/eboy.ttf"));
	prompts.push_back(new ScreenText(w, "./assets/fonts/eboy.ttf"));
	saveGameLocator = new ScreenText(w, "./assets/fonts/eboy.ttf");
	menuItems.push_back(new StartGame(new ScreenText(w, "./assets/fonts/eboy.ttf"), this));
	menuItems.push_back(new QuitGame(new ScreenText(w, "./assets/fonts/eboy.ttf"), this));
	menuItems[0]->SetDefaultColor(Color24(255, 255, 255));
	menuItems[1]->SetDefaultColor(Color24(255, 255, 255));

	menuItems[0]->text->setText("Enter the Cave", Game::thisGame->SCREENX / 2, (Game::thisGame->SCREENY / 4)*1.2, true, 40, 255, 255, 255);
	menuItems[1]->text->setText("Quit", Game::thisGame->SCREENX / 2, (Game::thisGame->SCREENY / 4) * 2.5, true, 40, 255, 255, 255);

	prompts[0]->setText("Press SPACE to Flip Gravity", 250, (Game::thisGame->SCREENY / 4)*0.1, true, 16, 255, 255, 255);
	prompts[1]->setText("Press R to Pickup Coins", 250, (Game::thisGame->SCREENY / 4)*0.2, true, 16, 255, 255, 255);
	prompts[2]->setText("Press LCTRL to Grapple Hook", 250, (Game::thisGame->SCREENY / 4)*0.3, true, 16, 255, 255, 255);
	prompts[3]->setText("Press M to Toggle Music", 250, (Game::thisGame->SCREENY / 4)*0.4, true, 16, 255, 255, 255);
	prompts[4]->setText("Press F10 to Toggle Fullscreen", 250, (Game::thisGame->SCREENY / 4)*0.5, true, 16, 255, 255, 255);
	prompts[4]->setText("Press ESC to Pause Game", 250, (Game::thisGame->SCREENY / 4)*0.6, true, 16, 255, 255, 255);
	saveGameLocator->setText("Save Game Found at: userData.dat", Game::thisGame->SCREENX - 300, (Game::thisGame->SCREENY - Game::thisGame->SCREENY / 10), true, 16, 0, 255, 0);

	if (Game::thisGame->scoreTracker->fileExists("./userData.dat"))
	{
		saveGameLocator->setText("Save Game Found at: userData.dat");
		saveGameLocator->setColor(0, 255, 0);
	}
	else {
		saveGameLocator->setText("Save Game Not Found");
		saveGameLocator->setColor(255,0,0);
	}

	gameUI->showScore = false;
	gameUI->currentMenu = this;
}


void MainMenu::Update()
{
	if (lastPress + 250 <= SDL_GetTicks())
	{
		SDL_Keycode key = Game::thisGame->input->Get();

		switch (key)
		{
		case SDLK_UP:
			selected = (selected - 1) % menuItems.size();
			lastPress = SDL_GetTicks();
			break;
		case SDLK_DOWN:
			selected = (selected + 1) % menuItems.size();
			lastPress = SDL_GetTicks();
			break;
		case SDLK_SPACE:
			menuItems[selected]->Invoke();
			break;
		}
		
	}
	if (!closing)
	{
		for (auto &i : menuItems)
		{
			if (i != menuItems[selected])
			{
				i->Reset();
			}
		}

		menuItems[selected]->OnHover();
	}
	else
	{
		return;
	}
}

void MainMenu::Render()
{
	if (!closing)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		
		bg->Render(renderer);
		chest->Render(renderer);
		for (auto &item : menuItems)
		{
			item->Render();
		}
		for (auto &item : prompts)
		{
			item->render();
		}
		saveGameLocator->render();

		hand->Render(renderer);

		SDL_RenderPresent(renderer);
	}

	
}



void MainMenu::Close()
{
	closing = true;
	Game::thisGame->inMenu = false;
	
}

void StartGame::Invoke()
{
	menu->Close();
	Game::thisGame->Reset();
	Game::thisGame->Start();
}

void QuitGame::Invoke()
{
	menu->Close();
	Game::thisGame->ExitGame();
}