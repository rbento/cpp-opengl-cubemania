// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __ORTHO_RENDERER_H__
#define __ORTHO_RENDERER_H__

#include "SDL_opengl.h"

#include "constants.h"
#include "error.h"
#include "entity.h"
#include "primitive.h"
#include "transform.h"

class Sprite;

class OrthoRenderer 
{
private:

	vector<Sprite*> mSprites;

private:

	OrthoRenderer();

public:

	~OrthoRenderer();

	static OrthoRenderer* instance();

	void addSprite(Sprite& _component);
	void removeSprite(Sprite& _component);

	void render();
};

#endif