#pragma once

#include "ofVec2f.h"

#define TIME_PERSON_LEFT 300; // milliseconds

/**
 * @class Person
 * @brief Represents an individual with position, height, orientation, and size attributes.
 *
 * Also tracks the last time the person's coordinates were updated, allowing detection of inactivity.
 */
class Person
{

public:

	/**
	 * @brief Constructs a Person with a given unique ID.
	 *
	 * @param id The identifier associated with the person.
	 */
	explicit Person (int id);

	/**
	 * @brief Returns the current position of the person.
	 *
	 * @return A 2D vector representing the person's position.
	 */
	ofVec2f position () const;

	/**
	 * @brief Sets the person's position.
	 *
	 * Updates the internal timestamp for the last coordinate update.
	 *
	 * @param position A 2D vector representing the new position.
	 */
	void setPosition (ofVec2f position);

	/**
	 * @brief Returns the current height of the person.
	 *
	 * @return The height as a float.
	 */
	float height () const;

	/**
	 * @brief Sets the height of the person.
	 *
	 * @param height The new height value.
	 */
	void setHeight (float height);

	/**
	 * @brief Returns the current angle of the person.
	 *
	 * @return The angle as an integer (typically in degrees).
	 */
	int angle () const;

	/**
	 * @brief Sets the angle of the person.
	 *
	 * @param angle The new angle value.
	 */
	void setAngle (int angle);

	/**
	 * @brief Returns the current size of the person.
	 *
	 * @return The size as a float.
	 */
	float size () const;

	/**
	 * @brief Sets the size of the person.
	 *
	 * @param size The new size value.
	 */
	void setSize (float size);

	/**
	 * @brief Indicates whether the person is considered to have left.
	 *
	 * This is typically based on the time since the last coordinate update.
	 *
	 * @return True if the person is considered inactive or gone, false otherwise.
	 */
	bool hasLeft () const;

private:

	/**
	 * @brief The unique ID associated with this person.
	 */
	int mId = -1;

	/**
	 * @brief The current 2D position of the person.
	 */
	ofVec2f mPosition;

	/**
	 * @brief The height of the person.
	 */
	float mHeight = 0.0f;

	/**
	 * @brief The angle (orientation) of the person.
	 */
	int mAngle = 0;

	/**
	 * @brief The size or area associated with the person.
	 */
	float mSize = 0.0f;

	/**
	 * @brief Timestamp of the last position update.
	 *
	 * Used to determine if the person has become inactive.
	 */
	std::chrono::steady_clock::time_point mLastTimeCoordUpdated;
};
