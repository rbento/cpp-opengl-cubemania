
#include "sound_manager.h"

SoundManager::SoundManager()
{
	Logger::msg("A SoundManager was created.");
}

SoundManager::~SoundManager()
{
	Logger::msg("A SoundManager was destroyed.");
}

SoundManager* SoundManager::instance()
{
	static SoundManager instance;
	return &instance;
}

void SoundManager::startup()
{
	if (Mix_OpenAudio(kAudioRate, kAudioFormat, kAudioChannels, kAudioBufferSize) == -1)
	{
	   Error::show("Unable to start SDL_mixer up.", SDL_GetError(), true); 
	}
}

void SoundManager::shutdown()
{
	map<string, Mix_Music*>::iterator i;
	for (i = mMusics.begin(); i != mMusics.end(); ++i)
	{
		Logger::outputs("SoundManager", "Freeing music", (*i).first);
		Mix_FreeMusic((*i).second);
	}

	map<string, Mix_Chunk*>::iterator j;
	for (j = mSoundEffects.begin(); j != mSoundEffects.end(); ++j)
	{
		Logger::outputs("SoundManager", "Freeing sound effect", (*j).first);
		Mix_FreeChunk((*j).second);
	}

	Mix_CloseAudio();
}

void SoundManager::setup()
{
}

Music* SoundManager::loadMusic(const string& _filename)
{
	if (_filename.empty())
	{
		Error::show("Trying to load a music with an empty filename", SDL_GetError(), true); 
	}

	map<string, Mix_Music*>::iterator it = mMusics.find(_filename);

	if (it == mMusics.end())
	{
		Logger::outputs("SoundManager", "Loading music from file", _filename);

		Mix_Music* asset = Mix_LoadMUS(_filename.c_str());

		if (asset)
		{
			mMusics.insert(pair<string, Mix_Music*>(_filename, asset));
		}
		else
		{
			Error::show("Unable to load music from file", SDL_GetError(), true); 
		}	
	}
	else
	{
		Logger::outputs("SoundManager", "Loading music from buffer", _filename);
	}

	return new Music(*(mMusics.find(_filename)->second));
}

SoundEffect* SoundManager::loadSoundEffect(const string& _filename)
{
	if (_filename.empty())
	{
		Error::show("Trying to load a sound effect with an empty filename", SDL_GetError(), true); 
	}

	map<string, Mix_Chunk*>::iterator it = mSoundEffects.find(_filename);

	if (it == mSoundEffects.end())
	{
		Logger::outputs("SoundManager", "Loading sound effect from file", _filename);

		Mix_Chunk* asset = Mix_LoadWAV(_filename.c_str());

		if (asset)
		{
			mSoundEffects.insert(pair<string, Mix_Chunk*>(_filename, asset));
		}
		else
		{
			Error::show("Unable to load sound effect from file", SDL_GetError(), true); 
		}	
	}
	else
	{
		Logger::outputs("SoundManager", "Loading sound effect from buffer", _filename);
	}

	return new SoundEffect(*(mSoundEffects.find(_filename)->second));
}