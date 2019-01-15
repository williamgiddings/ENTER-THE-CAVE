#pragma once
#include "UI.h"
#include "ScreenText.h"
#include "SDL.h"
#include "WG_GameBackend.h"
#include <string>
#include "SDL_ttf.h"
#include "Sprite.h"


UI::UI(SDL_Window *w, SDL_Renderer *r)
{
	renderer = r;
	scoreText = new ScreenText(w,"./assets/fonts/eboy.ttf");
	coinsText = new ScreenText(w, "./assets/fonts/eboy.ttf");
	fpsCounter = new ScreenText(w, "./assets/fonts/eboy.ttf");
	paused = new ScreenText(w, "./assets/fonts/eboy.ttf");
	paused->setText("PAUSED", Game::thisGame->SCREENX/2, Game::thisGame->SCREENY/2, true, 72, 255, 255, 255);
	fader = new BGFADER();

	hand = new Sprite("./assets/sprites/hand_cursor.png", new WG_Vector2(0, 0), new WG_Vector2(32, 32), r);
	hand->SetScale(2, 2);


	prompts.push_back(new ScreenText(w, "./assets/fonts/eboy.ttf"));
	prompts.push_back(new ScreenText(w, "./assets/fonts/eboy.ttf"));
	prompts.push_back(new ScreenText(w, "./assets/fonts/eboy.ttf"));
	prompts.push_back(new ScreenText(w, "./assets/fonts/eboy.ttf"));
	prompts.push_back(new ScreenText(w, "./assets/fonts/eboy.ttf"));
	prompts[0]->setText("Press SPACE to Flip Gravity", Game::thisGame->SCREENX / 2, (Game::thisGame->SCREENY / 4)*3.4, true, 16, 255, 255, 255);
	prompts[1]->setText("Press R to Pickup Coins", Game::thisGame->SCREENX / 2, (Game::thisGame->SCREENY / 4)*3.5, true, 16, 255, 255, 255);
	prompts[2]->setText("Press LCTRL to Grapple Hook", Game::thisGame->SCREENX / 2, (Game::thisGame->SCREENY / 4)*3.6, true, 16, 255, 255, 255);
	prompts[3]->setText("Press M to Toggle Music", Game::thisGame->SCREENX / 2, (Game::thisGame->SCREENY / 4)*3.7, true, 16, 255, 255, 255);
	prompts[4]->setText("Press F10 to Toggle Fullscreen", Game::thisGame->SCREENX / 2, (Game::thisGame->SCREENY / 4)*3.8, true, 16, 255, 255, 255);

}

void UI::SetFPSCounter(const int fps)
{
	std::string value = "FPS: " + std::to_string(fps);
	fpsCounter->setText(value, fpsCounter->width, Game::thisGame->SCREENY-32, true, 28, 0, 255, 0);
}

UI::~UI()
{
	delete scoreText;
	delete coinsText;
	delete fpsCounter;
	delete paused;
	delete hand;
	delete fader;
	for (auto &p : prompts)
	{
		delete p;
	}
}

void UI::SetScore(int val)
{
	std::string value = "SCORE: " + std::to_string(val);
	scoreText->setText(value, Game::thisGame->SCREENX / 2, 32, true, 28, 255, 255, 255);
}

void UI::SetCoins(int val)
{
	std::string value = "COINS: " + std::to_string(val);
	coinsText->setText(value, (Game::thisGame->SCREENX / 4) * 3.5, 32, true, 28, 255, 255, 255);
	hand->transform.x = coinsText->x - hand->transform.w;
	hand->transform.y = coinsText->y - coinsText->height/2;
}

void UI::Render(SDL_Renderer *r)
{
	if (currentMenu != NULL)
	{
		currentMenu->Render();
	}
	if (showScore)
	{
		scoreText->render();
		coinsText->render();
	}
	if (handShow)
	{
		hand->Render(renderer);
	}
	if (Game::thisGame->paused)
	{
		fader->Render();
		paused->render();
		for (auto &p : prompts)
		{
			p->render();
		}
	}


	fpsCounter->render();
	
}

void UI::ShowHand(bool f)
{
	handShow = f;
}

BGFADER::BGFADER()
{
	color = new Color24(0, 0, 0);
	fader = new SDL_Rect();
	fader->w = Game::thisGame->SCREENX;
	fader->h = Game::thisGame->SCREENY;
	fader->x = 0;
	fader->y = 0;
}

void BGFADER::Render()
{
	SDL_SetRenderDrawColor(Game::thisGame->renderer, color->r, color->g, color->b, alpha);
	SDL_SetRenderDrawBlendMode(Game::thisGame->renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(Game::thisGame->renderer, fader);
}



void MenuButton::Reset()
{
	active = false;
	text->setColor(defaultColor.r, defaultColor.g, defaultColor.b);
}

void MenuButton::OnHover()
{
	menu->hand->transform.x = this->text->x - menu->hand->transform.w;
	menu->hand->transform.y = this->text->y - this->text->height / 2;
	active = true;
	text->setColor(255, 0, 0);

}

