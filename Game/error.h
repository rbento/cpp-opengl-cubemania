// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __ERROR_H__
#define __ERROR_H__


#include <windows.h>
#include <stdio.h>

#include <sstream>
#include <string>

#include "SDL_opengl.h"

using namespace std;

class Error
{
public: 

	static void showf(const string& message, double value, bool quit = false)
	{
		stringstream out;
		out << value;
		handle(message, out.str(), quit);
	}

	static void showi(const string& message, long value, bool quit = false)
	{
		stringstream out;
		out << value;
		handle(message, out.str(), quit);
	}

	static void show(const string& message, bool quit = false)
	{
		handle(message, "", quit);
	}

	static void show(const string& message, const string& value = "", bool quit = false)
	{
		handle(message, value, quit);
	}

	static void glPopError(const string& marker)
	{
		GLenum glError = glGetError();
		if (glError != GL_NO_ERROR)
		{
			stringstream out;
			out << gluErrorString(glError);
			handle(marker, out.str(), false);			
		}
	}

private:

	static void handle(const string& message, const string& value = "", bool quit = false)
	{
		stringstream out;
		out << message;

		if (!value.empty())
		{
			out << ": " << value;
		}

		MessageBoxA(0, out.str().c_str(), "Error", MB_OK);

		if (quit)
		{
			exit(1);
		}
	}
};

#endif