// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __TEXT_MANAGER_H__
#define __TEXT_MANAGER_H__

#include <iostream>
#include <string>
#include <vector>

#include "SDL_opengl.h"

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "constants.h"
#include "color.h"
#include "error.h"
#include "logger.h"
#include "manager.h"

using namespace std;

struct Text
{
	string str;
	Color color;
	float x;
	float y;

	Text(const string& _str, const Color& _color = Color(), float _x = 0.0f, float _y = 0.0f) : str(_str), color(_color), x(_x), y(_y) {}
};

class TextManager : public Manager
{
private: 

	vector<Text*> mTexts;

private:

	TextManager();

public:

	~TextManager();

	static TextManager* instance();

	void startup();
	void shutdown();

	void update();

	void placeAt(const string& text, const Color& _color, float x, float y);
};

#endif;