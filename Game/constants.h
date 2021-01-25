// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include "SDL_mixer.h"
#include <string>

using namespace std;

const string kWindowCaption = "Cubemania 3D";

const int kWindowWidth = 800;
const int kWindowHeight = 600;
const int kBitsPerPixel = 32;

const int kAudioRate = 22050;
const Uint16 kAudioFormat = MIX_DEFAULT_FORMAT; 
const int kAudioChannels = 2;
const int kAudioBufferSize = 4096;

#endif;