// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <string>
#include <vector>

#include <GL/freeglut.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"

#include "error.h"
#include "logger.h"
#include "manager.h"

using namespace std;

class TextureManager : public Manager
{
private: 

	vector<GLuint> mTextures;

private: 

	TextureManager();

public:

	~TextureManager();

	static TextureManager* instance();

	void startup();
	void shutdown();

	SDL_Surface* loadSurface(const string&);

	GLuint createFromSurface(SDL_Surface*);
	GLuint createFromFile(const string&);
};

#endif