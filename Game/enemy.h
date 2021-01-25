// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "entity.h"
#include "primitive.h"
#include "time.h"

class Enemy : public Entity
{
private:

	int mRotation[3];
	float mRotationSpeed;

public:

	GLuint spawnTimeout;
	bool isDying;
	bool isDead;
	bool isBomber;
	float speed;
	float scale;

public:

	Enemy();
	~Enemy();

	void update(const Time&);
};

#endif
