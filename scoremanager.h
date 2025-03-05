#pragma once
#include "settings.h"

class Score
{
private:
    int score = 0;
    int level = 0;
    int linesCleared = 0;

public:
    void addScore(int lines, bool tSpin = false)
    {
        int baseScore = 0;

        if (tSpin)
        {
            baseScore = (lines == 1) ? 800 : (lines == 2) ? 1200
                                                          : 1600;
        }
        else
        {
            switch (lines)
            {
            case 1:
                baseScore = SINGLE;
                break;
            case 2:
                baseScore = DOUBLE;
                break;
            case 3:
                baseScore = TRIPLE;
                break;
            case 4:
                baseScore = TETRIS;
                break;
            default:
                return;
            }
        }

        score += baseScore * (level + 1);
        linesCleared += lines;

        if (linesCleared >= 10)
        {
            levelUp();
        }
    }

    void softDropBonus(int rows)
    {
        score += rows * SOFT_DROP_POINTS;
    }

    void hardDropBonus(int rows)
    {
        score += rows * HARD_DROP_POINTS;
    }

    void levelUp()
    {
        level++;
        linesCleared = 0; // Reset lines cleared for next level
        Speed -= level * 10;
    }

    int getScore() { return score; }
    int getLevel() { return level; }
};