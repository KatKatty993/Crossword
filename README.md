# Crossword Game (C++ with SFML)

## Description

This is a simple crossword puzzle game implemented in **C++** using the **SFML** library. The game features three levels, each containing 3 horizontal Ukrainian-language clues. The user fills in the crossword grid and checks their answers with a button.

## Features

- Ukrainian interface and full support for Ukrainian characters.
- Three unique levels with different clues.
- **"Check"** button that displays:
  - ✅ A green checkmark if all answers are correct.
  - ❌ A red cross if any answers are incorrect or missing.
- Animated transitions between levels (left/right).
- Cells automatically move to the next letter after typing.
- Clean and intuitive visual interface.

## Screenshot

![Game Interface](bfcd94c2-b058-4ee0-a328-76f6ddf280b0.png)

## Requirements

- C++17 or later
- [SFML 2.5+](https://www.sfml-dev.org/download.php)
- The `OpenSans-Regular.ttf` font must be in the same directory as the executable.

## Build Instructions (using CMake)

```bash
mkdir build
cd build
cmake ..
make

Or compile manually:

g++ ddddd.cpp -o crossword -lsfml-graphics -lsfml-window -lsfml-system

Run the Game

./crossword

Author

KatKatty993
