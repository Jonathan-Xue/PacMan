#include "levelEditorPanel.h"

LevelEditorPanel::LevelEditorPanel() {}

LevelEditorPanel::LevelEditorPanel(EditorOptions *ceo) {
	currentEditorOption = ceo;

	// Setup
	levelEditorPanel.setup("Variables");

	levelEditorPanel.add(editorNumRowsSlider.set("Rows", 31, 25, 50));
	levelEditorPanel.add(editorNumColsSlider.set("Columns", 28, 25, 50));

	levelEditorPanel.add(editorWallBlockButton.setup("Wall Block"));
	levelEditorPanel.add(editorRegularBlockButton.setup("Regular Block"));
	levelEditorPanel.add(editorStandardPelletBlockButton.setup("Standard Pellet Block"));
	levelEditorPanel.add(editorPowerPelletBlockButton.setup("Power Pellet Block"));

	levelEditorPanel.add(editorPacmanSpriteButton.setup("Pacman Sprite"));

	levelEditorPanel.add(editorBlinkySpriteButton.setup("Blinky Sprite"));
	levelEditorPanel.add(editorBlinkyHomeTileButton.setup("Blinky Home Position"));

	levelEditorPanel.add(editorPinkySpriteButton.setup("Pinky Sprite"));
	levelEditorPanel.add(editorPinkyHomeTileButton.setup("Pinky Home Position"));

	levelEditorPanel.add(editorInkySpriteButton.setup("Inky Sprite"));
	levelEditorPanel.add(editorInkyHomeTileButton.setup("Inky Home Position"));

	levelEditorPanel.add(editorClydeSpriteButton.setup("Clyde Sprite"));
	levelEditorPanel.add(editorClydeHomeTileButton.setup("Clyde Home Position"));

	// Listeners
	editorNumRowsSlider.addListener(this, &LevelEditorPanel::editorNumRowsSliderListener);
	editorNumColsSlider.addListener(this, &LevelEditorPanel::editorNumColsSliderListener);

	editorWallBlockButton.addListener(this, &LevelEditorPanel::editorWallBlockButtonListener);
	editorRegularBlockButton.addListener(this, &LevelEditorPanel::editorRegularBlockButtonListener);
	editorStandardPelletBlockButton.addListener(this, &LevelEditorPanel::editorStandardPelletBlockButtonListener);
	editorPowerPelletBlockButton.addListener(this, &LevelEditorPanel::editorPowerPelletBlockButtonListener);

	editorPacmanSpriteButton.addListener(this, &LevelEditorPanel::editorPacmanSpriteButtonListener);

	editorBlinkySpriteButton.addListener(this, &LevelEditorPanel::editorBlinkySpriteButtonListener);
	editorBlinkyHomeTileButton.addListener(this, &LevelEditorPanel::editorBlinkyHomeTileButtonListener);

	editorPinkySpriteButton.addListener(this, &LevelEditorPanel::editorPinkySpriteButtonListener);
	editorPinkyHomeTileButton.addListener(this, &LevelEditorPanel::editorPinkyHomeTileButtonListener);

	editorInkySpriteButton.addListener(this, &LevelEditorPanel::editorInkySpriteButtonListener);
	editorInkyHomeTileButton.addListener(this, &LevelEditorPanel::editorInkyHomeTileButtonListener);

	editorClydeSpriteButton.addListener(this, &LevelEditorPanel::editorClydeSpriteButtonListener);
	editorClydeHomeTileButton.addListener(this, &LevelEditorPanel::editorClydeHomeTileButtonListener);
}

LevelEditorPanel::~LevelEditorPanel() {}

bool LevelEditorPanel::withinBounds(int x, int y) {
	return (x > levelEditorPanel.getPosition().x &&
		x < levelEditorPanel.getPosition().x + levelEditorPanel.getWidth() &&
		y > levelEditorPanel.getPosition().y &&
		y < levelEditorPanel.getPosition().y + levelEditorPanel.getHeight());
}

void LevelEditorPanel::draw() {
	levelEditorPanel.draw();
}

void LevelEditorPanel::editorNumRowsSliderListener(int &value) {
	(*currentEditorOption) = ROW_ADJUSTMENT;
}

void LevelEditorPanel::editorNumColsSliderListener(int &value) {
	(*currentEditorOption) = COL_ADJUSTMENT;
}

void LevelEditorPanel::editorWallBlockButtonListener() {
	(*currentEditorOption) = WALL_BLOCK;
}

void LevelEditorPanel::editorRegularBlockButtonListener() {
	(*currentEditorOption) = REGULAR_BLOCK;
}

void LevelEditorPanel::editorStandardPelletBlockButtonListener() {
	(*currentEditorOption) = STANDARD_PELLET_BLOCK;
}

void LevelEditorPanel::editorPowerPelletBlockButtonListener() {
	(*currentEditorOption) = POWER_PELLET_BLOCK;
}

void LevelEditorPanel::editorPacmanSpriteButtonListener() {
	(*currentEditorOption) = PACMAN_SPRITE;
}

void LevelEditorPanel::editorBlinkySpriteButtonListener() {
	(*currentEditorOption) = BLINKY_SPRITE;
}

void LevelEditorPanel::editorBlinkyHomeTileButtonListener() {
	(*currentEditorOption) = BLINKY_HOME_TILE;
}

void LevelEditorPanel::editorPinkySpriteButtonListener() {
	(*currentEditorOption) = PINKY_SPRITE;
}

void LevelEditorPanel::editorPinkyHomeTileButtonListener() {
	(*currentEditorOption) = PINKY_HOME_TILE;
}

void LevelEditorPanel::editorInkySpriteButtonListener() {
	(*currentEditorOption) = INKY_SPRITE;
}

void LevelEditorPanel::editorInkyHomeTileButtonListener() {
	(*currentEditorOption) = INKY_HOME_TILE;
}

void LevelEditorPanel::editorClydeSpriteButtonListener() {
	(*currentEditorOption) = CLYDE_SPRITE;
}

void LevelEditorPanel::editorClydeHomeTileButtonListener() {
	(*currentEditorOption) = CLYDE_HOME_TILE;
}

int LevelEditorPanel::getRows() {
	return editorNumRowsSlider;
}

int LevelEditorPanel::getCols() {
	return editorNumColsSlider;
}