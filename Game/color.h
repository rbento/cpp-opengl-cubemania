// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __COLOR_H__
#define __COLOR_H__

#include "SDL_opengl.h"

#include "math_util.h"

#include <sstream>
#include <string>

using namespace std;
using namespace math;

struct Color
{
public:

	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;

public:

	Color(GLfloat _r = 1.0f, GLfloat _g = 1.0f, GLfloat _b = 1.0f, GLfloat _a = 1.0f) : r(_r), g(_g), b(_b), a(_a)
	{
	}

	static Color getRandom()
	{
		GLfloat r = nextFloat(0.0f, 1.0f);
		GLfloat g = nextFloat(0.0f, 1.0f);
		GLfloat b = nextFloat(0.0f, 1.0f);
		GLfloat a = nextFloat(0.7f, 1.0f);

		return Color(r, g, b, a);
	}

	string toString()
	{
		stringstream result;
		result << "[ " << "r: " << r << ", g: " << g << ", b: " << b << ", a: " << a << " ]";
		return  result.str();
	}
};

#endif

