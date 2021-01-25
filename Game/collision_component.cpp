
#include "collision_component.h"

CollisionComponent::CollisionComponent(Entity& _owner) : Component(_owner) 
{
	aabb.center = &_owner.transform()->position;
}

CollisionComponent::~CollisionComponent()
{
}

bool CollisionComponent::collidesWith(Entity& _other)
{
	CollisionComponent* other = _other.getComponent<CollisionComponent>();

	if (other)
	{
		return testAABB(aabb, other->aabb);
	}

	return false;
};

bool CollisionComponent::testAABB(const AABB& a, const AABB& b)
{
    if (abs(a.center->x - b.center->x) > (a.radius[0] + b.radius[0])) return false;
    if (abs(a.center->y - b.center->y) > (a.radius[1] + b.radius[1])) return false;
    if (abs(a.center->z - b.center->z) > (a.radius[2] + b.radius[2])) return false;
    
    return true;
};

void CollisionComponent::width(GLfloat _value)
{
	clampf(_value, 0.0f, 1000.0f);
	aabb.radius[0] = _value;
}

GLfloat CollisionComponent::width()
{
	return aabb.radius[0];
}

void CollisionComponent::height(GLfloat _value)
{
	clampf(_value, 0.0f, 1000.0f);
	aabb.radius[1] = _value;
}

GLfloat CollisionComponent::height()
{
	return aabb.radius[1];
}

void CollisionComponent::depth(GLfloat _value)
{
	clampf(_value, 0.0f, 1000.0f);
	aabb.radius[2] = _value;
}

GLfloat CollisionComponent::depth()
{
	return aabb.radius[2];
}