// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include <map>
#include <string>

#include "SDL.h"
#include "SDL_mixer.h"

#include "constants.h"
#include "error.h"
#include "logger.h"
#include "manager.h"
#include "music.h"
#include "sound_effect.h"

using namespace std;

class SoundManager : public Manager
{
private: 

	map<string, Mix_Music*> mMusics;
	map<string, Mix_Chunk*> mSoundEffects;

	SoundManager();

public:

	~SoundManager();

	static SoundManager* instance();

	void startup();
	void shutdown();

	Music* loadMusic(const string& filename);
	SoundEffect* loadSoundEffect(const string& filename);

	void setup();
};

#endif