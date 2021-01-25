// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __SOUND_EFFECT_H__
#define __SOUND_EFFECT_H__

#include "SDL_mixer.h"

#include "logger.h"

class SoundEffect
{
private:

	Mix_Chunk* chunk;

public:

	SoundEffect(Mix_Chunk& chunk);
	~SoundEffect();

	void play();
};

#endif