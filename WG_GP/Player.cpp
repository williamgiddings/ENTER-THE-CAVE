#include "WG_GameBackend.h"
#include "WG_Collider.h"
#include <iostream>

void Player::Render(SDL_Renderer *r)
{
	
	if (grapple != NULL)
	{
		grapple->Render(r);
	}
	
	if (gravtFlip)
	{
		SDL_RendererFlip f = SDL_FLIP_VERTICAL;
		sprite->Render(r, f);
	}
	else
	{
		sprite->Render(r);
	}
	

	if (collider != NULL)
	{
		collider->Render();
	}
}

Player::Player(Sprite *s)
{
	gravity = Game::thisGame->physics->GRAVITY_Y;
	sprite = s;
	alive = true;
	grapple = new GrappleLine(&sprite->transform);
	gravFlip();
	death = Mix_LoadWAV("./assets/sounds/effects/death.wav");

	SetAnimator(new Animator(s, Game::thisGame->renderer));
	animator->animations.push_back
	(
		new Animation("Run", "./assets/sprites/characters.png", std::vector<AnimationFrame*>
		{
			new AnimationFrame(new WG_Vector2(9, 42), new WG_Vector2(15, 22), 100),
			new AnimationFrame(new WG_Vector2(41, 42), new WG_Vector2(15, 22), 100),
			new AnimationFrame(new WG_Vector2(73, 42), new WG_Vector2(15, 22), 100),
			new AnimationFrame(new WG_Vector2(105, 42), new WG_Vector2(15, 22), 100)
		}
	));

	name = "player";
	animator->Play("Run");
	animator->loop = true;

}

void Player::SetAnimator(Animator * a)
{
	animator = a;
}

Player::~Player()
{
	delete animator;
	delete grapple;
	grapple = NULL;
	animator = NULL;
}

void Player::Update()
{
	if (Game::thisGame->running)
	{
		if (!animator->isPlaying)
		{
			animator->Play("Run");
			animator->loop = true;
		}

		if (useGravity && !isGrounded)
		{
			if (gravtFlip)
			{
				if (velocity->y <= gravity)
				{
					AddVelocity(WG_Vector2(0, -1));
				}
			}
			else
			{
				if (velocity->y >= gravity)
				{
					AddVelocity(WG_Vector2(0, 1));
				}
			}

		}
		animator->Update();
		getInput();
		CheckCollision();
		if (Game::thisGame->running)
		{
			sprite->transform.y += velocity->y;
			sprite->transform.x += velocity->x;

			if (sprite->transform.x < 32)
			{
				Die(LIFE_EXPIRED);
			}
		}

		
		if (grapple != NULL && Game::thisGame->running)
		{
			grapple->Update();
		}
	}
}

void Player::CheckCollision()
{
	isGrounded = false;
	canFlipGrav = false;
	Game::thisGame->gameUI->ShowHand(false);
	for (auto &cd : collider->collidingObjects) 
	{
		if (Game::thisGame->running)
		{
			if (cd->collider->trigger == false) //hard collisions
			{
				if (gravtFlip)
				{
					switch (cd->collisionVector->y)
					{
					case -1:
						if (abs(velocity->y) > 0 /*!isGrounded*/)
						{
							velocity->y = 0;
						}
						isGrounded = true;
						canFlipGrav = true;
						break;
					case 1:
						if (abs(velocity->y) > 0 /*!isGrounded*/)
						{
							velocity->y = 0;
						}
						velocity->y -= 2;
						break;
					}
				}
				else
				{
					switch (cd->collisionVector->y)
					{
					case 1:
						if (abs(velocity->y) > 0 /*!isGrounded*/)
						{
							velocity->y = 0;
						}
						isGrounded = true;
						canFlipGrav = true;
						break;
					case -1:
						if (abs(velocity->y) > 0 /*!isGrounded*/)
						{
							velocity->y = 0;
						}
						velocity->y += 2;
						break;
					}
				}
				switch (cd->collisionVector->x) //X
				{
				case -1:

					if (cd->collider->gameObject->velocity != nullptr)
					{
						int v = cd->collider->gameObject->velocity->x;

						velocity->x = v;
					}

					break;

				case 1:

					if (cd->collider->gameObject->velocity != nullptr)
					{
						int v = cd->collider->gameObject->velocity->x;

						velocity->x = v;
					}

					break;
				case 0:
					velocity->x = 0;
					break;
				}

				if (cd->collider->gameObject->name == "spikes")
				{
					cd->collider->gameObject->Interact();
					Die(LIFE_EXPIRED);
				}

			}
			else //trigger stuff
			{

				if (cd->collider->gameObject->name == "coin")
				{
					Game::thisGame->gameUI->ShowHand(true);
					if (Game::thisGame->input->Get() == SDLK_r)
					{
						Game::thisGame->terrain->coinspawn->Grab();
					}
				}

			}
		}
		
	} 
}

void Player::Die(Uint8 flag)
{
	Game::thisGame->audio->StopMusic();
	if (flag == LIFE_EXPIRED)
	{
		Mix_PlayChannel(-1, death, 0);
	}
	Game::thisGame->scrollMultiplyer = 0;
	animator->Stop();
	Game::thisGame->showEndScreen(flag);
}


void Player::AddVelocity(WG_Vector2 vel)
{
	if (!isGrounded)
	{
		velocity->y += vel.y;
	}
	if (vel.y > 0)
	{
		
	}
}

void Player::getInput()
{
	if (Game::thisGame->input->Get() == SDLK_SPACE && canFlipGrav)
	{
		gravFlip();
		canFlipGrav = false;
	}
	
	if (Game::thisGame->input->Get() == SDLK_LCTRL && (lastGrapple + 500) <= SDL_GetTicks())
	{
		grapple->Fire();
		lastGrapple = SDL_GetTicks();
	}
}

void Player::gravFlip()
{
	gravtFlip = !gravtFlip;
	gravity = -gravity;
	grapple->hookspeed = -grapple->hookspeed;
}



