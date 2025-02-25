#pragma once

class Grid {
    public:
    int grid[HEIGHT][WIDTH];
    
    Grid() {
        for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        grid[i][j] = 0;
    }
};