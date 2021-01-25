
#include "score.h"

Score::Score(const string& _value, float _x, float _y, Uint32 _time) : mText(TextManager::instance()), mValue(_value), mX(_x), mY(_y), mTimeout(_time + 800),mDone(false)
{
}

void Score::update(const Time& _time)
{
	static Color color = Color(1.0f, 0.6f, 0.0f, 0.9f);

	if (mDone)
	{
		return;
	}

	if (_time.present <= mTimeout)
	{
		mText->placeAt(mValue, color, mX, mY);
		mY += 1.0f;
	}
	else
	{
		mDone = true;
	}
}

bool Score::done()
{
	return mDone;
}