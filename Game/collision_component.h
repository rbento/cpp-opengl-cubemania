// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __COLLISION_COMPONENT_H__
#define __COLLISION_COMPONENT_H__

#include "SDL_opengl.h"

#include "component.h"
#include "entity.h"
#include "logger.h"

#include "math_util.h"

using namespace math;
using namespace std;

struct AABB
{
	Vector3* center;  // center point
	GLfloat radius[3]; // halfwidths

	AABB() : center(0)
	{
		radius[0] = 0.0f;
		radius[1] = 0.0f;
		radius[2] = 0.0f;
	}
};

class CollisionComponent : public Component
{
private:

	AABB aabb;

private:

	bool testAABB(const AABB& a, const AABB& b);

public:

	CollisionComponent(Entity& _owner);
	~CollisionComponent();

	bool collidesWith(Entity& other);

	void width(GLfloat);
	GLfloat width();

	void height(GLfloat);
	GLfloat height();

	void depth(GLfloat);
	GLfloat depth();
};

#endif