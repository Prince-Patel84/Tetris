#pragma once
#include "tetromino.h"
#include "grid.h"
#include <cstdlib>
#include <ctime>
#include "winlix.h"
#include "scoremanager.h"
#include <iostream>
using namespace std;

// Function Declaration
Grid *Start();
void UserInput(Grid *grid, Block *tetromino, Score *&s);
void Gamelogic(Grid *grid, Block *&tetromino, Block *&newtetromino, Score *&score);
void Draw(Grid *grid, Block *T, Block *NT, Score *&s);
void End();

Block *GenerateRandomTetromino(Grid *grid);
bool CheckCollision(Grid *grid, Block *tetromino, int newX, int newY);

// Function Definitions
Grid *Start()
{
    GameStatus = true;
    return new Grid();
}

void UserInput(Grid *grid, Block *tetromino, Score *&s)
{
    if (_kbhit())
    {
        char key = _getch();

        switch (key)
        {
        case 'a':
            if (!CheckCollision(grid, tetromino, tetromino->posX - 1, tetromino->posY))
                tetromino->posX -= 1;
            break;
        case 'd':
            if (!CheckCollision(grid, tetromino, tetromino->posX + 1, tetromino->posY))
                tetromino->posX += 1;
            break;
        case 's':
            if (!CheckCollision(grid, tetromino, tetromino->posX, tetromino->posY + 1))
            {
                tetromino->posY += 1;
                s->softDropBonus(1);
            }
            break;
        case ' ':
        {
            int oldPosY = tetromino->posY;
            while (!CheckCollision(grid, tetromino, tetromino->posX, tetromino->posY + 1))
                tetromino->posY += 1;
            s->hardDropBonus(tetromino->posY - oldPosY);
        }
        break;
        case 'w':
            tetromino->rotate();
            if (CheckCollision(grid, tetromino, tetromino->posX, tetromino->posY))
            {
                tetromino->rotateBack();
            }
            break;
        case 'x':
            GameStatus = false;
            break;
        }
    }
}

void Gamelogic(Grid *grid, Block *&tetromino, Block *&newtetromino, Score *&score)
{
    int rC = 0;
    for (int i = HEIGHT - 1; i >= 0; i--)
    {
        bool isFullRow = true;
        for (int j = WIDTH - 1; j >= 0; j--)
        {
            if (!grid->grid[i][j])
            {
                isFullRow = false;
                break;
            }
        }
        if (isFullRow)
        {

            for (int p = i; p > 0; p--)
                for (int j = WIDTH - 1; j >= 0; j--)
                {
                    grid->grid[p][j] = grid->grid[p - 1][j];
                }

            for (int j = WIDTH - 1; j >= 0; j--)
            {
                grid->grid[0][j] = 0;
            }
            rC++;
            i++;
        }
    }

    if (tetromino->name == 'T' && rC)
        score->addScore(rC, true);
    else if (rC)
        score->addScore(rC);

    if (!CheckCollision(grid, tetromino, tetromino->posX, tetromino->posY + 1))
        tetromino->posY += 1;
    else
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (tetromino->block[i][j] > 0)
                {
                    int x = tetromino->posX + j;
                    int y = tetromino->posY + i;
                    if (y >= 0)
                        grid->grid[y][x] = tetromino->block[i][j];
                }
            }
        }

        delete tetromino;
        tetromino = newtetromino;
        newtetromino = GenerateRandomTetromino(grid);
    }
}

void Draw(Grid *grid, Block *T, Block *NT, Score *&s)
{
    ClearScreen(true);

    int tempGrid[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            tempGrid[i][j] = grid->grid[i][j];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (T->block[i][j] > 0)
            {
                int x = T->posX + j;
                int y = T->posY + i;
                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
                {
                    tempGrid[y][x] = T->block[i][j];
                }
            }
        }
    }

    for (int i = 0; i < HEIGHT + 2; i++)
    {
        for (int j = 0; j < WIDTH + 2 + 5 + 1; j++)
        {
            if (i == 1 && j == WIDTH + 2)
            {
                cout << "Next :";
                j = WIDTH + 4;
            }
            else if (i == 0 || j == 0 || j == WIDTH + 1 || i == HEIGHT + 1 || j == WIDTH + 2 + 5)
                cout << "# ";
            else if ((tempGrid[i - 1][j - 1] > 0) && (j < WIDTH + 2))
                cout << TS[tempGrid[i - 1][j - 1]] << ' ';
            else if ((i > 2) && (i < 7) && (j > WIDTH + 2) && (NT->block[i - 3][j - WIDTH - 3] > 0))
            {
                cout << TS[NT->block[i - 3][j - WIDTH - 3]] << ' ';
            }
            else
                cout << "  ";
        }

        cout << endl;
    }
    cout << "Score: " << s->getScore() << "  Level: " << s->getLevel() << endl;

    SleepFunction(Speed);
}

Block *GenerateRandomTetromino(Grid *grid)
{
    srand(time(0));
    int randomNum = rand() % 7;

    switch (randomNum)
    {
    case 0:
    {
        Block *NewTetromino = new TetrominoI();
        if (CheckCollision(grid, NewTetromino, NewTetromino->posX, NewTetromino->posY))
            GameStatus = false;
        return NewTetromino;
    }
    break;
    case 1:
    {
        Block *NewTetromino = new TetrominoO();
        if (CheckCollision(grid, NewTetromino, NewTetromino->posX, NewTetromino->posY))
            GameStatus = false;
        NewTetromino->posY = -1;
        return NewTetromino;
    }
    break;
    case 2:
    {
        Block *NewTetromino = new TetrominoT();
        if (CheckCollision(grid, NewTetromino, NewTetromino->posX, NewTetromino->posY))
            GameStatus = false;
        NewTetromino->posY = -1;
        return NewTetromino;
    }
    break;
    case 3:
    {
        Block *NewTetromino = new TetrominoL();
        if (CheckCollision(grid, NewTetromino, NewTetromino->posX, NewTetromino->posY))
            GameStatus = false;
        return NewTetromino;
    }
    break;
    case 4:
    {
        Block *NewTetromino = new TetrominoJ();
        if (CheckCollision(grid, NewTetromino, NewTetromino->posX, NewTetromino->posY))
            GameStatus = false;
        return NewTetromino;
    }
    break;
    case 5:
    {
        Block *NewTetromino = new TetrominoS();
        if (CheckCollision(grid, NewTetromino, NewTetromino->posX, NewTetromino->posY))
            GameStatus = false;
        NewTetromino->posY = -1;
        return NewTetromino;
    }
    break;
    case 6:
    {
        Block *NewTetromino = new TetrominoZ();
        if (CheckCollision(grid, NewTetromino, NewTetromino->posX, NewTetromino->posY))
            GameStatus = false;
        NewTetromino->posY = -1;
        return NewTetromino;
    }
    break;
    }
    return new TetrominoI();
}

bool CheckCollision(Grid *grid, Block *tetromino, int newX, int newY)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {

            if (tetromino->block[i][j] > 0)
            {
                int x = newX + j;
                int y = newY + i;

                if (x < 0 || x >= WIDTH)
                    return true;

                if (y >= HEIGHT)
                    return true;

                if (y >= 0 && grid->grid[y][x] > 0)
                    return true;
            }
        }
    }
    return false;
}
