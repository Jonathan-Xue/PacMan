#include "RoundedButton.h"

RoundedButton::RoundedButton(){}

RoundedButton::RoundedButton(int r) {
	topLeftRadius = r;
	topRightRadius = r;
	bottomRightRadius = r;
	bottomLeftRadius = r;
}

RoundedButton::RoundedButton(int r1, int r2, int r3, int r4) {
	topLeftRadius = r1;
	topRightRadius = r2;
	bottomRightRadius = r3;
	bottomLeftRadius = r4;
}

RoundedButton::~RoundedButton(){}

void RoundedButton::draw() {
	ofSetColor(backgroundColor);
	ofDrawRectRounded(ofRectangle(xPos, yPos, width, height), topLeftRadius, topRightRadius, bottomRightRadius, bottomLeftRadius);

	ofSetColor(fontColor);
	fontType.drawString(name,
		(width - fontType.stringWidth(name)) / 2 + xPos,
		(height - fontType.stringHeight(name)) / 2 + fontType.stringHeight(name) + yPos);
}

void RoundedButton::setRadius(int r) {
	topLeftRadius = r;
	topRightRadius = r;
	bottomRightRadius = r;
	bottomLeftRadius = r;
}

void RoundedButton::setRadius(int r1, int r2, int r3, int r4) {
	topLeftRadius = r1;
	topRightRadius = r2;
	bottomRightRadius = r3;
	bottomLeftRadius = r4;
}