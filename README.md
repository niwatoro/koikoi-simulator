# Koi-Koi Simulator

A C++ implementation of the traditional Japanese card game Koi-Koi (こいこい) played with Hanafuda (花札) cards.

## Overview

This simulator allows players to enjoy the traditional Japanese card game Koi-Koi either against an AI opponent or watch AI players compete against each other. The game implements the complete ruleset of Koi-Koi, including all standard yaku (scoring combinations) and the signature "koi-koi" calling mechanic.

## Features

- Two game modes:
  - Player vs AI
  - AI vs AI (simulation mode)
- Complete implementation of Hanafuda card mechanics
- Full yaku (scoring combinations) system
- Configurable number of rounds (default: 12)
- Interactive command-line interface

## Building the Project

### Prerequisites

- CMake (version 3.10 or higher)
- C++17 compatible compiler
- Make or equivalent build tool

### Build Instructions

1. Clone the repository
2. Create and navigate to the build directory:

```bash
cd koikoi_simulator
```

3. Build the project:

```bash
cmake .
make
```

The executable will be created in the `build` directory.

## Running the Game

After building, run the executable from the build directory:

```bash
./build/koikoi_simulator
```

Follow the on-screen prompts to:

1. Select game mode (Player vs AI or AI vs AI)
2. Set the number of rounds
3. Play the game according to the displayed instructions

## Project Structure

- `main.cpp` - Entry point and game menu
- `game.hpp/cpp` - Core game logic and flow control
- `card.hpp/cpp` - Hanafuda card implementation
- `player.hpp/cpp` - Player class (both human and AI)
- `yaku.hpp/cpp` - Scoring combination rules and calculations

## Game Rules

Koi-Koi is played with Hanafuda cards, where players try to create scoring combinations (yaku) with captured cards. Each round:

1. Players are dealt 8 cards each
2. 8 cards are placed on the table
3. Players take turns matching cards from their hand with cards on the table
4. When a yaku is completed, the player can choose to continue (koi-koi) or end the round
5. The game continues for the specified number of rounds.
