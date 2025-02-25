#include <iostream>
#include <cstdlib>
#include <ctime>

#include "winlix.h"
#include "settings.h"
#include "tetromino.h"

using namespace std;

class Grid {
    public:
    int grid[HEIGHT][WIDTH];
    
    Grid() {
        for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        grid[i][j] = 0;
    }
};

//Function Decleration
Grid* Start();
void Draw(Grid* grid, Block* T);
void UserInput(Grid* grid,Block* tetromino);
void Gamelogic(Grid* grid, Block*& tetromino);
void End();

Block* GenerateRandomTetromino();
bool CheckCollision(Grid* grid, Block* tetromino, int newX, int newY);

int main() {
    Grid* grid = Start();
    Block* cTetromino = GenerateRandomTetromino();

    while (GameStatus) {
        UserInput(grid,cTetromino);
        Gamelogic(grid, cTetromino);
        Draw(grid, cTetromino);
    }

    return 0;
}

Grid* Start() {
    GameStatus = true;
    return new Grid();
}

void Draw(Grid* grid, Block* T) {
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

    SleepFunction(200);
}

void UserInput(Grid* grid,Block* tetromino) {
    if (_kbhit()) {  
        char key = _getch(); 

        switch (key) {
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
                    tetromino->posY += 1;
                break;
            case ' ': 
                while(!CheckCollision(grid, tetromino, tetromino->posX, tetromino->posY + 1))
                    tetromino->posY += 1;
                break;
            case 'w': 
                tetromino->rotate();
                if (tetromino->posX < 0) tetromino->posX = 0; 
                if (tetromino->posX + 4 > WIDTH) tetromino->posX = WIDTH - 4; 
                if (tetromino->posY + 4 > HEIGHT) tetromino->posY = HEIGHT - 4; 
                break;
            case 'x': 
                GameStatus = false;
                break;
        }
    }
}

Block* GenerateRandomTetromino() {
srand(time(0));
int randomNum = rand() % 7;

    switch (randomNum) {
        case 0: return new TetrominoI();
        case 1: return new TetrominoO();
        case 2: return new TetrominoT();
        case 3: return new TetrominoL();
        case 4: return new TetrominoJ();
        case 5: return new TetrominoS();
        case 6: return new TetrominoZ();
    }
    return new TetrominoI();
}

bool CheckCollision(Grid* grid, Block* tetromino, int newX, int newY) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetromino->block[i][j] == 1) {  
                int x = newX + j;
                int y = newY + i;

                if (x < 0 || x >= WIDTH)  
                    return true;

                if (y >= HEIGHT)  
                    return true;

                if (y >= 0 && grid->grid[y][x] == 1)  
                    return true;
            }
        }
    }
    return false;
}



void Gamelogic(Grid* grid, Block*& tetromino) {
    if (!CheckCollision(grid, tetromino, tetromino->posX, tetromino->posY + 1)) {
        tetromino->posY += 1;
    } else {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tetromino->block[i][j] == 1) {
                    int x = tetromino->posX + j;
                    int y = tetromino->posY + i;
                    if (y >= 0) grid->grid[y][x] = 1;
                }
            }
        }
        
        delete tetromino;
        tetromino = GenerateRandomTetromino();
    }
}
