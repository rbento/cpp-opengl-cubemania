// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <string>
#include "logger.h"
#include "primitive.h"
#include "transform.h"

using namespace std;

class Sprite
{

private:

	Primitive* mPrimitive;
	Transform mTransform;

	GLfloat mWidth;
	GLfloat mHeight;

	bool mVisible;

public:

	Sprite(const string& filename, GLfloat width, GLfloat height, GLfloat x = 0.0f, GLfloat y = 0.0f, bool visible = true);
	~Sprite();

	Primitive* primitive();
	Transform* transform();

	GLfloat width();
	GLfloat height();

	GLfloat top();
	GLfloat right();
	GLfloat bottom();
	GLfloat left();

	void show();
	void hide();

	bool isVisible();
};

#endif