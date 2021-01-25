
#include "mesh_component.h"
#include "perspective_renderer.h"

MeshComponent::MeshComponent(Entity& _owner) : mPrimitives(vector<Primitive*>()), Component(_owner) 
{
	Logger::outputs("MeshComponent", "A mesh component was created.");

	PerspectiveRenderer::instance()->attachComponent(*this);
}

MeshComponent::~MeshComponent()
{
	PerspectiveRenderer::instance()->detachComponent(*this);

	vector<Primitive*>::iterator it;

	for (it = mPrimitives.begin(); it != mPrimitives.end(); ++it)
	{
		delete *it;
	}

	mPrimitives.clear();

	Logger::outputs("MeshComponent", "A mesh component was destroyed.");
}

vector<Primitive*>* MeshComponent::primitives()
{
	return &mPrimitives;
}