#pragma once
#include "SDL_mixer.h"


class AudioSystem
{
	int lastMuted = 0;
public:
	Mix_Music *musicTrack = NULL;
	bool muted = false;

	AudioSystem()
	{
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		Mix_Volume(-1, MIX_MAX_VOLUME / 10);
	};
	~AudioSystem()
	{
		Mix_FreeMusic(musicTrack);
		musicTrack = NULL;
	};

	void LoadMusicTrack(const char* path);
	void PlayMusic();
	void MusicPaused(bool f);
	void StopMusic();
	void ToggleMusic();
};