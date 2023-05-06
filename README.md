# Apple Survival: The Classic Snake Game with a Twist
**Are you tired of playing the same old snake game?  
Then try Apple Survival, the game where you play as the apple trying to avoid being eaten by the snake!**

# Meet the Team
We are Group 77, a team of five students from ENGG1340-COMP2113(22-23 Sem 2):
+ Yu Tin Yau  3036067353
+ Shen Wenqi  3036061799
+ Tsui Chit Hei  3036067901
+ Wong Kai Ching  3036067884
+ Wong Chun Wang  3036085343

Together, we've taken the classic snake game and given it a fresh twist, creating a game that is both nostalgic and exciting.

# How To Play
Play as the apple and use the WASD (UP, LEFT, DOWN, RIGHT) keys to move around the screen.
It is suggested to not hold down the key, but instead press it only when you want to change directions.
Avoid the snake's head as you collect apples and try to stay alive as long as possible.
Beware though, the snake speed increases over time!

# Exciting Features
## Portals
Use portals to instantly teleport to other positions on the map, making gameplay more dynamic and strategic.
We've used arrays and dynamic memory management to ensure smooth gameplay. Portals are represented by the "@" symbol. When the player enters one,
he/she gets teleported randomly to another portal.

The random generation of portals fulfills the first requirement of random events.

Our portal also utitlizes dynamic memory is make efficient use of memory, which fulfills the third requirement.

## Highscores
Keep track of your scores and compete with others on the highscores list.
We've used file I/O and sorting algorithms to implement this feature, which fulfills the foruth requirement

## Random Events
Powerups and perks randomly appear in the game, giving you an extra boost to help you stay alive longer. 
"S" is an item that stuns the snake temporarily, while the "+" item increases player speed temporarily
You never know what you might get! 

The random generation of items fulfills the first requirement of random events.

# Data Structures for Storing Game Status
To keep track of game status, we've used a variety of data structures, including **arrays** and **vectors**. We use arrays to store information about the positions of game objects, as well as the coordinates of the player and the snake. Vectors are used to store highscores and the corresponding player names. By using these data structures, we're able to efficiently manage game status information and ensure smooth gameplay.#

# Non-standard C/C++ Libraries
***Important!***  
Our game uses the **ncurses** library for in-game content display.
**makefile failure** will happen if ncurses is not present in your operating system.  
If you don't have ncurses installed on your operating system, don't worry!
You can easily install it by running the following command:
> sudo apt-get install libncurses5-dev libncursesw5-dev

The library is used for generating graphics and animations so that the user can a smooth experience.

# Getting Started
To start playing Apple Survival, simply type the following commands into your terminal:
> make game  
> ./game

If you want to clean up your game files, we offer three options:
1. Reset Highscores:
> make clearscores

2. Clean game files: *note that highscores will not reset.*
> make clean

3. Complete remove the game:
> make uninstall

# Join the Fun!
Apple Survival is a fun and exciting game that is sure to keep you entertained for hours. 
So why not give it a try? :smile:
