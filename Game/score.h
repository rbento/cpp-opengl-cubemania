// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __SCORE_H__
#define __SCORE_H__

#include <string>

#include "time.h"
#include "text_manager.h"

using namespace std;

class Score
{
private:

	TextManager* mText;
	string mValue;
	float mX, mY;
	Uint32 mTimeout;
	bool mDone;

public:

	Score(const string& value, float x, float y, Uint32 _time);

	void update(const Time& _time);

	bool done();
};

#endif