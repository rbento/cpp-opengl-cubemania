
#include "sound_effect.h"

SoundEffect::SoundEffect(Mix_Chunk& _chunk) : chunk(&_chunk)
{
	Logger::msg("A SoundEffect was created.");
}

SoundEffect::~SoundEffect()
{
	Logger::msg("A SoundEffect was destroyed.");
}

void SoundEffect::play()
{
	Mix_PlayChannel(-1, chunk, 0);
}

