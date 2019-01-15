#include "EndScreen.h"
#include "WG_GameBackend.h"
#include "ScoreTracker.h"

EndScreen::EndScreen(SDL_Renderer *r, SDL_Window *w, UI *gameUI, Uint8 typeOfEndGame)
{
	lastPress = SDL_GetTicks() + 500; //stops 'auto seleceting through menus'
	renderer = r;
	scoreText = gameUI->scoreText;
	coinsText = gameUI->coinsText;

	fader = new BGFADER();
	renderer = r;
	bg = UI_BG_SCROLL;
	bg->SetScale(16, 16);
	bg->SetPosition((Game::thisGame->SCREENX / 2) - bg->transform.w / 2, (Game::thisGame->SCREENY / 2) - bg->transform.h / 2);
	skull = UI_SKULL;
	skull->SetScale(7, 7);
	skull->SetPosition((Game::thisGame->SCREENX / 2) - skull->transform.w / 2, ((bg->transform.y + bg->transform.h) / 10) * 1);
	gameover = new ScreenText(w, "./assets/fonts/eboy.ttf");
	gameover->setText("GAME OVER", Game::thisGame->SCREENX / 2, skull->transform.y + (skull->transform.h) + 64, true, 55, 255, 0, 0);
	if (typeOfEndGame == TIME_EXPIRED)
	{
		gameover->setText("OUT OF TIME");
	}
	
	highScoreT = new ScreenText(w, "./assets/fonts/eboy.ttf");
	highScoreT->setText("HIGH SCORE", Game::thisGame->SCREENX / 2, skull->transform.y + (skull->transform.h) + 64 + gameover->height, true, 55, 214, 192, 2);

	hand = UI_HAND;
	hand->SetScale(3, 3);

	scoreText->setColor(0,0,0);
	coinsText->setColor(0, 0, 0);
	scoreText->move((Game::thisGame->SCREENX / 2) - scoreText->width /2,((bg->transform.y + bg->transform.h) / 10) * 5.5);
	coinsText->move((Game::thisGame->SCREENX / 2) - coinsText->width/2,((bg->transform.y + bg->transform.h) / 10) * 6);

	menuItems.push_back(new RetryButton(new ScreenText(w, "./assets/fonts/eboy.ttf"), this));
	menuItems.push_back(new ReturnToMenu(new ScreenText(w, "./assets/fonts/eboy.ttf"), this));
	menuItems[0]->SetDefaultColor(Color24(0, 0, 0));
	menuItems[0]->SetDefaultColor(Color24(0, 0, 0));

	menuItems[0]->text->setText("Try Again", Game::thisGame->SCREENX / 2, ((bg->transform.y + bg->transform.h) / 10) * 7.5, true, 32, 0, 0, 0);
	menuItems[1]->text->setText("Run Away", Game::thisGame->SCREENX / 2, ((bg->transform.y + bg->transform.h)/10)*8, true, 32, 0, 0, 0);
	
	gameUI->showScore = true;
	gameUI->currentMenu = this;
	

	IsHighScore();

}

void EndScreen::IsHighScore()
{
	if (Game::thisGame->scoreHS < Game::thisGame->distanceTravelled)
	{
		highScore = true;
	}
	if (Game::thisGame->coinHS < Game::thisGame->coinsCollected)
	{
		highCoins = true;
	}

	if (highCoins || highScore)
	{
		Game::thisGame->scoreTracker->SetHighScore(Game::thisGame->distanceTravelled, Game::thisGame->coinsCollected);
	}
}

void EndScreen::Update()
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

void EndScreen::Render()
{
	if (!closing)
	{
		fader->Render();
		bg->Render(renderer);
		skull->Render(renderer);
		gameover->render();
		if (highCoins || highScore)
		{
			highScoreT->render();
		}
		for (auto &item : menuItems)
		{
			item->Render();
		}
		hand->Render(renderer);
	}

}

void EndScreen::Close()
{
	Game::thisGame->showingEndScreen = false;
	closing = true;
}

void RetryButton::Invoke()
{
	Game::thisGame->gameUI->currentMenu->Close();
	Game::thisGame->Reset();
	Game::thisGame->Start();
}
void ReturnToMenu::Invoke()
{
	Game::thisGame->gameUI->currentMenu->Close();
	Game::thisGame->Reset();
	Game::thisGame->GoToMenu();
	
}

void RetryButton::OnHover()
{
	menu->hand->transform.x = this->text->x - menu->hand->transform.w;
	menu->hand->transform.y = this->text->y - this->text->height/2;
	active = true;
	text->setColor(245, 245, 245);
}
void ReturnToMenu::OnHover()
{
	menu->hand->transform.x = this->text->x - menu->hand->transform.w;
	menu->hand->transform.y = this->text->y - this->text->height / 2;
	active = true;
	text->setColor(245, 245, 245);
}