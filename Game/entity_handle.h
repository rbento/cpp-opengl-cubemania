// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __ENTITY_HANDLE_H__
#define __ENTITY_HANDLE_H__

#include "entity.h"

using namespace std;

class EntityHandle
{
private:

	int mId;
	int mHandle;

public:

	explicit EntityHandle(Entity& _entity) : mId(_entity.id()), mHandle(_entity.handle())
	{
	}

	Entity* toEntity() const
	{
		Entity* entity = Entity::findByHandle(mHandle);

		if (NULL != entity && entity->id() == mId)
		{
			return entity;
		}

		return NULL;
	}

	string toString()
	{
		stringstream result;
		result << "EntityHandle [ id:" << mId << ", handle:" << mHandle << " ]";
		return result.str();
	}
};

#endif