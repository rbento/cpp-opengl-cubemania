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

#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <math.h>

#include "vector2.h"

namespace math
{
	class Vector2;

    class Vector3
	{

	public:
        float   x;
        float   y;
        float   z;

		float pack[3];

        /** Creates a new null vector 3D */
        explicit Vector3();

        /** Create a new vector 3D based on the given values.
        @param _x x coordinate
        @param _y y coordinate
        @param _z z coordinate
        */
        explicit Vector3(float _x, float _y, float _z);

        /**
          Creates a new Vector3 using the x and y coordinates
          from the given Vector2 and the given z coordinate.
          @param Vector2& A 2D vector
          @param z A z coordinate.
        */
        explicit Vector3(const Vector2& other, float _z);

        /**
            Creates a new Vector3 using the x and y coordinates
            from the given Vector2 and applying 0 in the Z coordinate
            @param Vector2& A 2D vector
        */
        explicit Vector3(const Vector2& other);

        /**
            Creates a new Vector3 from the given array. The coordinates
            will be mapped as following. Index 0 as x, index 1 as y and
            index 2 as z
            @param xyz An array containing the x, y, z coordinates
        */
        explicit Vector3(float xyz[3]);

        /**
            Adds to x coordinate
            @param _x The amount to add in x
            @return This vector.
        */
        Vector3& addX(float _x);

        /**
            Adds to y coordinate
            @param _y The amount to add in y
            @return This vector.
        */
        Vector3& addY(float _y);

        /**
            Adds to z coordinate
            @param _z The amount to add in z
            @return This vector.
        */
        Vector3& addZ(float _z);

        /**
            Adds to all vector coordinates

            @param _x The amount to add in x
            @param _y The amount to add in y
            @param _z The amount to add in z

            @return This vector.
        */
        Vector3& add(float _x, float _y, float _z);

        /**
            Sets the x, y and z coordinates in one single operation.

            @param _x The x coordinate
            @param _y The y coordinate
            @param _z The z coordinate
            @return This own vector is returned, for invocation chaning.
        */
        Vector3& set(float _x, float _y, float _z);

        /**
            Sets the x, y and z coordinates in one single operation. The
            coordinates will be mapped as following. Array index 0 as x,
            index 1 as y and index 2 as z

            @param xyz An array containing the x, y, z coordinates
            @return This own vector is returned, for invocation chaning.
        */
        Vector3& set(const float xyz[3]);

        /**
            Sets the x, y and z coordinates in one single operation.
            The x and y coordinates will be taken from the given Vector2.

            @param Vector2& A 2D vector
            @param z A z coordinate.
        */
        Vector3& set(const Vector2& v, float _z);

        /**
            Allows write access to the vector coordinates as if was
            an array containing the x in index 0, y in index 1
            and z in index 2. No bounds check are made, so be careful.
            @param index The coordinate index. As descrived above.
        */
        float& operator [](long index);

        /**
            Allows read access to the vector coordinates as if was
            an array containing the x in index 0, y in index 1
            and z in index 2. No bounds check are made, so be careful.
            @param k The coordinate index. As descrived above.
        */
        float operator [](long index) const;

        /** Assigns the value from the other Vector3 in this Vector3.*/
        Vector3& operator =(const Vector2& other);

        /** Assignment operator. z will be assigned to 0. */
        Vector3& operator +=(const Vector3& other);

        /** Adds the given Vector3 values to this vector */
        Vector3& operator +=(const Vector2& other);

        /** Subtracts this Vector3 from the given vector */
        Vector3& operator -=(const Vector3& other);

        /**
            Subtracts this Vector2 from the given vector.
            Z coordinate will be left unchanged.
        */
        Vector3& operator -=(const Vector2& other);

        /** Multiplies this vector by the given scalar constant. */
        Vector3& operator *=(float c);

        /** Divides this vector by the given vector */
        Vector3& operator /=(float c);

        /** Creates a new Vector that is the negation of this one. */
        Vector3 operator -(void) const;
        /** Creates a new vector with the sum of this and the given one.*/
        Vector3 operator +(const Vector3& other) const;
        /**
            Creates a new vector with the sum of this and the given one.
            The z coordinate will remain equal to this vector z coordinate.
        */
        Vector3 operator +(const Vector2& other) const;

        /** Creates a new vector with the subtraction of this and the given
            one.*/
        Vector3 operator -(const Vector3& other) const;

        /**
            Creates a new vector with the subtraction of this and the given one
            The z coordinate will remain equal to this vector z coordinate.
        */
        Vector3 operator -(const Vector2& other) const;

        /** Creates a new vector with the product of this vector and the given
            scalar constant.*/
        Vector3 operator *(float c) const;

        /** Creates a new vector with the division of this vector and the given
            scalar constant.*/
        Vector3 operator /(float c) const;

        /** Creates a new vector with the product of this vector and the given
            one.*/
        Vector3 operator *(const Vector3& other) const;

        /** Test if two vectors are equal */
        bool operator ==(const Vector3& other) const;

        /** Test if two vectors are different */
        bool operator !=(const Vector3& other) const;

        /** @return the size (magnitude) of this vector squared */
        float getSizeSqr() const;

        /** @return the size (magnitude) of this vector */
        float getSize() const;

        /** Sets the size (magnitude) of this vector */
        Vector3& setSize(float size);

        /** Creates a new vector with the cross product from this vector and
            the given one.
            @param other The vector that the cross product will be applyed.
            @return This own vector is returned, for invocation chaning.
        */
        Vector3 cross(const Vector3& other) const;

        /** Apply a cross product in this vector with the given vector.
            @param other The vector that will be used in the cross product.
            @return This own vector, modified by the cross product,
                    for invocation chaning.
        */
        Vector3& applyCross(const Vector3& other);

        /**
            Applies the dot product of this vector and the other one.
            @return The dot product.
        */
        float dot(const Vector3& other) const;
        /**
            Applies the dot product of this vector and the other one.
            The z coordinate will be ignored.

            @return The dot product.
        */
        float dot(const Vector2& other) const;

        /**
            Changes the size of this vector to one.
            Orientation is left unchanged.
        */
        Vector3& normalize(void);

        /**
            Rotates this vector around the x axis.
            @return This own vector is returned, for invocation chaning.
        */
        Vector3& rotateX(float angle);

        /**
            Rotates this vector around the y axis.
            @return This own vector is returned, for invocation chaning.
        */
        Vector3& rotateY(float angle);

        /**
            Rotates this vector around the z axis.
            @return This own vector is returned, for invocation chaning.
        */
        Vector3& rotateZ(float angle);

        /**
            Rotates this vector around the given axis.
            @return This own vector is returned, for invocation chaning.
        */
        Vector3& rotateAxis(float angle, const Vector3& axis);

        /**
            @return A float array containing the x, y and z elements
        */
		float* toArray();

        /**
            @return The string representation of this vector.
        */
		std::string toString();

		static Vector3 bySizeAndAngle(float size, float angle);
    };
}

#endif
