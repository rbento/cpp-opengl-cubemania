
#include "entity.h"

vector<Entity*> Entity::mEntities = vector<Entity*>();

Entity::Entity(const string& _tag, int _id) : mTag(_tag), mId(_id)
{
	srand((unsigned int)time(0));

	add(*this);

	Logger::outputs("Entity", "An entity was created with id", mId);
}

Entity::~Entity()
{
	for (set<Component*>::iterator it = mComponents.begin(); it != mComponents.end();)
	{
		delete (*it);
		it = mComponents.erase(it);
	}

	for (vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end();)
	{
		if (mId == (*it)->id())
		{
			it = mEntities.erase(it);
		}
		else
		{
			++it;
		}
	}

	stringstream out;
	out << "An entity with id " << mId <<" was destroyed.";
	Logger::outputs("Entity", out.str());
}

bool Entity::nextIdExists(const int _id) const
{
	if (mEntities.empty())
	{
		return false;
	}

	for (vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
	{
		if (_id == (*it)->id())
		{
			return true;
		}
	}

	return false;
}

int Entity::nextId()
{
	int id = nextInt(rand());

	while (nextIdExists(id))
	{
		id = nextInt(rand());
	}

	return id;
}

void Entity::add(Entity& _entity)
{
	_entity.mId = nextId();

	mEntities.push_back(&_entity);
}

Entity* Entity::findByTag(const string& _tag)
{
	if (_tag.empty())
	{
		return 0;
	}

	for (vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
	{
		if (_tag == (*it)->tag())
		{
			return *it;
		}
	}

	return 0;
}

void Entity::clear()
{
	for (vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end();)
	{
		delete (*it);
		it = mEntities.erase(it);
	}
}

int Entity::count()
{
	return mEntities.size();
}

int Entity::id() const
{
	return mId;
}

string Entity::tag() const
{
	return mTag;
}

Transform* Entity::transform()
{
	return &mTransform;
}

string Entity::toString()
{
	stringstream ss;
	ss << "Entity [ id:" << mId << ", tag:" << mTag << ", transform: " << mTransform.toString() << " ]";
	return ss.str();
}
