// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __MANAGER_H__
#define __MANAGER_H__

class Manager
{
protected:

	bool mIsStarted;

public:

	Manager() {}
	virtual ~Manager() {}

	virtual void startup() = 0;
	virtual void shutdown() = 0;

	bool isStarted() 
	{ 
		return mIsStarted; 
	}
};

#endif