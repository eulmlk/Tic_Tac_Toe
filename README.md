# Simple Tic Tac Toe Application with Difficulties

This is a minimal Tic Tac Toe application written in C++ using the SDL library. It features both two-player and one-player modes with three difficulty levels: easy, medium, and hard.
**Note**: This project is compatible only with Linux and Unix systems.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Game Modes](#game-modes)
- [Difficulties](#difficulties)
- [License](#license)

---

## Features

- Two-player mode: Play against a friend locally.
- One-player mode: Challenge the computer with different difficulty levels.
- Multiple difficulty levels to suit different player preferences.

## Requirements

- C++ compiler with C++17 support
- SDL library installed
- SDL_ttf library installed

## Installation

1. Clone the repository:

```bash
git clone https://github.com/eulmlk/Tic_Tac_Toe.git
```

2. Compile the code:

```bash
cd Tic_Tac_Toe
g++ -std=c++17 src/*.cpp -I include/ -o TicTacToe -lSDL2 -lSDL2_ttf
```

## Usage

To start the application, run the compiled `TicTacToe` executable.

```bash
./TicTacToe
```

## Game Modes

### Two-player Mode

In this mode, two players take turns to make their moves.

### One-player Mode

In this mode, you can play against the computer. You have the option to select the difficulty level.

## Difficulties

### Easy

- The computer makes random moves.

### Medium

- The computer employs a basic strategy to try to win or block the player.

### Hard

- The computer uses a sophisticated algorithm, minimax algorithm, to play optimally.

## License

This project is licensed under the [MIT License](LICENSE).

---

Enjoy playing Tic Tac Toe! If you have any feedback or suggestions, feel free to let me know.
