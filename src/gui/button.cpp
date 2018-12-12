#include "button.h"

Button::Button() {}

Button::~Button() {}

void Button::setup(string n, const ofColor &bColor, const std::string& fFile, const ofColor &fColor, int fSize) {
	ofRegisterMouseEvents(this);
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
		(height - fontType.stringHeight(name)) / 2 + fontType.stringHeight(name) + yPos);
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

void Button::setVisible(bool v) {
	visible = v;
}

void Button::mouseMoved(ofMouseEventArgs &args) {}

void Button::mouseDragged(ofMouseEventArgs &args) {}

void Button::mousePressed(ofMouseEventArgs &args) {
	if (visible) {
		if (args.x > xPos && args.x < xPos + width && args.y > yPos && args.y < yPos + height) {
			ofVec2f mousePos = ofVec2f(args.x, args.y);
			ofNotifyEvent(clicked, mousePos, this);
		}
	}
}

void Button::mouseReleased(ofMouseEventArgs &args) {}

void Button::mouseScrolled(ofMouseEventArgs &args) {}

void Button::mouseEntered(ofMouseEventArgs &args) {}

void Button::mouseExited(ofMouseEventArgs &args) {}