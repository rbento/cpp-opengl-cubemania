// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __MESH_COMPONENT_H__
#define __MESH_COMPONENT_H__

#include <vector>

#include "component.h"
#include "entity.h"
#include "logger.h"
#include "primitive.h"

using namespace std;

class Entity;

class MeshComponent : public Component
{
private:

	vector<Primitive*> mPrimitives;

public:

	MeshComponent(Entity& _owner);
	~MeshComponent();

	vector<Primitive*>* primitives();
};

#endif