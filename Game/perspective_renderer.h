// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __PERSPECTIVE_RENDERER_H__
#define __PERSPECTIVE_RENDERER_H__

#include "SDL_opengl.h"

#include "constants.h"
#include "error.h"
#include "entity.h"
#include "primitive.h"
#include "transform.h"

class MeshComponent;

class PerspectiveRenderer 
{
private:

	vector<MeshComponent*> mComponents;

private:

	PerspectiveRenderer();

public:

	~PerspectiveRenderer();

	static PerspectiveRenderer* instance();

	void attachComponent(MeshComponent& _component);
	void detachComponent(MeshComponent& _component);

	void render();
};

#endif