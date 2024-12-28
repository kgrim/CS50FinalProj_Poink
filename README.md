# POINK! Pong Game
#### Video Demo:  <[URL HERE](https://youtu.be/WfLZE8ulS7M)>

#### Description:
POINK! is a simple 2D pong game written in C++ using the Raylib library. It allows players to enjoy a classic pong experience with both single-player and two-player modes. The game includes a main menu, gameplay mechanics, and a game over screen with options to restart or exit.

## Features

- **Single Player**: Play against AI.
- **Two Player**: Play with a friend locally.
- **Menu Navigation**: Select game mode or exit.
- **Scoreboard**: Keep track of player scores.
- **Game Over**: Retry or exit after the game ends.

## Requirements

To run this game, you need the following dependencies:

- **C++ compiler**: A C++11 compatible compiler (e.g., GCC, Clang, MSVC).
- **Raylib**: A simple and easy-to-use game programming library that you can find [here](https://www.raylib.com/).

### Raylib Installation

1. **Windows**: Download the precompiled Raylib binaries from the official website or use a package manager like `vcpkg` to install Raylib.
2. **Mac**: You can install Raylib via Homebrew:
    ```
    brew install raylib
    ```
3. **Linux**: Use your distribution's package manager to install Raylib, for example on Ubuntu:
    ```
    sudo apt-get install libraylib-dev
    ```



### 1. Clone the repository:

```bash
git clone https://github.com/your-username/poink-game.git
cd poink-game
```

### Build the project:

You can build the game using any C++ compiler that supports C++11. Here are the instructions for a few common environments:

```bash
g++ -std=c++11 main.cpp -o poink-game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

#### Using CMake:
1. Create a build directory:
```bash
mkdir build
cd build
```

2. Run CMake:
```bash
cmake ..
```

3. Build the project:
```bash
make
```

4. Run the game:
```bash
./poink-game
```


## How to Play

- **Main Menu**: Navigate using the UP and DOWN arrow keys to select between "1 Player", "2 Player", or "Exit".
- **In-Game**:
  - Player 1 (Blue) uses W to move up and S to move down.
  - Player 2 (Red) uses the UP and DOWN arrow keys to move.
  - AI (if active) automatically moves based on the ball position.
- **Game Over**: Once the score reaches 10, the game will show the game over screen. You can press R to retry or ESC to exit the game.

## File Structure

```bash
poink-game/
│
├── src/
│   ├── ai.h            # AI logic for controlling the second player
│   ├── ball.h          # Ball logic and collision detection
│   ├── ball.cpp        # Ball implementation
│   ├── paddle.h        # Paddle logic and rendering
│   ├── player.h        # Player logic, score tracking, and paddle control
│   ├── player.cpp      # Player implementation
│   ├── main.cpp        # Main game loop, menu, gameplay, and game over
└── README.md           # This file
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.
