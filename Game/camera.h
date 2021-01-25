// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "SDL.h"
#include "SDL_opengl.h"

#include "constants.h"
#include "entity.h"

using namespace std;

class Camera : public Entity
{
public:

	Vector3 eye;
	Vector3 target;
	Vector3 up;

	GLdouble fovy;
	GLdouble aspect;
	GLdouble znear;
	GLdouble zfar;

	float zoom;
	float speed;

public:

	Camera();
	~Camera();

	void updatePerspective();
	void updateView();

	void zoomIn();
	void zoomOut();

	void strafeLeft();
	void strafeRight();

	void moveForward();
	void moveBackward();

	void turnLeft();
	void turnRight();

	void centerAt(Vector3 position);

	void rotate(float angle, float x, float y, float z);
	void mouseMove(float x, float y);

	Vector2 worldToScreen(Vector3);
};

#endif