
#include "input_manager.h"

InputManager::InputManager() : mousex(0), mousey(0)
{
	Logger::msg("An InputManager was created.");
}

InputManager::~InputManager()
{
	Logger::msg("An InputManager was destroyed.");
}

InputManager* InputManager::instance()
{
	static InputManager instance;
	return &instance;
}

void InputManager::startup()
{
	//SDL_ShowCursor(SDL_DISABLE);

	//SDL_WM_GrabInput(SDL_GRAB_ON);

	SDL_EnableKeyRepeat(100,SDL_DEFAULT_REPEAT_INTERVAL);

	SDL_PumpEvents();

	keyState = SDL_GetKeyState(0);

	currentMouseState = SDL_GetMouseState(&mousex, &mousey);
	previousMouseState = currentMouseState;

	fill(currentKeyState, currentKeyState + SDLK_LAST, 0);
	fill(previousKeyState, previousKeyState + SDLK_LAST, 0);
}

void InputManager::shutdown()
{
}

void InputManager::update()
{
	previousMouseState = currentMouseState;
	copy(currentKeyState, currentKeyState + SDLK_LAST, previousKeyState);

	SDL_PumpEvents();

	currentMouseState = SDL_GetMouseState(&mousex, &mousey);
	copy(keyState, keyState + SDLK_LAST, currentKeyState);	
}

bool InputManager::onEvent(SDL_EventType _event)
{
	while (SDL_PollEvent(&events))
	{
		if (events.type == _event)
		{
			return true;
		}
	}
	return false;
}

void InputManager::pushEvent(SDL_EventType _eventType)
{
	SDL_Event _event;
	_event.type = _eventType;
	SDL_PushEvent(&_event);
}

bool InputManager::keyPressed(const SDLKey& _key) 
{
	return !previousKeyState[_key] && currentKeyState[_key];
}

bool InputManager::keyReleased(const SDLKey& _key) 
{
	return previousKeyState[_key] && !currentKeyState[_key]; 
}

bool InputManager::keyHeld(const SDLKey& _key) 
{
	return previousKeyState[_key] && currentKeyState[_key];
}

bool InputManager::mouseButtonPressed(int _button)
{
	return !(previousMouseState & SDL_BUTTON(_button)) && (currentMouseState & SDL_BUTTON(_button));
}

bool InputManager::mouseButtonReleased(int _button)
{
	return (previousMouseState & SDL_BUTTON(_button)) && !(currentMouseState & SDL_BUTTON(_button));
}

bool InputManager::mouseButtonHeld(int _button)
{
	return (previousMouseState & SDL_BUTTON(_button)) && (currentMouseState & SDL_BUTTON(_button));
}

bool InputManager::mouseLeftHeld()
{
	return mouseButtonHeld(SDL_BUTTON_LEFT);
}

bool InputManager::mouseLeftPressed()
{
	return mouseButtonPressed(SDL_BUTTON_LEFT);
}

bool InputManager::mouseLeftReleased()
{
	return mouseButtonReleased(SDL_BUTTON_LEFT);
}

bool InputManager::mouseMiddleHeld()
{
	return mouseButtonHeld(SDL_BUTTON_MIDDLE);
}

bool InputManager::mouseMiddlePressed()
{
	return mouseButtonPressed(SDL_BUTTON_MIDDLE);
}

bool InputManager::mouseMiddleReleased()
{
	return mouseButtonReleased(SDL_BUTTON_MIDDLE);
}

bool InputManager::mouseRightHeld()
{
	return mouseButtonHeld(SDL_BUTTON_RIGHT);
}

bool InputManager::mouseRightPressed()
{
	return mouseButtonPressed(SDL_BUTTON_RIGHT);
}

bool InputManager::mouseRightReleased()
{
	return mouseButtonReleased(SDL_BUTTON_RIGHT);
}

int InputManager::getMouseX()
{
	return mousex;
}

int InputManager::getMouseY()
{
	return mousey;
}