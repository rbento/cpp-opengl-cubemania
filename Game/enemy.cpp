
#include "enemy.h"

Enemy::Enemy() : spawnTimeout(0), isDying(false), isDead(false), isBomber(false), speed(0.0f), scale(1.0), Entity("enemy")
{
	float size = nextFloat(1.0f, 2.5f);

	Primitive* cube = Primitive::createCube(size, Color::getRandom(), "Resources/Textures/txEnemy.png");

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

	mRotationSpeed = nextFloat(10.0f, 50.0f);
	isBomber = nextInt(0, 1024) % 2 == 0;

	Logger::outputs("Enemy", "An Enemy was created.");
}

Enemy::~Enemy()
{
	Logger::outputs("Enemy", "An Enemy was destroyed.");
}

void Enemy::update(const Time& _time)
{
	if (_time.present < spawnTimeout)
	{
		return;
	}

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
		transform()->position.x += speed * _time.delta;

		if (transform()->position.x >= 40.0f)
		{
			isDying = true;
		}
	}
}


