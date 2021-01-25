// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __BOMB_H__
#define __BOMB_H__

#include "entity.h"
#include "enemy.h"
#include "math_util.h"
#include "primitive.h"
#include "time.h"

using namespace math;

class Bomb : public Entity
{
private:

	Entity* mOwner;

	int mRotation[3];
	float mRotationSpeed;

public:

	Bomb(Entity*);
	~Bomb();

	void update(const Time&);

	void setDeliveryTimeout(Uint32);

	bool isFalling;
	bool isDying;
	bool isDead;
	float speed;
	float scale;
	Uint32 deliveryTimeout;
};

#endif
