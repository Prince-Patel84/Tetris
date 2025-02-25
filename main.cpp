#include "settings.h"
#include "tetromino.h"
#include "grid.h"
#include "functions.h"

int main() {
    Grid* grid = Start();
    Block* cTetromino = GenerateRandomTetromino();

    while (GameStatus) {
        UserInput(grid,cTetromino);
        Gamelogic(grid, cTetromino);
        Draw(grid, cTetromino);
    }

    // End();
    return 0;
}
