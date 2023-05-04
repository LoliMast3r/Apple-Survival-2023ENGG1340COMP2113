# Welcome to our project!
**This is Group 77, ENGG1340-COMP2113(22-23 Sem 2)**

## Group Members
Yu Tin Yau  
Shen Wenqi  
Tsui Chit Hei  
Wong Kai Ching  
Wong Chun Wang  

## About Our Game
Our game is based on the classic snake game.  
Instead of being the snake, you will be the apple who have to avoid being eaten by the snake.

## Features
### Portals
In our game, there are portals which the Apple can interact with to instantly teleport to other positions on the map.  
The portals have utilised arrays and dynamic memory management to ensure in-game smoothness.

### Highscores
Highscores are avalible in this game as a .txt file.  
Scores are saved after each game and highscores can be sccessed through the highscores tab in-game.  
File IO and sorting are used in this feature.

### Random Events
In the game, powerups and perks will appear to assist the player.    
Random functions are used in this feature.  

## Non-standard C/C++ Libraries
***Important!***  
**ncurses** is used in this game for in-game content display.  
**makefile failure** will happen if ncurses is not present in your operating system.  
Please install ncurses if you have not installed it in your operating system.  
> sudo apt-get install libncurses5-dev libncursesw5-dev

## Compilation
To start the game, simply type:
> make game  
> ./game

and the game will start.  

For cleaning game files, there are three options:
1. Reset Highscores:
> make clearscores

2. Clean game files: *note that highscores will not reset.*
> make clean

3. Complete removal:
> make uninstall

# We hope that you will have fun playing our game! :smile: