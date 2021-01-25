// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __TIME_H__
#define __TIME_H__

#include "sdl.h"
#include <sstream>
#include <string>

using namespace std;

struct Time
{
public:

	Uint32 past;
	Uint32 present;
	float delta;

public:

	Time(Uint32 _past = 0, Uint32 _present = 0, float _delta = 0.0) : past(_past), present(_present), delta(_delta)
	{
	}

	string toString() const
	{
		stringstream result;
		result << "[ " << "past: " << past << ", present: " << present << ", delta: " << delta << " ]";
		return  result.str();
	}
};

#endif
