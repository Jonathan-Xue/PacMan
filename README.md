# PacMan
# Pacman
## How To Install

## How To Connect An Arduino Controller (See Wiki For Wiring Schematic)
1. Connect the computer via Bluetooth the the HC-05 module; the password is either '0000' or '1234'
2. Launch the game; the RGBLED should turn green upon a successful connection

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
    * Inky
        * Scatter Target: Inky's home tile
        * Chase Target: Four tiles in front of Pacman
    * Pinky
        * Scatter Target: Pinky's home tile
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
* Edible Ghost: 200->400->800->1600 Points

## Further Documentation (Developers)
* See Wiki