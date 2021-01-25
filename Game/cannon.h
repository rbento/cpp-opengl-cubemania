// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __CANNON_H__
#define __CANNON_H__

#include "entity.h"
#include "primitive.h"
#include "time.h"

class Cannon : public Entity
{

public:

	Cannon();

	void update(const Time&);

	bool wasHit;
	float scale;
};

#endif
