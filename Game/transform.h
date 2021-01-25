// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "vector3.h"

using namespace math;
using namespace std;

class Transform
{
public:

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

public:

	Transform(Vector3 _position = Vector3(0,0,0), 
		Vector3 _rotation = Vector3(0,0,0), 
		Vector3 _scale = Vector3(1.0, 1.0, 1.0));

	string toString();
};

#endif