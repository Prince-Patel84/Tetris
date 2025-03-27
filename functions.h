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
void End(Grid *&g, Score *&s, Block *&t, Block *&nt);
void PlayAgain(Grid *&g, Score *&s, Block *&t, Block *&nt);
void Won(Grid *&g, Score *&s, Block *&t, Block *&nt);

Block *GenerateRandomTetromino(Grid *grid);
bool CheckCollision(Grid *grid, Block *tetromino, int newX, int newY);

// Function Definitions
Grid *Start()
{
    ClearScreen(true);
    GameStatus = true;

    cout << "                                          ==============================================================================" << endl;
    cout << "                                          = 0000000000000  0000000000  0000000000000  000 00000      0000   0 00000    =" << endl;
    cout << "                                          = 0000 000 0000  000   0000  0000 000 0000  000 0000000    0000  00  0000    =" << endl;
    cout << "                                          = 000  000  000  000    000  000  000  000  000 00000000   0000  000  000    =" << endl;
    cout << "                                          = 00   000   00  000     00  00   000   00  000 000000000  0000  0000  00    =" << endl;
    cout << "                                          = 0    000    0  000      0  0    000    0  000 00000000   0000  00000  0    =" << endl;
    cout << "                                          =      000       000   0          000       000 0000000    0000   00000      =" << endl;
    cout << "                                          =      000       000 000          000       000 00000      0000    00000     =" << endl;
    cout << "                                          =      000       0000000          000       000 0          0000     00000    =" << endl;
    cout << "                                          =      000       000 000          000       000 00         0000      00000   =" << endl;
    cout << "                                          =      000       000   0          000       000 000        0000       00000  =" << endl;
    cout << "                                          =      000       000      0       000       000  000       0000     0  00000 =" << endl;
    cout << "                                          =      000       000     00       000       000   000      0000     00  0000 =" << endl;
    cout << "                                          =      000       000    000       000       000    000     0000     000  000 =" << endl;
    cout << "                                          =      000       000   0000       000       000     000    0000     0000  00 =" << endl;
    cout << "                                          =      000       0000000000       000       000      0000  0000     00000 0  =" << endl;
    cout << "                                          ==========================                           =========================" << endl;
    cout << "                                                                   =                           =                        " << endl;
    cout << "                                                                   =         [PLAY]            =                        " << endl;
    cout << "                                                                   =                           =                        " << endl;
    cout << "                                                                   =   - Press P to Play       =                        " << endl;
    cout << "                                                                   =                           =                        " << endl;
    cout << "                                                                   =         Enjoy !!          =                        " << endl;
    cout << "                                                                   =                           =                        " << endl;
    cout << "                                                                   =   - Press X to Exit       =                        " << endl;
    cout << "                                                                   =                           =                        " << endl;
    cout << "                                                                   =                           =                        " << endl;
    cout << "                                                                   =        - By Binary Minds  =                        " << endl;
    cout << "                                                                   =============================                        " << endl;

    while (true)
    {
        char c = _getch();
        if (c == 'p' || c == 'P')
        {
            break;
        }
        else if (c == 'x' || c == 'X')
        {
            Game = false;
            break;
        }
    }

    return new Grid();
}

void UserInput(Grid *grid, Block *tetromino, Score *&s)
{
    if (_kbhit())
    {
        char key = _getch();

#ifdef _WIN32
        // Windows arrow keys detection
        if (key == -32)  // Arrow keys return -32 followed by another character in Windows
        {
            char arrowKey = _getch();
            switch (arrowKey)
            {
            case 72:  // Up arrow key
                tetromino->rotate();
                if (CheckCollision(grid, tetromino, tetromino->posX, tetromino->posY))
                {
                    tetromino->rotateBack();
                }
                break;
            case 80:  // Down arrow key
                if (!CheckCollision(grid, tetromino, tetromino->posX, tetromino->posY + 1))
                {
                    tetromino->posY += 1;
                    s->softDropBonus(1);
                }
                break;
            case 77:  // Right arrow key
                if (!CheckCollision(grid, tetromino, tetromino->posX + 1, tetromino->posY))
                    tetromino->posX += 1;
                break;
            case 75:  // Left arrow key
                if (!CheckCollision(grid, tetromino, tetromino->posX - 1, tetromino->posY))
                    tetromino->posX -= 1;
                break;
            }
        }
#else
        // Linux arrow keys detection
        if (key == '\033') // Escape character in Linux
        {
            if (_kbhit() && _getch() == '[')
            {
                char arrowKey = _getch();
                switch (arrowKey)
                {
                case 'A':
                    tetromino->rotate();
                    if (CheckCollision(grid, tetromino, tetromino->posX, tetromino->posY))
                    {
                        tetromino->rotateBack();
                    }
                    break;
                case 'B':
                    if (!CheckCollision(grid, tetromino, tetromino->posX, tetromino->posY + 1))
                    {
                        tetromino->posY += 1;
                        s->softDropBonus(1);
                    }
                    break;
                case 'C':
                    if (!CheckCollision(grid, tetromino, tetromino->posX + 1, tetromino->posY))
                        tetromino->posX += 1;
                    break;
                case 'D':
                    if (!CheckCollision(grid, tetromino, tetromino->posX - 1, tetromino->posY))
                        tetromino->posX -= 1;
                    break;
                }
            }
        }
#endif
        else
        {
            switch (key)
            {
            case ' ':
            {
                int oldPosY = tetromino->posY;
                while (!CheckCollision(grid, tetromino, tetromino->posX, tetromino->posY + 1))
                    tetromino->posY += 1;
                s->hardDropBonus(tetromino->posY - oldPosY);
            }
            break;
            case 27:
                GameStatus = false;
                break;
            }
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

    if (score->getScore() > 9999)
    {
        GameWon = true;
        GameStatus = false;
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

    // Grid Printing
    cout << "                                               ----------===========================================----------  " << endl;
    cout << "                                               |         0000000 000000 0000000 0000  0000000  00000         |  " << endl;
    cout << "                                               |            0    0         0    0   0    0    0              |  " << endl;
    cout << "                                               |            0    0000      0    0000     0     00000         |  " << endl;
    cout << "                                               |            0    0         0    0  0     0          0        |  " << endl;
    cout << "                                               |            0    000000    0    0   0 0000000  00000         |  " << endl;
    cout << "                                               |                                                             |  " << endl;
    cout << "                                               |              ";
    for (int i = 0; i < HEIGHT + 2; i++)
    {
        for (int j = 0; j < WIDTH + 2 + 5 + 1; j++)
        {
            if (i == 1 && j == WIDTH + 2)
            {
                cout << "Next :";
                j = WIDTH + 4;
            }
            else if (i == 10 && j == WIDTH + 3)
            {
                cout << "Score:";
                j = WIDTH + 5;
            }
            else if (i == 12 && j == WIDTH + 3)
            {
                cout << s->getScore();
                if (s->getScore() < 10)
                    cout << ' ';

                else if (s->getScore() >= 1000)
                    j = WIDTH + 4;

                else if (s->getScore() >= 100)
                {
                    cout << ' ';
                    j = WIDTH + 4;
                }
            }
            else if (i == 19 && j == WIDTH + 2)
            {
                cout << "@Level:" << s->getLevel();

                if (s->getLevel() >= 10)
                {
                    j = WIDTH + 6;
                    cout << ' ';
                }
                else
                    j = WIDTH + 5;
            }
            else if (i == 0 || j == 0 || j == WIDTH + 1 || i == HEIGHT + 1 || j == WIDTH + 2 + 5 || (i == 8 && j > WIDTH + 1) || (i == 17 && j > WIDTH + 1))
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
        cout << "           |              \n                                               |              ";
    }
    cout << "                                               |              \n                                               ----------===========================================----------" << endl;
    SleepFunction(Speed);
}

void End(Grid *&g, Score *&s, Block *&t, Block *&nt)
{
    cout << "                                                                                                                                                  " << endl;
    cout << "                                                                                                                                                  " << endl;
    cout << "                       00000000000   00        000             000        000000000        00000000000  000               000  000000000  00000000" << endl;
    cout << "                     000000000000   0000       0000           0000       000000000        0000000000000  0000           0000  000000000  0000000000" << endl;
    cout << "                   0000                                                                                                                         000" << endl;
    cout << "                 00000   0000000  00000000     0000           0000     000000000         000         000   0000       0000  000000000  0000000000" << endl;
    cout << "                00000   0000000  0000000000    000000       000000    000000000          000         000    0000     0000  000000000  00000000" << endl;
    cout << "                 00000     000  0000    0000   0000  00   00  0000   000                 000         000     0000   0000  000        0000   000" << endl;
    cout << "                   0000   000  0000      0000  0000   00 00   0000  000000000             0000000000000       0000 0000  000000000  0000     000" << endl;
    cout << "                     0000000  0000        0000 0000    000    0000 000000000               0000000000          0000000  000000000  0000       000" << endl;
    cout << "                        000 _________________________________________________________________________________________________________________  000" << endl;
    cout << "                       000 /         L L L I I I                                                                                     T J J J \\ 000" << endl;
    cout << "                      000 /          L CONTINUE J -Press P to Continue Playing..                                  Press X to Exit - T EXIT J  \\ 000" << endl;
    cout << "                     000 /           I I I J J J                                                                                     T I L L   \\ 000" << endl;
    cout << "                    000 /________________I-I___________________________________________________________________________________________I-I______\\ 000" << endl;

    while (true)
    {
        char c = _getch();
        if (c == 'p' || c == 'P')
        {
            PlayAgain(g, s, t, nt);
            break;
        }
        else if (c == 'x' || c == 'X')
            break;
    }
}

void PlayAgain(Grid *&g, Score *&s, Block *&t, Block *&nt)
{
    g->resetGrid();
    s->resetScore();
    delete t;
    delete nt;
    GameStatus = true;
    GameWon = false;
    t = GenerateRandomTetromino(g);
    nt = GenerateRandomTetromino(g);

    while (GameStatus)
    {
        UserInput(g, t, s);
        Gamelogic(g, t, nt, s);
        Draw(g, t, nt, s);
    }

    if (!GameWon)
        End(g, s, t, nt);
    else
        Won(g, s, t, nt);
}

void Won(Grid *&g, Score *&s, Block *&t, Block *&nt)
{
    cout << "                       0000000000000    0000     0000    000000000        000   " << endl;
    cout << "                      000000000000000   00000   00000   0000000000       00000  " << endl;
    cout << "                     000           000  000000 000000  000               00000  " << endl;
    cout << "                     000           000  000 00000 000  000               00000  " << endl;
    cout << "                     000           000  000  000  000  000       0000     000   " << endl;
    cout << "                     000           000  000       000  000       0000           " << endl;
    cout << "                      000000000000000   000       000   0000000000        000   " << endl;
    cout << "                       0000000000000    000       000    00000000        00000  " << endl;
    cout << "                  ----------===========================================----------" << endl;
    cout << endl;
    cout << "                                     0     0                  0                    0           0000000 0               0000000                             " << endl;
    cout << "                                      0   0                   0                    0              0    0              0       0                            " << endl;
    cout << "                                       0 0                    0                    0  0           0    0              0                                    " << endl;
    cout << "                                        0   00000  0    0     000000   0    00000  0 0   000      0    00000   000    0          000   0        000        " << endl;
    cout << "                                        0  0     0 0    0     0     0  0 0 0     0 00   00000     0    0    0 00000   0     000 0   0  000 00  00000       " << endl;
    cout << "                                        0  0     0 0    0     0     0  0   0     0 0 0  0         0    0    0 0       0     00   0000  0  0  0 0           " << endl;
    cout << "                                        0   00000   0000      000000   0    00000  0  0  0000     0    0    0  0000    000000 0     00 0  0  0  0000  0 0 0" << endl;
    cout << "                                  ------------=====================-----------------========================------------------======================----------" << endl;
    cout << endl;
    cout << "            000 _________________________________________________________________________________________________________________ 000" << endl;
    cout << "           000 /         L L L I I I                                                                                     T J J J \\ 000" << endl;
    cout << "          000 /          L CONTINUE J -Press P to Continue Playing..                                  Press X to Exit - T EXIT J  \\ 000" << endl;
    cout << "         000 /           I I I J J J                                                                                     T I L L   \\ 000" << endl;
    cout << "        000 /________________I-I___________________________________________________________________________________________I-I______\\ 000" << endl;
    while (true)
    {
        char c = _getch();
        if (c == 'p' || c == 'P')
        {
            PlayAgain(g, s, t, nt);
            break;
        }
        else if (c == 'x' || c == 'X')
            break;
    }
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