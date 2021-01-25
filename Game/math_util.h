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

#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

#include <algorithm>
#include <cmath>
#include <ctime>

namespace math
{
	static const float PIF = 3.1415926f;
	static const double PI = 3.14159265358979323846;
	static const double PI_OVER_2 = PI/2;
	static const double ONE_DEGREE = 180.0 / PI;
	static const double E = 2.7182818284590452354;

	inline double toDegrees(double angrad)
	{
		return angrad * ONE_DEGREE;
	}

	inline float toDegrees(float angrad)
	{
		return static_cast<float>(angrad * ONE_DEGREE);
	}

	inline float toDegrees(int angrad)
	{
		return toDegrees(static_cast<float>(angrad));
	}

	inline double toRadians(double angdeg)
	{
		return angdeg / ONE_DEGREE;
	}

	inline float toRadians(float angdeg)
	{
		return static_cast<float>(angdeg / ONE_DEGREE);
	}

	inline float toRadians(int angdeg)
	{
		return toRadians(static_cast<float>(angdeg));
	}

	inline void rotatef(float &value, float min, float max)
	{
		value = (value > max) ? min : (value < min) ? max : value;
	}

	inline void rotatei(int &value, int min, int max)
	{
		value = (value > max) ? min : (value < min) ? max : value;
	}

	inline void clampf(float &value, float min, float max)
	{
		value = (value > max) ? max : (value < min) ? min : value;
	}

	inline void clampi(int &value, int min, int max)
	{
		value = (value > max) ? max : (value < min) ? min : value;
	}

	// returns a random number between 0 and limit inclusive.
	inline int nextInt(int limit) 
	{
		int divisor = 32767/(limit+1);
		clampi(divisor, 1, 32767);
		int retval;

		do 
		{ 
			retval = rand() / divisor;
		} 

		while (retval > limit);

		return retval;
	}

	// returns a random number between lower and upper inclusive.
	inline int nextInt(int lower, int upper) 
	{
		int range = abs(upper-lower);
		return nextInt(range) + lower;
	}

	// returns a random number between lower and upper inclusive.
	inline int nextRandomIndexBetween(int min, int max) 
	{
		static int pp = -1;
		static int p = -1;

		int index = nextInt(min, max);

		while (index == p || index == pp)
		{
			index = nextInt(min, max);
		}

		pp = p;
		p = index;

		return index;
	}

	inline float nextFloat(float min, float max) 
	{
		float random = ((float) rand()) / (float) RAND_MAX;
		float diff = max - min;
		float r = random * diff;
		return min + r;
	}
}

#endif 
