// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __MUSIC_H__
#define __MUSIC_H__

#include "SDL_mixer.h"

#include "logger.h"

class Music
{
private:

	Mix_Music* mMusic;

public:

	Music(Mix_Music& music);
	~Music();

	void play();
	void pause();
	void resume();
	void stop();

	void fadeIn(int duration = 200);
	void fadeOut(int duration = 200);
};

#endif
