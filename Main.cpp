#include <iostream>
#include "winlix.h"

using namespace std;

const int HEIGHT = 20;
const int WIDTH = 10;
bool GameStatus = false;

void Gamelogic();
void End();

class Block {
public:
    int block[4][4];
    int posX, posY; 

    Block() {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                block[i][j] = 0;
        posX = WIDTH / 2 - 1; 
        posY = 0;  
    }
};

class TetrominoI : public Block {
public:
    TetrominoI() : Block() {
        block[0][1] = block[1][1] = block[2][1] = block[3][1] = 1;
    }
};

class Grid {
public:
    int grid[HEIGHT][WIDTH];

    Grid() {
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                grid[i][j] = 0;
    }
};

Grid* Start();
void Draw(Grid* grid, TetrominoI* T);

int main() {
    Grid* grid = Start();
    TetrominoI* I = new TetrominoI();

    while (GameStatus) {
        Draw(grid, I);
        // Gamelogic();
    }

    return 0;
}

Grid* Start() {
    GameStatus = true;
    return new Grid();
}

void Draw(Grid* grid, TetrominoI* T) {
    ClearScreen(true);

    int tempGrid[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            tempGrid[i][j] = grid->grid[i][j];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (T->block[i][j] == 1) { 
                int x = T->posX + j;  
                int y = T->posY + i;  
                if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
                    tempGrid[y][x] = 1;
                }
            }
        }
    }

    for (int i = 0; i < HEIGHT + 2; i++) {
        for (int j = 0; j < WIDTH + 2; j++) {
            if (i == 0 || j == 0 || j == WIDTH + 1 || i == HEIGHT + 1)
                cout << "# ";
            else if (tempGrid[i - 1][j - 1] == 1)
                cout << "& ";
            else
                cout << "  ";
        }
        cout << endl;
    }

    SleepFunction(150);
}
