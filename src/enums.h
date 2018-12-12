#pragma once

enum GameState {
	START,
	LEVEL_EDITOR,
	IN_PROGRESS,
	PAUSED,
	GAME_OVER,
	HIGH_SCORE
};

enum EditorOptions {
	ROW_ADJUSTMENT,
	COL_ADJUSTMENT,

	WALL_BLOCK,
	PATH_BLOCK,
	STANDARD_PELLET_BLOCK,
	POWER_PELLET_BLOCK,

	PACMAN_SPRITE,

	BLINKY_SPRITE,
	BLINKY_HOME_TILE,

	PINKY_SPRITE,
	PINKY_HOME_TILE,

	INKY_SPRITE,
	INKY_HOME_TILE,

	CLYDE_SPRITE,
	CLYDE_HOME_TILE
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