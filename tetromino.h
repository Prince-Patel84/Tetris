#pragma once
#include "settings.h"

class Block
{
public:
    int block[4][4];
    int prevBlock[4][4];
    int posX, posY;

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
        block[0][1] = block[1][1] = block[2][1] = block[3][1] = 1;
    }
};

class TetrominoO : public Block
{
public:
    TetrominoO() : Block()
    {
        block[1][1] = block[1][2] = block[2][1] = block[2][2] = 1;
    }
};

class TetrominoT : public Block
{
public:
    TetrominoT() : Block()
    {
        block[1][0] = block[1][1] = block[1][2] = block[2][1] = 1;
    }
};

class TetrominoL : public Block
{
public:
    TetrominoL() : Block()
    {
        block[0][2] = block[1][2] = block[2][2] = block[2][1] = 1;
    }
};

class TetrominoJ : public Block
{
public:
    TetrominoJ() : Block()
    {
        block[0][1] = block[1][1] = block[2][1] = block[2][2] = 1;
    }
};

class TetrominoS : public Block
{
public:
    TetrominoS() : Block()
    {
        block[1][1] = block[1][2] = block[2][0] = block[2][1] = 1;
    }
};

class TetrominoZ : public Block
{
public:
    TetrominoZ() : Block()
    {
        block[1][0] = block[1][1] = block[2][1] = block[2][2] = 1;
    }
};