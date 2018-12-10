#pragma once

#include "button.h"

class RoundedButton : public Button {

public:
	// Default Constructor
	RoundedButton();

	// Constructor
	RoundedButton(int r);

	// Parameterized Constructor
	RoundedButton(int r1, int r2, int r3, int r4);

	// Transfer Constructor
	RoundedButton(const RoundedButton& other) = default;

	// Copy Constructor
	RoundedButton(RoundedButton&& other) = default;

	// Destructor
	~RoundedButton();

	// Copy Assignment Operator
	RoundedButton& operator=(const RoundedButton& other) = default;

	// Transfer Assignment Operator
	RoundedButton& operator=(RoundedButton&& other) = default;

	// Draw
	void draw();

	// Setters
	void setRadius(int r);
	void setRadius(int r1, int r2, int r3, int r4);

private:
	int topLeftRadius;
	int topRightRadius;
	int bottomRightRadius;
	int bottomLeftRadius;

};