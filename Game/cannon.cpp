
#include "cannon.h"

Cannon::Cannon() : wasHit(false), scale(1.0f), Entity("cannon")
{
	float size = 0.7f;

	Primitive* lfup = Primitive::createCube(size, Color(0.5f,0.5f,0.5f,1.0f), "Resources/Textures/txCannon.png");
	lfup->offset.position.x -= (size * 0.9f);
	lfup->offset.position.y += size;

	Primitive* rtup = Primitive::createCube(size, Color(0.5f,0.5f,0.5f,1.0f), "Resources/Textures/txCannon.png");
	rtup->offset.position.x += (size * 0.9f);
	rtup->offset.position.y += size;

	Primitive* lfdn = Primitive::createCube(size, Color(0.5f,0.5f,0.5f,1.0f), "Resources/Textures/txCannon.png");
	lfdn->offset.position.x -= size + (size / 2);

	Primitive* rtdn = Primitive::createCube(size, Color(0.5f,0.5f,0.5f,1.0f), "Resources/Textures/txCannon.png");
	rtdn->offset.position.x += size + (size / 2);

	attachComponent<MeshComponent>();
	getComponent<MeshComponent>()->primitives()->push_back(lfup);
	getComponent<MeshComponent>()->primitives()->push_back(rtup);
	getComponent<MeshComponent>()->primitives()->push_back(lfdn);
	getComponent<MeshComponent>()->primitives()->push_back(rtdn);

	attachComponent<CollisionComponent>();
	getComponent<CollisionComponent>()->width(size*2);
	getComponent<CollisionComponent>()->height(size*2);
	getComponent<CollisionComponent>()->depth(size);
}

void Cannon::update(const Time& _time)
{
	static Uint32 hitTimeout = 0;
	static bool hitAnimation = false;

	if (wasHit && hitTimeout == 0)
	{
		hitTimeout = _time.present + 1600;
		hitAnimation = true;
	}

	if (hitTimeout > 0 && _time.present > hitTimeout)
	{
		wasHit = false;
		hitTimeout = 0;
	}

	if (hitAnimation)
	{
		static int direction = -1;

		if (direction == -1)
		{
			scale -= 0.1f;

			if (scale <= 0.0f)
			{
				direction = 1;
				scale = 0.0f;
			}
		}
		else if (direction == 1)
		{
			scale += 0.1f;

			if (scale >= 1.0f)
			{
				direction = -1;
				scale = 1.0f;
				hitAnimation = false;
			}
		}

		transform()->scale.x = scale;
		transform()->scale.y = scale;
		transform()->scale.z = scale;
	}
}
