# 🎮 Tetris Game in C++

## 👥 Team: Binary Minds
This game was developed by **Binary Minds** as part of our C++ project.

## 🕹 About the Game
This is a **Terminal-based Tetris game** implemented in **C++**. The game follows classic Tetris mechanics, where tetrominoes fall onto a 10x20 grid. Players can move, rotate, and drop pieces to complete lines and score points. The game increases in difficulty as more lines are cleared. Reach **9999 points** to win!

## ✨ Features
✅ **Seven Tetrominoes** - (I, O, T, S, Z, J, L) are implemented.  
✅ **10x20 Grid** - Standard Tetris board size.  
✅ **Piece Movement** - Move left, right, rotate, and drop pieces.  
✅ **Gravity & Speed Increase** - Pieces fall at increasing speeds as levels progress.  
✅ **Collision Detection** - Prevents illegal movements.  
✅ **Line Clearing** - Removes full rows and shifts the board down.  
✅ **Scoring System** - Earn points for clearing lines and hard drops.  
✅ **Level System** - Game speed increases as you progress.  
✅ **Win Condition** - Score **9999 points** to win!  
✅ **Game Over** - The game ends if pieces reach the top.  

## 🎛 Controls
- **⬅ Left Arrow** - Move left  
- **➡ Right Arrow** - Move right  
- **⬆ Up Arrow** - Rotate piece  
- **⬇ Down Arrow** - Soft drop  
- **⏹ Spacebar** - Hard drop  
- **⏏ Escape (ESC)** - Pause/Quit the game  

## 🛠 Installation & Compilation
### **Linux**
```sh
g++ -o tetris tetris.cpp
./tetris
```
### **Windows (MinGW)**
```sh
g++ -o tetris.exe tetris.cpp
tetris.exe
```

## 📂 Files Overview
- **tetris.cpp** → Main game logic  
- **game.h** → Handles game mechanics and controls  
- **score.txt** → Stores high scores  

## 🚀 Future Improvements
🔹 Add a graphical interface  
🔹 Multiplayer mode  
🔹 Customizable themes & controls  

## 🏆 Conclusion
Tetris is a timeless classic, and this implementation brings the iconic gameplay to the terminal with smooth mechanics, progressive difficulty, and a rewarding scoring system. Whether you're playing for fun or aiming to beat the **9999-point challenge**, we hope you enjoy the experience!

Thank you for playing! 🎮

---

## 👥 Team Members
| Name                     | Student ID |
| ------------------------ | ---------- |
| Prince Patel             | 202401151  |
| Vishwa Prajapati         | 202401163  |
| Dhruv Patel              | 202401142  |

