#pragma once
const int HEIGHT = 20;
const int WIDTH = 10;
bool GameStatus = false;
bool GameWon = false;
bool Game = true;
int Speed = 350;

const char TS[] = {' ', 'I', 'O', 'T', 'L', 'J', 'S', 'Z'}; // Symbols for Tetromino

// Scoring
const int SINGLE = 100;
const int DOUBLE = 300;
const int TRIPLE = 500;
const int TETRIS = 800;
const int SOFT_DROP_POINTS = 1;
const int HARD_DROP_POINTS = 2;