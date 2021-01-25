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

#include <stdexcept>
#include <sstream>

#include "vector2.h"

using namespace math;

Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
{
}

Vector2::Vector2(float xy[2]) : x(xy[0]), y(xy[1])
{
}

Vector2 Vector2::createBySizeAngle(float size, float angle)
{
	return Vector2(cos(angle) * size,
		sin(angle) * size);
}

Vector2& Vector2::set(float _x, float _y)
{
	x = _x;
	y = _y;
	return *this;
}

Vector2& Vector2::set(const float xy[2])
{
	x = xy[0];
	y = xy[1];
	return *this;
}

Vector2& Vector2::set(const Vector2& other)
{
	if (&other == this)
		return *this;

	x = other.x;
	y = other.y;
	return *this;
}

float Vector2::getSizeSqr() const
{
	return x * x + y * y;
}

float Vector2::getSize() const
{
	return sqrtf(getSizeSqr());
}

Vector2& Vector2::setSize(float _size)
{
	return (*this *= (_size / getSize()));
}

float Vector2::getAngle() const
{
	return atan2f(y,x);
}

Vector2& Vector2::rotate(float angle)
{
	float s = sin(angle);
	float c = cos(angle);

	float newX = x * c - y * s;
	float newY = x * s + y * c;

	x = newX;
	y = newY;

	return *this;
}
Vector2& Vector2::normalize()
{
	return (*this /= getSize());
}

float Vector2::operator[] (long index) const
{
	if (index == 0)
		return x;
	if (index == 1)
		return y;

	std::stringstream ss;
	ss << "Index out of bounds: " << index << " size: 2";
	throw std::out_of_range(ss.str());
}

float& Vector2::operator[] (long index)
{
	if (index == 0)
		return x;
	if (index == 1)
		return y;

	std::stringstream ss;
	ss << "Index out of bounds: " << index << " size: 2";
	throw std::out_of_range(ss.str());
}

Vector2& Vector2::operator += (const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2& Vector2::operator -= (const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2& Vector2::operator *= (float c)
{
	x *= c;
	y *= c;
	return *this;
}

Vector2& Vector2::operator /= (float c)
{
	x /= c;
	y /= c;
	return *this;
}

Vector2 Vector2::operator -(void) const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator +(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator -(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator *(float c) const
{
	return Vector2(x*c, y*c);
}

Vector2 Vector2::operator /(float c) const
{
	return Vector2(x/c, y/c);
}

bool Vector2::operator ==(const Vector2& other) const
{
	return x == other.x && y == other.y;
}

float Vector2::dot(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

/**
* Return the smallest angle between 2 vectors.
* The signal is used to indicate the angle rotation direction.
* Positive for counter-clockwise and negative for clockwise direction
*
* This method uses difference between two vectors.
*/
float Vector2::angleBetween(const Vector2 other) const
{
	float angle = other.getAngle() - getAngle();

	if (fabs(angle) < PI)
		return angle;

	return static_cast<float>(angle + (angle < 0 ? 2*PI : -2*PI));
}

/**
* Return the smallest angle between 2 vectors.
* The signal is used to indicate the angle rotation direction.
* Positive for counter-clockwise and negative for clockwise direction
*
* This method uses the dot product.
*/
float Vector2::angleSign(const Vector2& v2)const
{
	/** Must guarantee that v2 is a normalized vector */
	Vector2 v(v2);
	v.normalize();
	float dp, angPi ;


	dp = dot( v ); //dot product
	if(dp >= 1.0) dp = 1.0f;
	if(dp <=-1.0) dp =-1.0f;

	angPi = (float)acos( dp );

	//side test
	if (y*v.x > x*v.y)
		return -angPi;
	else
		return angPi;
}

std::string Vector2::toString()
{
	std::stringstream ss;

	ss << "[ x: " << x << " | y: " << y << " ]\n";

	return  ss.str();
}

Vector2 Vector2::bySizeAndAngle(float size, float angle)
{
	return Vector2(cos(angle) * size, sin(angle) * size);
}
