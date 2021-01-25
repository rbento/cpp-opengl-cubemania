// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <sstream>
#include <string>

#include "color.h"

struct Light
{
	Color ambient;
	Color diffuse;
	Color specular;
	Color emissive;

	Light(Color _ambient = Color(), Color _diffuse = Color(), Color _specular = Color(), Color _emissive = Color())
		: ambient(_ambient), diffuse(_diffuse), specular(_specular), emissive(_emissive)
	{
	}

	string toString()
	{
		stringstream result;
		result << "[ " << "ambient: " << ambient.toString() << ", diffuse: " << diffuse.toString() << ", specular: " << specular.toString() << ", emissive: " << emissive.toString() << " ]";
		return  result.str();
	}
};

#endif
