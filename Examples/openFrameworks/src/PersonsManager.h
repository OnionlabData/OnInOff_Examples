#pragma once

#include "Person.h"

#include "ofxOscMessage.h"

#define PERSON_ID_IDX 0
#define PERSON_POSX_IDX 1
#define PERSON_POSY_IDX 2
#define PERSON_HEIGHT_IDX 3
#define PERSON_ANGLE_IDX 4
#define PERSON_SIZE_IDX 5

/**
 * @class PersonsManager
 * @brief Manages a collection of Person objects, allowing updates and checks for departed persons.
 */
class PersonsManager
{

public:

	/**
	 * @brief Default constructor for PersonsManager.
	 */
	explicit PersonsManager () = default;

	/**
	 * @brief Returns the current map of tracked persons.
	 *
	 * @return A map where the key is the person's ID and the value is a Person object.
	 */
	std::unordered_map<int, Person> persons () const;

	/**
	 * @brief Updates a person's data based on the received OSC message.
	 *
	 * If the person identified in the message does not exist, they may be added.
	 *
	 * @param message An OSC message containing updated data for a person.
	 */
	void updatePerson (const ofxOscMessage& message);

	/**
	 * @brief Checks for persons that have left and removes them from tracking if necessary.
	 */
	void checkPersonsLeft ();

private:

	/**
	 * @brief Internal map storing all currently tracked persons.
	 *
	 * The key represents the person's ID and the value is the corresponding Person object.
	 */
	std::unordered_map<int, Person> mPersons;

};
