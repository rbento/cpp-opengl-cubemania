
#include "music.h"

Music::Music(Mix_Music& _music) : mMusic(&_music)
{
	Logger::msg("A Music was created.");
}

Music::~Music()
{
	Logger::msg("A Music was destroyed.");
}

void Music::play()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(mMusic, -1);
	}
}

void Music::pause()
{
	Mix_PauseMusic();
}

void Music::resume()
{
	if (Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
	}
}

void Music::stop()
{
	Mix_HaltMusic();
}

void Music::fadeIn(int _duration)
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_FadeInMusic(mMusic, -1, _duration);
	}
}

void Music::fadeOut(int _duration)
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_FadeOutMusic(_duration);
	}
}