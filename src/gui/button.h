#pragma once

#include <string>
#include <vector>

#include "ofMain.h"

using std::string;
using std::vector;

class Button {

public:
	ofEvent<ofVec2f> clicked;

	// Default Constructor
	Button();

	// Transfer Constructor
	Button(const Button& other) = default;

	// Copy Constructor
	Button(Button&& other) = default;

	// Destructor
	~Button();

	// Copy Assignment Operator
	Button& operator=(const Button& other) = default;

	// Transfer Assignment Operator
	Button& operator=(Button&& other) = default;

	// Setup
	void setup(string n, const ofColor &bColor, const std::string& fFile, const ofColor &fColor, int fSize);

	// Draw
	void draw();

	// Getters
	string getName();
	vector<int> getPosition();
	vector<int> getSize();

	// Setters
	void setBackgroundColor(const ofColor &bColor);

	void setFont(const std::string& fFile, const ofColor &fColor, int fSize);
	void setFontType(const std::string& fFile);
	void setFontColor(const ofColor &fColor);
	void setFontSize(int fSize);

	void setName(string n);
	void setPosition(int x, int y);
	void setSize(int w, int h);

	void setVisible(bool v);

	// Events
	void mouseMoved(ofMouseEventArgs & args);
	void mouseDragged(ofMouseEventArgs & args);
	void mousePressed(ofMouseEventArgs & args);
	void mouseReleased(ofMouseEventArgs & args);
	void mouseScrolled(ofMouseEventArgs & args);
	void mouseEntered(ofMouseEventArgs & args);
	void mouseExited(ofMouseEventArgs & args);

protected:
	ofColor backgroundColor = ofColor(255, 255, 255);

	ofTrueTypeFont fontType;
	ofColor fontColor = ofColor(0, 0, 0);
	string fontFile = "";
	int fontSize = 0;

	string name = "";
	int xPos = 0;
	int yPos = 0;
	int width = 0;
	int height = 0;

	bool visible = false;

};