#include "settings.h"
#include "tetromino.h"
#include "grid.h"
#include "functions.h"

int main()
{
    Grid *grid = Start();
    Block *Tetromino = GenerateRandomTetromino(grid);
    Block *nextTetromino = GenerateRandomTetromino(grid);

    while (GameStatus)
    {
        UserInput(grid, Tetromino);
        Gamelogic(grid, Tetromino, nextTetromino);
        Draw(grid, Tetromino, nextTetromino);
    }

    // End();
    return 0;
}
