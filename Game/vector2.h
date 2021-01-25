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

#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <stdexcept>
#include <sstream>
#include <string>

#include "math_util.h"

namespace math
{
	/**
	This class represents a 2 coordinate space mathematical vector.
	All operations expected for a vector, like sum, subtraction, product,
	cross product, dot product and normalization are provided.
	*/
	class Vector2
	{
	public:

		float x;
		float y;

		/** Builds a NULL vector */
		Vector2();

		/** Builds a vector based in it's x and y components */
		explicit Vector2(float aX, float anY);

		/** Builds a vector based in a two dimensional array */
		explicit Vector2(float xy[2]);

		/** Builds a vector based in it's size (magnitude) and angle */
		static Vector2 createBySizeAngle(float mag, float angle);

		/** Changes the x and y values */
		Vector2& set(float x, float y);

		/** Changes the x and y values */
		Vector2& set(const Vector2& other);

		/** Changes the x and y values */
		Vector2& set(const float xy[2]);

		/** Retrieves the size of this vector squared */
		float getSizeSqr() const;

		/** Retrieves this vector magnitude */
		float getSize() const;

		/** Changes this vector magnitude. This operation will not interfere
		* in the vector angulation.
		* Return this vector itself, after changing the magnitude. */
		Vector2& setSize(float _size);

		/** Returns the angle of the vector in relation to the x
		* axis, in a counter-clockwise rotation. That is, 90 degrees is
		* a vector pointing up and 0 degrees is a vector pointing right. */
		float getAngle() const;

		/** Rotates the vector counter-clockwise.
		* Returns the vector itself, after the rotation. */
		Vector2& rotate(float angle);

		/** Normalizes this vector.
		* Returns the vector itself, after the normalization. */
		Vector2& normalize();

		/** Adds this vector to another vector */
		Vector2& operator += (const Vector2& other);

		/** Subtracts this vector from another vector */
		Vector2& operator -= (const Vector2& other);

		/** Multiplies the magnitude of this vector to a constant */
		Vector2& operator *= (float c);

		/** Divides this vector magnitude by a constant*/
		Vector2& operator /= (float c);

		/** Negates this vector.
		* Same as rotating the vector in 180º but possibly much faster. */
		Vector2 operator -(void) const;
		Vector2 operator +(const Vector2& other) const;
		Vector2 operator -(const Vector2& other) const;

		Vector2 operator *(float c) const;
		Vector2 operator /(float c) const;

		float operator[] (long index) const;
		float& operator[] (long index);

		bool operator ==(const Vector2& other) const;

		float dot(const Vector2& other) const;
		float angleBetween(const Vector2 other) const;
		float angleSign(const Vector2& v) const;

		/**
		@return The string representation of this vector.
		*/
		std::string toString();

		static Vector2 bySizeAndAngle(float size, float angle);
	};

}

#endif

