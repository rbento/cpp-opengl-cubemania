/******************************************************************************
*
* COPYRIGHT Vinícius G. Mendonça ALL RIGHTS RESERVED.
*
* This software cannot be copied, stored, distributed without  
* Vinícius G.Mendonça prior authorization.
*
* This file was made available on http://www.pontov.com.br and it is free 
* to be restributed or used under Creative Commons license 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
*******************************************************************************
* Este software nao pode ser copiado, armazenado, distribuido sem autorização 
* a priori de Vinícius G. Mendonça
*
* Este arquivo foi disponibilizado no site http://www.pontov.com.br e esta 
* livre para distribuição seguindo a licença Creative Commons 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
******************************************************************************/

#include "vector3.h"

using namespace math;

Vector3::Vector3() : x(0), y(0), z(0)
{}

Vector3::Vector3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{}

Vector3::Vector3(const Vector2& other, float _z)
	: x(other.x), y(other.y), z(_z)
{
}

Vector3::Vector3(const Vector2& other)
	: x(other.x), y(other.y), z(0)
{
}

Vector3::Vector3(float xyz[3])
	: x(xyz[0]), y(xyz[1]), z(xyz[2])
{
}

Vector3& Vector3::set(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
	return *this;
}

Vector3& Vector3::set(const float xyz[3])
{
	x = xyz[0];
	y = xyz[1];
	z = xyz[2];
	return *this;
}

Vector3& Vector3::set(const Vector2& v, float _z)
{
	x = v.x;
	y = v.y;
	z = _z;
	return *this;
}

Vector3& Vector3::addX(float _x)
{
	x += _x;
	return *this;
}

Vector3& Vector3::addY(float _y)
{
	y += _y;
	return *this;
}

Vector3& Vector3::addZ(float _z)
{
	z += _z;
	return *this;
}

Vector3& Vector3::add(float _x, float _y, float _z)
{
	x += _x;
	y += _y;
	z += _z;
	return *this;
}


float& Vector3::operator [](long index)
{
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default:
		{
			std::stringstream ss;
			ss << "Index out of bounds: " << index << " size: 3";
			throw std::out_of_range(ss.str());
		}
	}
}

float Vector3::operator [](long index) const
{
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default:
		{
			std::stringstream ss;
			ss << "Index out of bounds: " << index << " size: 3";
			throw std::out_of_range(ss.str());
		}
	}
}

Vector3& Vector3::operator +=(const Vector3& other)
{
	return add(other.x, other.y, other.z);
}

Vector3& Vector3::operator =(const Vector2& other)
{
	return set(other, 0.0f);
}

Vector3& Vector3::operator +=(const Vector2& other)
{
	return add(other.x, other.y, 0.0f);
}

Vector3& Vector3::operator -=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return (*this);
}

Vector3& Vector3::operator -=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return (*this);
}

Vector3& Vector3::operator *=(float c)
{
	x *= c;
	y *= c;
	z *= c;
	return *this;
}

Vector3& Vector3::operator /=(float c)
{
	x /= c;
	y /= c;
	z /= c;
	return *this;
}

Vector3 Vector3::operator -(void) const
{
	return (Vector3(-x, -y, -z));
}

Vector3 Vector3::operator +(const Vector3& other) const
{
	return (Vector3(x + other.x, y + other.y, z + other.z));
}

Vector3 Vector3::operator +(const Vector2& other) const
{
	return (Vector3(x + other.x, y + other.y, z));
}

Vector3 Vector3::operator -(const Vector3& other) const
{
	return (Vector3(x - other.x, y - other.y, z - other.z));
}

Vector3 Vector3::operator -(const Vector2& other) const
{
	return (Vector3(x - other.x, y - other.y, z));
}

Vector3 Vector3::operator *(float c) const
{
	return (Vector3(x * c, y * c, z * c));
}

Vector3 Vector3::operator /(float t) const
{
	float f = 1.0F / t;
	return (Vector3(x * f, y * f, z * f));
}

Vector3 Vector3::operator *(const Vector3& other) const
{
	return (Vector3(x * other.x,
		y * other.y,
		z * other.z));
}

bool Vector3::operator ==(const Vector3& other) const
{
	return ((x == other.x) &&
		(y == other.y) &&
		(z == other.z));
}

bool Vector3::operator !=(const Vector3& other) const
{
	return ((x != other.x) ||
		(y != other.y) ||
		(z != other.z));
}

float Vector3::dot(const Vector3& other) const
{
	return (x * other.x + y * other.y + z * other.z);
}

float Vector3::dot(const Vector2& other) const
{
	return (x * other.x + y * other.y);
}

Vector3 Vector3::cross(const Vector3& other) const
{
	return (Vector3(y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x));
}

float Vector3::getSizeSqr() const
{
	return x * x + y * y + z * z;
}

float Vector3::getSize() const
{
	return sqrtf(getSizeSqr());
}

Vector3& Vector3::setSize(float size)
{
	return (*this *= (size / getSize()));
}

Vector3& Vector3::applyCross(const Vector3& other)
{
	float nx, ny;

	nx = y * other.z - z * other.y;
	ny = z * other.x - x * other.z;
	z = x * other.y - y * other.x;
	x = nx;
	y = ny;

	return *this;
}

Vector3& Vector3::normalize(void)
{
	return (*this /= getSize());
}


Vector3& Vector3::rotateX(float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);

	float ny = c * y - s * z;
	float nz = c * z + s * y;

	y = ny;
	z = nz;

	return (*this);
}

Vector3& Vector3::rotateY(float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);

	float nx = c * x + s * z;
	float nz = c * z - s * x;

	x = nx;
	z = nz;

	return (*this);
}

Vector3& Vector3::rotateZ(float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);

	float nx = c * x - s * y;
	float ny = c * y + s * x;

	x = nx;
	y = ny;

	return (*this);
}

Vector3& Vector3::rotateAxis(float angle, const Vector3& axis)
{
	float s = sinf(angle);
	float c = cosf(angle);
	float k = 1.0F - c;

	float nx = x * (c + k * axis.x * axis.x) +
		y * (k * axis.x * axis.y - s * axis.z) +
		z * (k * axis.x * axis.z + s * axis.y);

	float ny = x * (k * axis.x * axis.y + s * axis.z) +
		y * (c + k * axis.y * axis.y) +
		z * (k * axis.y * axis.z - s * axis.x);

	float nz = x * (k * axis.x * axis.z - s * axis.y) +
		y * (k * axis.y * axis.z + s * axis.x) +
		z * (c + k * axis.z * axis.z);

	x = nx;
	y = ny;
	z = nz;

	return *this;
}

float* Vector3::toArray()
{
	pack[0] = x;
	pack[1] = y;
	pack[2] = z;

	return pack;
}

std::string Vector3::toString()
{
	std::stringstream result;
	result << "[ x:" << x << ", y:" << y << ", z:" << z << " ]";
	return  result.str();
}

Vector3 Vector3::bySizeAndAngle(float size, float angle)
{
	return Vector3(static_cast<float>(cos(angle) * size), static_cast<float>(sin(angle) * size), 0.0f);
}