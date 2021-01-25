// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __CORE_COMPONENT_H__
#define __CORE_COMPONENT_H__

#include "time.h"

class CoreComponent
{
public:

	CoreComponent() {}
	virtual ~CoreComponent() {}

	virtual void reset() = 0;

	virtual void initialize() = 0;
	virtual void cleanup() = 0;

	virtual void loadContent() = 0;
	virtual void unloadContent() = 0;

	virtual void input() = 0;
	virtual void update(const Time&) = 0;
};

#endif