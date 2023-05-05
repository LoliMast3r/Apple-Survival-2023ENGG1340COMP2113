# Welcome to our project!
**This is Group 77, ENGG1340-COMP2113(22-23 Sem 2)**

## Group Members
Yu Tin Yau  
Shen Wenqi  
Tsui Chit Hei  
Wong Kai Ching  
Wong Chun Wang  

## About Our Game
Our game is based on the classic snake game, where players control an apple instead of a snake to avoid being eaten.

## Controls
Players can move the apple using the WASD keys.

## Features
### Portals
The game includes portals that allow the apple to instantly teleport to other positions on the map. 
We've used arrays and dynamic memory management to ensure smooth gameplay.

### Highscores
The game saves scores after each game and displays a highscores list that can be accessed through the in-game menu. 
We've used file I/O and sorting algorithms to implement this feature.

### Random Events
Powerups and perks randomly appear in the game to assist the player.

## Non-standard C/C++ Libraries
***Important!***  
Our game uses the **ncurses** library for in-game content display.
**makefile failure** will happen if ncurses is not present in your operating system.  
Please install ncurses if you have not installed it in your operating system.  
> sudo apt-get install libncurses5-dev libncursesw5-dev

## Compilation
To start the game, simply type:
> make game  
> ./game

and the game will start.  

For cleaning game files, we offer three options:
1. Reset Highscores:
> make clearscores

2. Clean game files: *note that highscores will not reset.*
> make clean

3. Complete remove the game:
> make uninstall

# We hope that you will have fun playing our game! :smile:
