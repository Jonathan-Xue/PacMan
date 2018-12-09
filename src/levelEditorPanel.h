#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "enums.h"

#include "board.h"
#include "tile.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class LevelEditorPanel {
	
	public:
		// Default Constructor
		LevelEditorPanel();

		// Parametrized Constructor
		LevelEditorPanel(EditorOptions *ceo);

		// Copy Constructor
		LevelEditorPanel(const LevelEditorPanel& other) = default;

		// Transfer Constructor
		LevelEditorPanel(LevelEditorPanel&& other) = default;

		// Destructor
		~LevelEditorPanel();

		/*
			Checks To See If An (x,y) Coordinate Is Inside Bounds
				@param: x
				@param: y
				@return: true/false
		*/
		bool withinBounds(int x, int y);

		// Draw
		void draw();

		// Listeners
		void editorNumRowsSliderListener(int &value);
		void editorNumColsSliderListener(int &value);

		void editorWallBlockButtonListener();
		void editorRegularBlockButtonListener();
		void editorStandardPelletBlockButtonListener();
		void editorPowerPelletBlockButtonListener();

		void editorPacmanSpriteButtonListener();

		void editorBlinkySpriteButtonListener();
		void editorBlinkyHomeTileButtonListener();

		void editorPinkySpriteButtonListener();
		void editorPinkyHomeTileButtonListener();

		void editorInkySpriteButtonListener();
		void editorInkyHomeTileButtonListener();

		void editorClydeSpriteButtonListener();
		void editorClydeHomeTileButtonListener();

		void mouseMoved(ofMouseEventArgs & args) {}
		void mouseDragged(ofMouseEventArgs & args) {}
		void mousePressed(ofMouseEventArgs & args) {}
		void mouseReleased(ofMouseEventArgs & args) {}
		void mouseScrolled(ofMouseEventArgs & args) {}
		void mouseEntered(ofMouseEventArgs & args) {}
		void mouseExited(ofMouseEventArgs & args) {}

		// Getters
		int getRows();
		int getCols();

	private:
		EditorOptions *currentEditorOption;

		ofxPanel levelEditorPanel;

		ofParameter<int> editorNumRowsSlider;
		ofParameter<int> editorNumColsSlider;

		ofxButton editorWallBlockButton;
		ofxButton editorRegularBlockButton;
		ofxButton editorStandardPelletBlockButton;
		ofxButton editorPowerPelletBlockButton;

		ofxButton editorPacmanSpriteButton;

		ofxButton editorBlinkySpriteButton;
		ofxButton editorBlinkyHomeTileButton;

		ofxButton editorPinkySpriteButton;
		ofxButton editorPinkyHomeTileButton;

		ofxButton editorInkySpriteButton;
		ofxButton editorInkyHomeTileButton;

		ofxButton editorClydeSpriteButton;
		ofxButton editorClydeHomeTileButton;

};