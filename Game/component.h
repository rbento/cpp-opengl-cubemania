// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <sstream>
#include <string>
#include "logger.h"

using namespace std;

class Entity;

class Component
{
private: 

	Entity* mOwner;
	bool mEnabled;

public:

	Component(Entity& _owner, bool _enabled = true) : mOwner(&_owner), mEnabled(_enabled) 
	{
		Logger::outputs("Component", "A component was created.");
	}

	virtual ~Component()
	{
		Logger::outputs("Component", "A component was destroyed.");
	}

	Entity* owner() 
	{ 
		return mOwner; 
	}

	void enable() 
	{ 
		mEnabled = true; 
	}

	void disable() 
	{ 
		mEnabled = false; 
	}

	bool isEnabled() 
	{ 
		return mEnabled; 
	}

	string toString() 
	{
		stringstream result;
		return result.str();
	}
};

#endif