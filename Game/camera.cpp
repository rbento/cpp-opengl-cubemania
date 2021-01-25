
#include "camera.h"

Camera::Camera() : eye(Vector3(0.0, 0.0, 1.0)),
				   target(Vector3(0.0, 0.0, 0.0)),
				   up(Vector3(0.0, 1.0, 0.0)),
				   fovy(96.0f),
				   aspect((GLdouble)kWindowWidth/(GLdouble)kWindowHeight),
				   znear(0.1f),
				   zfar(100000.0f),
				   zoom(1.0f),
				   speed(2.0f),
				   Entity("camera")
{
	Logger::msg("A Camera was created.");
}

Camera::~Camera()
{
	Logger::msg("A Camera was destroyed.");
}

void Camera::updatePerspective()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fovy * zoom, aspect, znear, zfar);
}

void Camera::updateView()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye.x, eye.y, eye.z, target.x, target.y, target.z, up.x, up.y, up.z);

	glTranslatef(0, 0, zoom);
	glTranslatef(transform()->position.x, transform()->position.y, 0);

	glRotatef(transform()->rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(transform()->rotation.y, 0.0f, 1.0f, 0.0f);
}

void Camera::zoomOut()
{
	zoom -= 0.1f;
	zoom = zoom < 1.0f ? 1.0f : zoom;
}

void Camera::zoomIn()
{
	zoom += 0.1f;
	zoom = zoom > 25.0f ? 25.0f : zoom;
}

void Camera::turnLeft() 
{
	transform()->rotation.y -= speed;
}

void Camera::turnRight() 
{
	transform()->rotation.y += speed;
}

void Camera::strafeLeft() 
{
	Vector3 v = Vector3(target.x - eye.x, target.y - eye.y, target.z - eye.z);

	v.cross(up);
	v.normalize();

	eye.x += v.x * speed;
	eye.z += v.z * speed;

	target.x += v.x * speed;
	target.z += v.z * speed;

	transform()->position = target;
}

void Camera::strafeRight() 
{
	Vector3 v = Vector3(target.x - eye.x, target.y - eye.y, target.z - eye.z);

	v.cross(up);
	v.normalize();

	eye.x -= v.x * speed;
	eye.z -= v.z * speed;

	target.x -= v.x * speed;
	target.z -= v.z * speed;

	transform()->position = target;
}

void Camera::moveBackward() 
{
	Vector3 v = Vector3(target.x - eye.x, target.y - eye.y, target.z - eye.z);

	v.normalize();

	eye.z -= v.z * speed;
	target.z -= v.z * speed;

	transform()->position = target;
}

void Camera::moveForward() 
{
	Vector3 v = Vector3(target.x - eye.x, target.y - eye.y, target.z - eye.z);

	v.normalize();

	eye.z += v.z * speed;
	target.z += v.z * speed;

	transform()->position = target;
}

void Camera::rotate(float angle, float x, float y, float z)
{
	float nx = target.x - eye.x,
		  ny = target.y - eye.y,
		  nz = target.z - eye.z;

	float tx = nx,
		  ty = ny,
		  tz = nz;

	float cosang = (float)cos(angle);
	float sinang = (float)sin(angle);

	nx  = (cosang + (1 - cosang) * x * x)       * tx;
	nx += ((1 - cosang) * x * y - z * sinang)   * ty;
	nx += ((1 - cosang) * x * z + y * sinang)   * tz;

	ny  = ((1 - cosang) * x * y + z * sinang)   * tx;
	ny += (cosang + (1 - cosang) * y * y)       * ty;
	ny += ((1 - cosang) * y * z - x * sinang)   * tz;

	nz  = ((1 - cosang) * x * z - y * sinang)   * tx;
	nz += ((1 - cosang) * y * z + x * sinang)   * ty;
	nz += (cosang + (1 - cosang) * z * z)       * tz;

	target.x = eye.x + nx;
	target.y = eye.y + ny;
	target.z = eye.z + nz;
}

void Camera::mouseMove(float _x, float _y)
{
	int middlex = kWindowWidth  / 2,
		middley = kWindowHeight / 2;

	float angley = 0.0f,
		  anglez = 0.0f;

	static float currentRotX = 0.0f;

	if ( (_x == middlex) && (_y == middley) ) return;

	SDL_WarpMouse(middlex, middley);

	angley = (float)( (middlex - _x) ) / 1000.0f;
	anglez = (float)( (middley - _y) ) / 1000.0f;

	currentRotX += anglez;

	if(currentRotX > 1.0f)
		currentRotX = 1.0f;
	else if(currentRotX < -1.0f)
		currentRotX = -1.0f;
	else
	{
		Vector3 v = Vector3(target.x - eye.x, target.y - eye.y, target.y - eye.z);

		v.cross(up);
		v.normalize();

		rotate(anglez, v.x, v.y, v.z);
		rotate(angley, 0.0f, 1.0f, 0.0f);
	}
}

void Camera::centerAt(Vector3 _target)
{
	target = _target;

	Vector3 v = Vector3(target.x - eye.x, target.y - eye.y, target.z - eye.z);

	v.cross(up);
	v.normalize();

	eye.x -= v.x;
	eye.z -= v.z;

	target.x -= v.x;
	target.z -= v.z;

	transform()->position = target;
}

Vector2 Camera::worldToScreen(Vector3 v)
{
	GLdouble projection[16];
	GLdouble model[16];
	GLint viewport[4];

	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLdouble objX = v.x;
	GLdouble objY = v.y;
	GLdouble objZ = v.z;

	GLdouble winX, winY, winZ;

	gluProject(objX, objY, objZ, model, projection, viewport, &winX, &winY, &winZ);

	Error::glPopError("Camera worldToScreen");

	return Vector2(static_cast<float>(winX), static_cast<float>(winY));
}