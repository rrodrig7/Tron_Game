# Tron Game

A simple Tron-style game implemented in C. Players control a moving diamon(player) that leaves a trail behind, and the goal is to avoid hitting the walls or trails(including your own). The game can be extended to include an opponent.

## Features

Player can move in four directions (up, down, left, right) using arrow keys.
- The player leaves a trail behind as it moves. <br>
- The game uses ncurses to handle rendering and input in the terminal <br>
- The player and opponent's trail length is limited, and the trail disappears after a certain length <br>

## Prerequisites

To build and run the game, you'll need the following:
- **ncurses Library**: Install `ncurses` on your system.
    - On Debian/Ubuntu:
    ```sh
        sudo apt-get install libncurses-dev
    ```
    - On macOS (using Homebrew):
    ```sh
        brew install ncurses
    ```

## Build Instructions:
### Using the Makefile
1. Clone the repository to your local machine:
```sh
    git clone <>
    cd Tron_Game
```
2. Compile the program 
```sh
    cmake .
    make
```
This will generate the executable tron_game.

3. Run the game:
```sh
    ./tron_game
```
4. Clean up the object files and the executable after running the game:
```sh
    make clean
```
5. To remove all generated files, including any CMake-related files:
```sh
    make clean-all
```

### Custom Build with GCC

If you prefer not to use the Makefile, you can manually compile the game using the following gcc command:
```sh
    gcc -o tron_game main.c init.c ai.c display.c game.c color.c -lncurses
    ```
This will compile all the source files and link the ncurses library to generate the `tron_game` executable
Run the executable file:
```sh
    ./tron_game
```

## How to Play 
Movement: Control the player's directions using the arrow keys:
- `Up` Arrow: Move up<br>
- `Down` Arrow: Move down<br>
- `Left` Arrow: Move Left<br>
- `Right` Arrow: Move right<br>
Avoid crashing into the walls, your own trail, or the opponent's trail.

## Future Features
- Add an AI opponent that moves using pathfinding algorithms (e.g., A*).<br>
- Support for multiplayer mode or two players competing in the same game.<br>

## Known Issues
- The first time the player's trail reaches the full length, it restarts from zero again. It just happens at the beginning. <br>
- Opponent logic needs improvement to simulate more realistic movement and decision-making.<br>

## Acknowledgments
* Inspired by the classic Tron light cycle game.
* Uses the ncurses library for terminal rendering and input handling. 
