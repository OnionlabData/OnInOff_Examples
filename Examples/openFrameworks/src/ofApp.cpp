#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup ()
{
	ofSetWindowTitle ("OnInOff");
	ofSetFrameRate (60); // run at 60 fps

	// listen on the given port
	ofLog () << "Listening for osc messages on port " << PORT;
	mReceiver.setup (PORT);
}

//--------------------------------------------------------------
void ofApp::update ()
{
	while (mReceiver.hasWaitingMessages ())
	{
		// get the next message
		ofxOscMessage message;
		mReceiver.getNextMessage (message);

		if (message.getAddress () == PERSON_ADDRESS)
			mPersonsManager.updatePerson (message);
	}

	// check whether persons have not been updated
	mPersonsManager.checkPersonsLeft ();
}

//--------------------------------------------------------------
void ofApp::draw ()
{
	ofBackgroundGradient (100, 0);

	for (const auto& person : mPersonsManager.persons ())
	{
		const auto position = person.second.position ();
		ofDrawCircle (ofGetWidth () * position.x, ofGetHeight () * position.y, 10);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed (int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased (int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved (int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged (int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed (int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased (int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered (int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited (int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized (int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage (ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent (ofDragInfo dragInfo)
{

}