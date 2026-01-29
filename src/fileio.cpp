#include "../include/fileio.h"
#include "../include/globals.h"
#include "../include/constants.h"
#include "../include/console.h"
#include "../include/game.h"
#include <fstream>
#include <string>
#include <cstdlib>

using std::fstream;
using std::ios;
using std::string;
using std::getline;

// ============================================================================
// File I/O Implementation
// ============================================================================

void storeData()
{
    // First line contains difficulty, next 5 lines contain high scores
    fstream f;
    f.open("gameData.txt", ios::out);
    if (f.fail())
    {
        // Silently fail if unable to save - game can continue without saving
        return;
    }
    f << difficulty << std::endl;
    for (int i = 0; i < 5; i++)
    {
        f << highScore[i];
        if (i != 4)
        {
            f << std::endl;
        }
    }
    f.close();
}

bool readData()
{
    fstream f;
    f.open("gameData.txt", ios::in);
    if (f.fail())
    {
        return false;
    }
    string temp;
    getline(f, temp);
    difficulty = strToInt(temp.c_str());
    for (int i = 0; i < 5; i++)
    {
        getline(f, temp);
        highScore[i] = strToInt(temp.c_str());
    }
    f.close();
    return true;
}

void loadBoard()
{
    fstream f;
    f.open("board.txt", ios::in);
    if (f.fail())
    {
        setColor(red);
        printString("Board.txt was not found..........Exiting the game.");
        setColor(white);
        refreshScreen();
        cleanupConsole();
        exit(1);
    }
    string line;
    int row = 0;
    while (getline(f, line))
    {
        for (size_t i = 0; i < line.length(); i++)
        {
            board[row][i] = line[i];
        }
        row++;
    }
    f.close();
}
