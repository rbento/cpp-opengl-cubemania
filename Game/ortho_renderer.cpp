
#include "ortho_renderer.h"
#include "sprite.h"

OrthoRenderer::OrthoRenderer()
{
	Logger::msg("An OrthoRenderer was created.");
}

OrthoRenderer::~OrthoRenderer()
{
	Logger::msg("An OrthoRenderer was destroyed.");
}

OrthoRenderer* OrthoRenderer::instance()
{
	static OrthoRenderer instance;
	return &instance;
}

void OrthoRenderer::addSprite(Sprite& _sprite)
{
	mSprites.push_back(&_sprite);

	Logger::outputs("OrthoRenderer", "A sprite was added.");
}

void OrthoRenderer::removeSprite(Sprite& _sprite)
{
	Logger::outputs("OrthoRenderer", "A sprite was removed.");

	vector<Sprite*>::iterator result = find(mSprites.begin(), mSprites.end(), &_sprite);

	if (result != mSprites.end())
	{
		mSprites.erase(result);
	}
}

void OrthoRenderer::render()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, kWindowWidth, 0, kWindowHeight, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	int count = mSprites.size();

	for (int i = 0; i < count; ++i) 
	{
		Sprite* sprite = mSprites[i];

		if (!sprite->isVisible())
		{
			continue;
		}

		Transform* transform = sprite->transform();
		Primitive* primitive = sprite->primitive();

		glPushMatrix();

			glTranslatef(transform->position.x, transform->position.y, transform->position.z);

			glRotatef(transform->rotation.x, 1.0f, 0.0f, 0.0f);
			glRotatef(transform->rotation.y, 0.0f, 1.0f, 0.0f);
			glRotatef(transform->rotation.z, 0.0f, 0.0f, 1.0f);

			glScalef(transform->scale.x, transform->scale.y, transform->scale.z);

			glCallList(primitive->id);

		glPopMatrix();
	}

	glPopMatrix();

	Error::glPopError("OrthoRenderer");
}
