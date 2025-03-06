#include "game.h"

int main()
{
    Grid *grid = Start();
    Block *Tetromino = GenerateRandomTetromino(grid);
    Block *nextTetromino = GenerateRandomTetromino(grid);
    Score *score = new Score();
    if (Game)
    {
        while (GameStatus)
        {
            UserInput(grid, Tetromino, score);
            Gamelogic(grid, Tetromino, nextTetromino, score);
            Draw(grid, Tetromino, nextTetromino, score);
        }

        End(grid, score, Tetromino, nextTetromino);
    }
    return 0;
}
