
#include "graphics_manager.h"

GraphicsManager::GraphicsManager()
{
	Logger::msg("A GraphicsManager was created.");
}

GraphicsManager::~GraphicsManager()
{
	Logger::msg("A GraphicsManager was destroyed.");
}

GraphicsManager* GraphicsManager::instance()
{
	static GraphicsManager instance;
	return &instance;
}

void GraphicsManager::startup()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Error::show("Unable to initialize SDL", SDL_GetError(), true);
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, kBitsPerPixel);

	if (0 == SDL_SetVideoMode(kWindowWidth, kWindowHeight, kBitsPerPixel, SDL_OPENGL))
	{
		Error::show("Unable to create the window", SDL_GetError(), true);
	}

	SDL_Surface* icon = IMG_Load("Resources/Icon/Game.ico");
	SDL_WM_SetIcon(icon, NULL);
	SDL_WM_SetCaption(kWindowCaption.c_str(), 0);

	Error::glPopError("GraphicsManager startup");

	setup();
}

void GraphicsManager::shutdown()
{
	SDL_Quit();
}

void GraphicsManager::setup()
{
	// options
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0f);                       

	// hints
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// features
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);

	glViewport(0, 0, kWindowWidth, kWindowHeight);

	Error::glPopError("GraphicsManager setup");
}

void GraphicsManager::beginScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
}

void GraphicsManager::endScene()
{
	SDL_GL_SwapBuffers();
}