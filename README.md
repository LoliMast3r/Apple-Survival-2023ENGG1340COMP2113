# Apple Rush: The Classic Snake Game with a Twist
**Are you tired of playing the same old snake game? 
Then try Apple Rush, the game where you play as the apple trying to avoid being eaten by the snake!**

## Meet the Team
We are Group 77, a team of five students from ENGG1340-COMP2113(22-23 Sem 2):
+ Yu Tin Yau  
+ Shen Wenqi  
+ Tsui Chit Hei  
+ Wong Kai Ching  
+ Wong Chun Wang  

Together, we've taken the classic snake game and given it a fresh twist, creating a game that is both nostalgic and exciting.

## How To Play
Play as the apple and use the WASD keys to move around the screen. 
Avoid the snake's head and body as you collect apples and try to stay alive as long as possible.

## Exiciting Features
### Portals
Use portals to instantly teleport to other positions on the map, making gameplay more dynamic and strategic.
We've used arrays and dynamic memory management to ensure smooth gameplay.

### Highscores
Keep track of your scores and compete with others on the highscores list.
We've used file I/O and sorting algorithms to implement this feature.

### Random Events
Powerups and perks randomly appear in the game, giving you an extra boost to help you stay alive longer. 
You never know what you might get!

## Non-standard C/C++ Libraries
***Important!***  
Our game uses the **ncurses** library for in-game content display.
**makefile failure** will happen if ncurses is not present in your operating system.  
If you don't have ncurses installed on your operating system, don't worry!
You can easily install it by running the following command:
> sudo apt-get install libncurses5-dev libncursesw5-dev

## Getting Started
To start playing Apple Rush, simply type the following commands into your terminal:
> make game  
> ./game

If you want to clean up your game files, we offer three options:
1. Reset Highscores:
> make clearscores

2. Clean game files: *note that highscores will not reset.*
> make clean

3. Complete remove the game:
> make uninstall

#Join the Fun!
Apple Rush is a fun and exciting game that is sure to keep you entertained for hours. 
So why not give it a try? :smile:
