
#include "sprite.h"
#include "ortho_renderer.h"

Sprite::Sprite(const string& _filename, GLfloat _width, GLfloat _height, GLfloat _x, GLfloat _y, bool _visible) : mWidth(_width), mHeight(_height), mTransform(Vector3(_x, _y, 0.0f)), mVisible(_visible)
{
	mPrimitive = Primitive::createPlane(_width, _height, Color(), _filename);

	Logger::outputs("Sprite", "A sprite was created.");

	OrthoRenderer::instance()->addSprite(*this);
}

Sprite::~Sprite()
{
	OrthoRenderer::instance()->removeSprite(*this);

	Logger::outputs("Sprite", "A sprite was destroyed.");

	delete mPrimitive;
}

Primitive* Sprite::primitive()
{
	return mPrimitive;
}

Transform* Sprite::transform()
{
	return &mTransform;
}

GLfloat Sprite::width()
{
	return mWidth;
}

GLfloat Sprite::height()
{
	return mHeight;
}

GLfloat Sprite::top()
{
	return mTransform.position.y - (mHeight/ 2);
}

GLfloat Sprite::right()
{
	return mTransform.position.x + (mWidth/ 2);
}

GLfloat Sprite::bottom()
{
	return mTransform.position.y + (mHeight/ 2);
}

GLfloat Sprite::left()
{
	return mTransform.position.x - (mWidth / 2);
}

void Sprite::show()
{
	mVisible = true;
}

void Sprite::hide()
{
	mVisible = false;
}

bool Sprite::isVisible()
{
	return mVisible;
}
