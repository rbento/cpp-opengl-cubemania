// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <windows.h>

#include <algorithm>
#include <string>
#include <sstream>
#include <set>
#include <vector>

#include "logger.h"
#include "math_util.h"
#include "transform.h"
#include "collision_component.h"
#include "mesh_component.h"

using namespace std;
using namespace math;

class Component;

class Entity
{
private:

	friend class EntityHandle;

	static vector<Entity*> mEntities;

	string mTag;
	int mId;

	Transform mTransform;

protected:

	set<Component*> mComponents;

private:

	int nextId();
	bool nextIdExists(const int _id) const;
	void add(Entity& _entity);

public:

	Entity(const string& _tag = "entity", int _id = -1);
	~Entity();

	static Entity* findByTag(const string& _tag);

	Transform* transform();

	void clear();
	static int count();
	int id() const;

	string tag() const;
	string toString();

	template <typename T> T* getComponent()
	{
		set<Component*>::iterator it;

		for (it = mComponents.begin(); it != mComponents.end(); ++it) 
		{
			T* component = dynamic_cast<T*>(*it);

			if (0 != component) 
			{
				return component;
			}
		}

		return 0;
	}

	template <typename T> void attachComponent() 
	{
		Component* component = getComponent<T>();

		set<Component*>::iterator result = mComponents.find(component);

		stringstream str;

		if (result == mComponents.end())
		{
			component = new T(*this);
			mComponents.insert(component);

			str << "A component " << typeid(T).name() << " was attached.";
			Logger::outputs("Entity",  str.str());

			return;
		}

		str << "A component of type " << typeid(T).name() << " was already attached.";
		Logger::outputs("Entity",  str.str());
	}

	template <typename T> void detachComponent()
	{
		Component* component = getComponent<T>();

		set<Component*>::iterator result = mComponents.find(component);

		stringstream str;

		if (result != mComponents.end())
		{
			str << "A component of type " << typeid(component).name() << " was detached.";
			Logger::outputs("Entity",  str.str());

			delete *result;
			mComponents.erase(result);

			return;
		}

		str << "Couldn't find and detach a component of type " << typeid(component).name() << ".";
		Logger::outputs("Entity",  str.str());
	}

	template <typename T> void enableComponent()
	{
		Component* component = getComponent<T>();

		if (0 != component)
		{
			component->enable();

			stringstream str;
			str << "A component " << typeid(component).name() << " was enabled.";
			Logger::outputs("Entity",  str.str());

			return;
		}
	}

	template <typename T> void disableComponent()
	{
		Component* component = getComponent<T>();

		if (0 != component)
		{
			stringstream str;
			str << "A component " << typeid(component).name() << " was disabled.";
			Logger::outputs("Entity",  str.str());

			component->disable();
		}
	}

	template <typename T> bool hasComponent() 
	{
		return 0 != getComponent<T>();
	}
};

#endif
