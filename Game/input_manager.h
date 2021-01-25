// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include <algorithm>
#include <string>
#include "SDL.h"

#include "error.h"
#include "logger.h"
#include "manager.h"
#include "time.h"

using namespace std;

class InputManager : public Manager
{
private:

	SDL_Event events;

	Uint8* keyState;
	Uint8 previousKeyState[SDLK_LAST];
	Uint8 currentKeyState[SDLK_LAST];

	Uint8 previousMouseState;
	Uint8 currentMouseState;

	int mousex;
	int mousey;

private: 

	InputManager();

	bool mouseButtonPressed(int);
	bool mouseButtonReleased(int);
	bool mouseButtonHeld(int);

public:

	~InputManager();

	static InputManager* instance();

	void startup();
	void shutdown();

	bool onEvent(SDL_EventType);
	void pushEvent(SDL_EventType);

	bool keyPressed(const SDLKey&);
	bool keyReleased(const SDLKey&);
	bool keyHeld(const SDLKey&);

	bool mouseLeftHeld();
	bool mouseLeftPressed();
	bool mouseLeftReleased();

	bool mouseMiddleHeld();
	bool mouseMiddlePressed();
	bool mouseMiddleReleased();

	bool mouseRightHeld();
	bool mouseRightPressed();
	bool mouseRightReleased();

	int getMouseX();
	int getMouseY();

	void update();
};

#endif