
#include "shot.h"

Shot::Shot() : Entity("shot")
{
	float size = 0.3f;

	Primitive* cube = Primitive::createCube(size, Color(1.0f, 1.0f, 1.0f, 0.8f), "Resources/Textures/txShot.png");

	attachComponent<MeshComponent>();
	getComponent<MeshComponent>()->primitives()->push_back(cube);

	attachComponent<CollisionComponent>();
	getComponent<CollisionComponent>()->width(size);
	getComponent<CollisionComponent>()->height(size);
	getComponent<CollisionComponent>()->depth(size);
}

