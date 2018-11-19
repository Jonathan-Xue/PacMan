#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	/*
	UIUC CS126 Final Project
	 _ __   __ _  ___ _ __ ___   __ _ _ __
	| '_ \ / _` |/ __| '_ ` _ \ / _` | '_ \
	| |_) | (_| | (__| | | | | | (_| | | | |
	| .__/ \__,_|\___|_| |_| |_|\__,_|_| |_|
	|_|
	*/

	// setup the GL context (width, height, OF_WINDOW/OF_FULLSCREEN)
	ofSetupOpenGL(672, 864, OF_WINDOW);
	ofRunApp(new ofApp());
}