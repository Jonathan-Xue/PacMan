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
	ofSetupOpenGL(1024, 768, OF_WINDOW); 
	ofSetFrameRate(60);
	ofRunApp(new ofApp());
}
