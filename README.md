# SpaceWars

A terminal-based space shooter game written in C++. Battle against 3 enemies, collect coins, and progress through difficulty levels.

## Gameplay

- Control a spaceship at the bottom of the screen
- Shoot projectiles to destroy 3 enemy ships
- Collect coins to gain score and health
- Complete all 3 difficulty levels to win

### Controls

| Key | Action |
|-----|--------|
| Left Arrow | Move left |
| Right Arrow | Move right |
| Spacebar | Fire |
| Escape | Exit to menu |

### Difficulty Levels

- **Easy**: Enemies have less health, barriers protect you longer
- **Medium**: Moderate enemy health, fewer barriers
- **Hard**: Enemies have more health, no barriers

## Building

### Requirements

**Linux:**
- CMake 3.10+
- GCC/G++ with C++11 support
- ncurses development library

```bash
# Debian/Ubuntu
sudo apt install build-essential cmake libncurses-dev

# Arch Linux
sudo pacman -S base-devel cmake ncurses
```

**Windows:**
- CMake 3.10+
- Visual Studio or MinGW with C++11 support

### Compile

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Run

```bash
cd build
./SpaceWars      # Linux
SpaceWars.exe    # Windows
```

## Project Structure

```
gameproject/
├── CMakeLists.txt
├── board.txt              # Game arena layout (36x90)
├── include/
│   ├── console.h          # Cross-platform terminal API
│   ├── constants.h        # Game constants and enums
│   ├── entity.h           # Player/enemy functions
│   ├── fileio.h           # Save/load functions
│   ├── game.h             # Game logic functions
│   ├── globals.h          # Global variable declarations
│   ├── types.h            # Data structures
│   └── ui.h               # Menu and UI functions
└── src/
    ├── console.cpp        # Terminal implementation (Win32/ncurses)
    ├── entity.cpp         # Player and enemy logic
    ├── fileio.cpp         # High score persistence
    ├── game.cpp           # Board, coins, difficulty
    ├── globals.cpp        # Global variable definitions
    ├── main.cpp           # Game loop and state machine
    └── ui.cpp             # Menus and HUD
```

## Features

- Cross-platform support (Windows and Linux)
- ASCII art graphics
- 3 enemy types with different behaviors
- Coin collection system
- High score tracking (saved to `gameData.txt`)
- Progressive difficulty with barrier mechanics

## Architecture

The game uses a state machine for screen management:

```
MAIN_MENU → PLAY_GAME → LEVEL_COMPLETE → PLAY_GAME (next level)
    │           │
    │           └→ GAME_OVER → MAIN_MENU
    │           └→ GAME_WON → MAIN_MENU
    │
    ├→ SET_DIFFICULTY → MAIN_MENU
    ├→ HIGH_SCORE → MAIN_MENU
    ├→ INSTRUCTIONS → MAIN_MENU
    └→ EXIT_GAME
```

### Cross-Platform Design

The `console.h`/`console.cpp` module abstracts platform differences:

| Feature | Windows | Linux |
|---------|---------|-------|
| Terminal init | Win32 Console API | ncurses |
| Cursor control | `SetConsoleCursorPosition` | `move()` |
| Colors | `SetConsoleTextAttribute` | `attron(COLOR_PAIR())` |
| Input | `GetAsyncKeyState` | `getch()` with `nodelay()` |
| Clear screen | `system("cls")` | `clear()` |

## License

This project is provided as-is for educational purposes.
