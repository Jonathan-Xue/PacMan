# PacMan
## How To Install
### OpenFrameworks Project
1. Download OpenFrameworks [Link](https://openframeworks.cc/download/)
2. Use the project generator to create a new OpenFrameworks project with the addons: ofxGui, ofxSerial
3. Copy the contents of *bin* and *src* into the corresponding directories in the new project

### Arduino Controller
1. Download the Arduino IDE [Link](https://www.arduino.cc/en/Main/Software)
2. Setup the Arduino & components as detailed in the wiring schematic (see [Wiki](https://github.com/uiuc-fa18-cs126/finalproject-Jonathan-Xue/wiki))
3. Load the corresponding *.ino* file onto the Arduino

## How To Connect An Arduino Controller
1. Provide power to the Arduino; the RGBLED should turn on to indicate the controller is ready
2. Connect the computer via Bluetooth the the HC-05 module; the password is either '0000' or '1234'
3. Launch the game; the RGBLED should turn to green upon a successful connection

## Game Rules
### General
* All sprites must be within board bounds
* The game is over when Pacman is out of lives
* Board Size:
    * Minimum: 25 tiles by 25 tiles
    * Maximum: 50 tiles by 50 tiles
* Scatter & Chase Phases
    1. Ghosts scatter for 7 seconds, then chase for 20 seconds
    2. Ghosts scatter for 7 seconds, then chase for 20 seconds
    3. Ghosts scatter for 5 seconds, then chase for 20 seconds
    4. Ghosts scatter for 5 seconds, then switch to Chase mode permanently
* Frightened Phase
    * Occurs when Pacman eats a power pellet
    * Lasts for eight seconds; Ghosts start flashing when there are two seconds left
    * Ghosts travel at 87.5% of max speed
* Speed
    * Pacman Default Speed: 8.0 Tiles Per Second
        * Increases By 0.5 Tiles Per Second For Each Level Passed
    * Ghost Default Speed: 7.5 Tiles Per Second
        * Increases By 0.5 Tiles Per Second For Each Level Passed

### Pacman
* Three lives
* Movement
    * WASD
    * Eating a pellet slows it down by one frame
    * Eating a power pellet slows it down by three frames

### Ghosts
* Ghost Types
    * Blinky
        * Scatter Target: Blinky's home tile
        * Chase Target: Pacman's current tile
    * Pinky
        * Scatter Target: Pinky's home tile
        * Chase Target: Four tiles in front of Pacman
    * Inky
        * Scatter Target: Inky's home tile
        * Chase Target: Tile obtained by doubling the vector from Blinky's current tile position to two tiles in front of PacMan
    * Clyde
        * Scatter Target: Clyde's home tile
        * Chase Target: If Clyde is within eight squares of PacMan, then his home tile. Otherwise, Pacman's current tile

* Movement
    * Can only reverse direction under one of the following circumstances:
        1. Scatter Phase -> Chase Phase
        2. Chase Phase -> Scatter Phase
        3. Scatter or Chase Phase -> Frightened Phase
        4. No other available option
    * Scatter & Chase Phases
        * Travels in the direction which takes it closest to its target
    * Frightened Phase
        * Random

* Death
    * Target: Home tile
    * Ghosts travel at 200% speed
    * Passing through Pacman won't yield any effect

### Point System
* Regular Pellet: 10 Points
* Power Pellet: 50 Points
* Edible Ghost: 500 Points

## Further Documentation (Developers)
* See [Wiki](https://github.com/uiuc-fa18-cs126/finalproject-Jonathan-Xue/wiki)