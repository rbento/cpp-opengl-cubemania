
#include "transform.h"

Transform::Transform(Vector3 _position, 
					 Vector3 _rotation, 
					 Vector3 _scale) 
	: position(_position), 
	  rotation(_rotation), 
	  scale(_scale)
{
}

string Transform::toString()
{
	stringstream result;
	result << "[ " << "position: " << position.toString() << ", rotation: " << rotation.toString() << ", scale: " << scale.toString() << " ]";
	return  result.str();
}