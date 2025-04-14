#include "Person.h"

Person::Person (const int id) : mId (id)
{
}

ofVec2f Person::position () const
{
	return mPosition;
}

void Person::setPosition (const ofVec2f position)
{
	mPosition = position;

	mLastTimeCoordUpdated = std::chrono::high_resolution_clock::now ();
}

float Person::height () const
{
	return mHeight;
}

void Person::setHeight (const float height)
{
	mHeight = height;
}

int Person::angle () const
{
	return mAngle;
}

void Person::setAngle (const int angle)
{
	mAngle = angle;
}

float Person::size () const
{
	return mSize;
}

void Person::setSize (const float size)
{
	mSize = size;
}

bool Person::hasLeft () const
{
	const auto msElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now () - mLastTimeCoordUpdated).count ();
	return msElapsed > TIME_PERSON_LEFT;
}