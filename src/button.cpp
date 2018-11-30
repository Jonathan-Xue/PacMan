#include "button.h"

Button::Button(){}

Button::~Button(){}

void Button::setup(string n, const ofColor &bColor, const std::string& fFile, const ofColor &fColor, int fSize) {
	name = n;
	backgroundColor = bColor;

	fontFile = fFile;
	fontColor = fColor;
	fontSize = fSize;

	fontType.load(fontFile, fontSize, true, true);
}

void Button::draw() {
	ofSetColor(backgroundColor);
	ofDrawRectangle(xPos, yPos, width, height);

	ofSetColor(fontColor);
	fontType.drawString(name, 
		(width - fontType.stringWidth(name)) / 2 + xPos,
		(height - fontType.stringHeight(name)) / 2 + yPos);
}

string Button::getName() {
	return name;
}

vector<int> Button::getPosition() {
	return vector<int>{ xPos, yPos };
}

vector<int> Button::getSize() {
	return vector<int>{ width, height };
}

void Button::setBackgroundColor(const ofColor &bColor) {
	backgroundColor = bColor;
}

void Button::setFont(const std::string& fFile, const ofColor &fColor, int fSize) {
	fontFile = fFile;
	fontColor = fColor;
	fontSize = fSize;

	fontType.load(fontFile, fontSize, true, true);
}

void Button::setFontType(const std::string& fFile) {
	fontFile = fFile;

	fontType.load(fontFile, fontSize, true, true);
}

void Button::setFontColor(const ofColor &fColor) {
	fontColor = fColor;
}

void Button::setFontSize(int fSize) {
	fontSize = fSize;

	fontType.load(fontFile, fontSize, true, true);
}

void Button::setName(string n) {
	name = n;
}

void Button::setPosition(int x, int y) {
	xPos = x;
	yPos = y;
}

void Button::setSize(int w, int h) {
	width = w;
	height = h;
}