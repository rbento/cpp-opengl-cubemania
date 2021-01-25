// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include <string>
#include <vector>

#include "SDL_opengl.h"

#include "color.h"
#include "texture_manager.h"
#include "transform.h"

using namespace std;

class Primitive
{
public:

	GLuint id;
	GLfloat width;
	GLfloat height;
	GLfloat depth;
	Transform offset;

private:

	Primitive(const GLuint& _id = 0, const GLfloat width = 1.0f, const GLfloat height = 1.0f, const GLfloat depth = 0.0f, const Transform& _offset = Transform());

	static GLuint loadTexture(const string& _filename);
	static vector<GLuint> loadTextures(const vector<string>&);

	static void drawCubeFace(GLfloat _size, const Color& color = Color(), GLuint _texture = 0);

	static void drawCube(GLfloat _size, const Color& _color = Color(), GLuint _texture = 0);
	static void drawSkybox(GLfloat _size, GLuint* _textures);

public:

	~Primitive();

	static Primitive* createSphere(GLdouble _radius = 1.0, GLint _slices = 100, GLint _stacks = 100, const string& _filename = "");
	static Primitive* createCube(GLfloat _size = 1.0f, const Color& _color = Color(), const string& _filename = "");
	static Primitive* createPlane(GLfloat _width = 1.0f, GLfloat _height = 1.0f, const Color& _color = Color(), const string& _filename = "");
	static Primitive* createSkybox(GLfloat _size = 1.0f, const vector<string>& _filenames = vector<string>());
};

#endif