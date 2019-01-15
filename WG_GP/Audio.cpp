#include "SDL_mixer.h"
#include "Audio.h"
#include "SDL.h"

void AudioSystem::MusicPaused(bool f)
{
	if (f)
	{
		if (Mix_PausedMusic() == 0)
		{
			Mix_PauseMusic();
			Mix_Volume(-1, 0);
			muted = true;
		}
	}
	else 
	{ 
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
			Mix_Volume(-1, MIX_MAX_VOLUME / 10);
			muted = false;
		}
	}
}

void AudioSystem::ToggleMusic()
{
	if ((lastMuted + 500) < SDL_GetTicks())
	{
		if (!muted)
		{
			MusicPaused(true);
		}
		else
		{
			MusicPaused(false);
		}
		lastMuted = SDL_GetTicks();
	}
}


void AudioSystem::StopMusic()
{
	Mix_HaltMusic();
}

void AudioSystem::LoadMusicTrack(const char* path)
{
	musicTrack = Mix_LoadMUS(path);
}

void AudioSystem::PlayMusic()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(musicTrack, -1);
		Mix_VolumeMusic(MIX_MAX_VOLUME / 20);
	}
}