#pragma once
#include "settings.h"

class Block
{
public:
    int block[4][4];
    int prevBlock[4][4];
    int posX, posY;
    char name;

    Block()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                block[i][j] = 0;
        posX = WIDTH / 2 - 1;
        posY = 0;
    }

    void rotate()
    {
        saveState();
        int temp[4][4];

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                temp[j][i] = block[i][j];

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                block[i][j] = temp[i][3 - j];
    }

    void rotateBack()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                block[i][j] = prevBlock[i][j];
    }

private:
    void saveState()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                prevBlock[i][j] = block[i][j];
    }
};

class TetrominoI : public Block
{
public:
    TetrominoI() : Block()
    {
        name = 'I';
        block[0][1] = block[1][1] = block[2][1] = block[3][1] = 1;
    }
};

class TetrominoO : public Block
{
public:
    TetrominoO() : Block()
    {
        name = 'O';
        block[1][1] = block[1][2] = block[2][1] = block[2][2] = 2;
    }
};

class TetrominoT : public Block
{
public:
    TetrominoT() : Block()
    {
        name = 'T';
        block[1][0] = block[1][1] = block[1][2] = block[2][1] = 3;
    }
};

class TetrominoL : public Block
{
public:
    TetrominoL() : Block()
    {
        name = 'L';
        block[0][2] = block[1][2] = block[2][2] = block[2][1] = 4;
    }
};

class TetrominoJ : public Block
{
public:
    TetrominoJ() : Block()
    {
        name = 'J';
        block[0][1] = block[1][1] = block[2][1] = block[2][2] = 5;
    }
};

class TetrominoS : public Block
{
public:
    TetrominoS() : Block()
    {
        name = 'S';
        block[1][1] = block[1][2] = block[2][0] = block[2][1] = 6;
    }
};

class TetrominoZ : public Block
{
public:
    TetrominoZ() : Block()
    {
        name = 'Z';
        block[1][0] = block[1][1] = block[2][1] = block[2][2] = 7;
    }
};