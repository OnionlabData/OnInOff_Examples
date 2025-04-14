#include "PersonsManager.h"


std::unordered_map<int, Person> PersonsManager::persons () const
{
	return mPersons;
}

void PersonsManager::updatePerson (const ofxOscMessage& message)
{
	const auto id = message.getArgAsInt (PERSON_ID_IDX);
	const auto posX = message.getArgAsFloat (PERSON_POSX_IDX);
	const auto posY = message.getArgAsFloat (PERSON_POSY_IDX);

	auto personIt = mPersons.find (id);
	if (personIt == mPersons.end ()) // person doesn't exist
		personIt = mPersons.emplace (id, Person (id)).first;

	personIt->second.setPosition (ofVec2f (posX, posY));

	if (message.getNumArgs () > 3) // has height, angle and size
	{
		const auto height = message.getArgAsFloat (PERSON_HEIGHT_IDX);
		const auto angle = message.getArgAsInt (PERSON_ANGLE_IDX);
		const auto size = message.getArgAsFloat (PERSON_SIZE_IDX);

		personIt->second.setHeight (height);
		personIt->second.setAngle (angle);
		personIt->second.setSize (size);
	}
}

void PersonsManager::checkPersonsLeft ()
{
	auto personsIt = mPersons.begin ();
	while (personsIt != mPersons.end ())
	{
		if (personsIt->second.hasLeft ())
			personsIt = mPersons.erase (personsIt);
		else
			personsIt++;
	}
}