// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#include "entity.h"
#include "primitive.h"
#include "math_util.h"

using namespace math;

class Skybox : public Entity
{
public:

	Skybox(GLfloat, const string&);
};

#endif