# PacMan
## Project Details
Build a standard game of PacMan using OpenFrameworks. Input will be controlled either via WASD or through a joystick connected to an Arduino.

### Standard PacMan Rules
#### Board Design
* Each tile is 8 pixels by 8 pixels
* Screen Size: 28 tiles by 36 tiles
* Playing Board Size: 28 tiles By 31 tiles

#### Point System
* There are 240 regular dots on the board
    * Each regular dot is worth 10 points
* There are 4 energizer dots on the board
    * Each energizer dot is worth 50 points
    * Edible ghosts scale (single session): 200 points, 400 points, 800 points, 1600 points
* Upon reaching 10,000 points, an extra life is gained

#### Ghosts
* Release
    * Blinky
        * Starts outside the ghost box
    * Pinky
        * Released immediately
    * Inky
        * Released when PacMan consumes 30 dots
    * Clyde
        * Released when PacMan consumes 80 dots
* Tracking
    * Blinky
        * Current PacMan tile
    * Pinky
        * Four tiles ahead of PacMan's current direction of travel
    * Inky
        * Resultant tile of doubling the vector from Inky's current position to two tiles in front of PacMan's current direction of travel 
    * Clyde
        * Within eight squares of PacMan, bottom-left tile
        * Else, current PacMan tile
* Scatter & Chase Phases
    1. Scatter for 7 seconds, then Chase for 20 seconds.
    2. Scatter for 7 seconds, then Chase for 20 seconds.
    3. Scatter for 5 seconds, then Chase for 20 seconds.
    4. Scatter for 5 seconds, then switch to Chase mode permanently.

### Optional Enhancements
* Highscore File
* Music
* Multiplayer
    * Timed, competitive mode in which players compete to receive the most points within a pre-determined period of time
* Multiple maps
    * Pre-defined custom maps
    * User-inputted custom maps

## Libraries
* ofxGui
* ofxArduino or ofxSerial

## Prior Experience
Not Applicable. No prior work has been done regarding the development of PacMan in any language. Experience with OpenFrameworks is limited to the development of Snake.