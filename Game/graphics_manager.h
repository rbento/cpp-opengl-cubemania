// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __GRAPHICS_MANAGER_H__
#define __GRAPHICS_MANAGER_H__

#include <string>
#include <GL/freeglut.h>

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"

#include "constants.h"
#include "error.h"
#include "logger.h"
#include "manager.h"

using namespace std;

class GraphicsManager : public Manager
{
private: 

	GraphicsManager();

public:

	~GraphicsManager();

	static GraphicsManager* instance();

	void startup();
	void shutdown();

	void setup();

	void beginScene();
	void endScene();
};

#endif