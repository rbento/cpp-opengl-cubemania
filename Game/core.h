// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __CORE_H__
#define __CORE_H__

#include <vector>

#include "SDL.h"

#include "core_component.h"
#include "text_manager.h"
#include "graphics_manager.h"
#include "input_manager.h"
#include "sound_manager.h"
#include "texture_manager.h"
#include "ortho_renderer.h"
#include "perspective_renderer.h"
#include "camera.h"
#include "time.h"

class Core : public CoreComponent
{
private:

	vector<CoreComponent*> mComponents;

	GraphicsManager* mGraphicsManager;
	InputManager* mInputManager;
	TextManager* mTextManager;
	TextureManager* mTextureManager;
	SoundManager* mSoundManager;

	OrthoRenderer* mOrthoRenderer;
	PerspectiveRenderer* mPerspectiveRenderer;

	Camera* mCamera;

	bool quit;

public:

	Core();
	~Core();

	void attachComponent(CoreComponent*);
	void detachComponent(CoreComponent*);

	void initialize();
	void cleanup();

	void startup();
	void shutdown();

	void loadContent();
	void unloadContent();

	void reset();

	void input();
	void update(const Time&);

	void run();		
};

#endif

