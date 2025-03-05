#include "game.h"

int main()
{
    Grid *grid = Start();
    Block *Tetromino = GenerateRandomTetromino(grid);
    Block *nextTetromino = GenerateRandomTetromino(grid);
    Score *score = new Score();

    while (GameStatus)
    {
        UserInput(grid, Tetromino, score);
        Gamelogic(grid, Tetromino, nextTetromino, score);
        Draw(grid, Tetromino, nextTetromino, score);
    }

    // End();
    return 0;
}
