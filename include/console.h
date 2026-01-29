#ifndef CONSOLE_H
#define CONSOLE_H

// ============================================================================
// Cross-Platform Console Abstraction Layer
// ============================================================================
// This module provides a unified API for console/terminal operations
// that works on both Windows (using Win32 API) and Linux (using ncurses).

// Platform detection
#ifdef _WIN32
    #define PLATFORM_WINDOWS
#else
    #define PLATFORM_LINUX
#endif

// ============================================================================
// Initialization and Cleanup
// ============================================================================

// Initialize the console/terminal for game use
// Must be called before any other console functions
void initConsole();

// Restore the console/terminal to its original state
// Must be called before program exit
void cleanupConsole();

// ============================================================================
// Cursor and Screen Control
// ============================================================================

// Move cursor to position (x=column, y=row), 0-indexed
void gotoxy(int x, int y);

// Hide/show the cursor
void hideCursor();
void showCursor();

// Clear the entire screen
void clearScreen();

// Flush output to screen (required for ncurses)
void refreshScreen();

// Get terminal dimensions
int getScreenWidth();
int getScreenHeight();

// ============================================================================
// Color Control
// ============================================================================

// Set text color using game's color constants (0-15)
void setColor(unsigned short color);

// ============================================================================
// Output Functions
// ============================================================================

// Print a single character at current cursor position
void printChar(char c);

// Print a string at current cursor position
void printString(const char* s);

// Print a character at specific position with color
void printCharAt(int x, int y, char c, unsigned short color);

// Print a string at specific position with color
void printStringAt(int x, int y, const char* s, unsigned short color);

// Print an integer at current cursor position
void printInt(int value);

// ============================================================================
// Input Functions
// ============================================================================

// Non-blocking key read. Returns -1 if no key pressed.
int getKeyNonBlocking();

// Blocking key read. Waits for a key press.
int waitForKey();

// Read a string from user input (with echo)
// Reads up to maxLen-1 characters into buffer, null-terminates
void readString(char* buffer, int maxLen);

// ============================================================================
// Cross-Platform Key Constants
// ============================================================================

// Key codes that work on both platforms
extern const int KEY_ARROW_LEFT;
extern const int KEY_ARROW_RIGHT;
extern const int KEY_ARROW_UP;
extern const int KEY_ARROW_DOWN;
extern const int KEY_SPACEBAR;
extern const int KEY_ESCAPE_KEY;
extern const int KEY_ENTER_KEY;
extern const int KEY_NONE;  // Returned when no key is pressed

#endif // CONSOLE_H
