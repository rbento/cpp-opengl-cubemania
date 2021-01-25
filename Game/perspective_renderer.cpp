
#include "perspective_renderer.h"
#include "mesh_component.h"

PerspectiveRenderer::PerspectiveRenderer()
{
	Logger::msg("A PerspectiveRenderer was created.");
}

PerspectiveRenderer::~PerspectiveRenderer()
{
	Logger::msg("A PerspectiveRenderer was destroyed.");
}

PerspectiveRenderer* PerspectiveRenderer::instance()
{
	static PerspectiveRenderer instance;
	return &instance;
}

void PerspectiveRenderer::attachComponent(MeshComponent& _component)
{
	mComponents.push_back(&_component);

	stringstream out;
	out << "A primitive was attached.";
	Logger::outputs("System", out.str());
}

void PerspectiveRenderer::detachComponent(MeshComponent& _component)
{
	stringstream out;
	out << "A primitive was detached.";
	Logger::outputs("System", out.str());

	vector<MeshComponent*>::iterator result = find(mComponents.begin(), mComponents.end(), &_component);

	if (result != mComponents.end())
	{
		mComponents.erase(result);
	}
}

void PerspectiveRenderer::render()
{
	int components = mComponents.size();

	for (int i = 0; i < components; ++i) 
	{
		MeshComponent* component = mComponents[i];

		Transform* transform = component->owner()->transform();

		glPushMatrix();

			glTranslatef(transform->position.x, transform->position.y, transform->position.z);

			glRotatef(transform->rotation.x, 1.0f, 0.0f, 0.0f);
			glRotatef(transform->rotation.y, 0.0f, 1.0f, 0.0f);
			glRotatef(transform->rotation.z, 0.0f, 0.0f, 1.0f);

			glScalef(transform->scale.x, transform->scale.y, transform->scale.z);

			int primitives = component->primitives()->size();

			for (int j = 0; j < primitives; ++j)
			{
				Primitive* primitive = (*component->primitives())[j];
				Transform* offset = &primitive->offset;

				glPushMatrix();

					glTranslatef(offset->position.x, offset->position.y, offset->position.z);

					glRotatef(offset->rotation.x, 1.0f, 0.0f, 0.0f);
					glRotatef(offset->rotation.y, 0.0f, 1.0f, 0.0f);
					glRotatef(offset->rotation.z, 0.0f, 0.0f, 1.0f);

					glScalef(offset->scale.x, offset->scale.y, offset->scale.z);

					glCallList(primitive->id);

				glPopMatrix();
			}

		glPopMatrix();
	}

	Error::glPopError("PerspectiveRenderer");
}




