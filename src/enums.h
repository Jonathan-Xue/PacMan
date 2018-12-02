#pragma once

enum GameState {
	START,
	IN_PROGRESS,
	PAUSED,
	GAME_OVER,
	HIGH_SCORE
};

enum GhostType {
	UNDEFINED,
	BLINKY,
	PINKY,
	INKY,
	CLYDE
};

enum SpriteMode {
	FRIGHTENED,
	SCATTER,
	CHASE
};