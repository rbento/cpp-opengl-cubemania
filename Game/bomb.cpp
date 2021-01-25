
#include "bomb.h"

Bomb::Bomb(Entity* _owner) : mOwner(_owner), isFalling(false), isDying(false), isDead(false), speed(0.0f), scale(1.0), Entity("bomb")
{
	float size = 0.36f;

	Primitive* cube = Primitive::createCube(size, Color(1.0f, 1.0f, 1.0f, 0.7f), "Resources/Textures/txBomb.png");

	attachComponent<MeshComponent>();
	getComponent<MeshComponent>()->primitives()->push_back(cube);

	attachComponent<CollisionComponent>();
	getComponent<CollisionComponent>()->width(size);
	getComponent<CollisionComponent>()->height(size);
	getComponent<CollisionComponent>()->depth(size);

	mRotation[0] = 0;
	mRotation[1] = 0;
	mRotation[2] = 0;

	int axis = nextInt(0, 2);
	mRotation[axis] = 1;

	axis = nextInt(0, 2);
	mRotation[axis] = 1;

	mRotationSpeed = nextFloat(10.0f, 80.0f);

	speed = nextFloat(2.0f, 10.0f);

	Logger::outputs("Bomb", "An bomb was created.");
}

Bomb::~Bomb()
{
	Logger::outputs("Bomb", "An bomb was destroyed.");
}

void Bomb::update(const Time& _time)
{
	if (!isFalling && _time.present > deliveryTimeout)
	{
		isFalling = true;

		transform()->position = mOwner->transform()->position;
	}

	if (!isFalling) return;

	if (mRotation[0] != 0)
	{
		float angle = transform()->rotation.x;
		angle += mRotationSpeed * _time.delta;
		rotatef(angle, 0.0f, 360.0f);
		transform()->rotation.x = angle;
	}

	if (mRotation[1] != 0)
	{
		float angle = transform()->rotation.y;
		angle += mRotationSpeed * _time.delta;
		rotatef(angle, 0.0f, 360.0f);
		transform()->rotation.y = angle;
	}

	if (mRotation[2] != 0)
	{
		float angle = transform()->rotation.z;
		angle += mRotationSpeed * _time.delta;
		rotatef(angle, 0.0f, 360.0f);
		transform()->rotation.z = angle;
	}

	if (isDying)
	{
		scale -= 0.1f;

		if (scale > 0.0f)
		{
			transform()->scale.x = scale;
			transform()->scale.y = scale;
			transform()->scale.z = scale;
		}
		else
		{
			isDead = true;
		}
	}

	if (!isDying && !isDead)
	{
		// Isso é física em marte
		transform()->position.y -= speed * _time.delta;

		if (transform()->position.y <= -30.0f)
		{
			isDying = true;
		}
	}
}

void Bomb::setDeliveryTimeout(Uint32 _timeout)
{
	deliveryTimeout = _timeout;
}