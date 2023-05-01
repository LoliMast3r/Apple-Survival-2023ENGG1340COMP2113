#include <ncurses.h>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

void clearWindow(WINDOW *win, int height, int width) {
    //fills window with space (" ")
    for (int i=1; i<height-2; i++) {
        for (int j=1; j<width-2;j++) {
            mvwprintw(win, i, j, " ");
        }
    }
}

void mainMenu(WINDOW *win, int height, int width, string &select, int &slotNum) {
    noecho();
    refresh();
    string Options[4] = {"New Game", "Controls", "Highscore", "Quit"};
    
    for (int i=0; i<4; i++) {
        if (i == slotNum) {
            //prints "-->" with one of the option string to show user which option is under selection
            string printSlot = "-->"+Options[i];
            mvwprintw(win, ((height-4)/2)+i-2, ((width-Options[i].size())/2)-3, "%s", printSlot.c_str());
        } else {
            //removes the "-->" string
            string printSlot = "   "+Options[i];
            mvwprintw(win, ((height-4)/2)+i-2, ((width-Options[i].size())/2)-3, "%s", printSlot.c_str());
        }
        //prints options in the centre
        mvwprintw(win, ((height-4)/2)+i-2, (width-Options[i].size())/2, "%s", Options[i].c_str());
    }
    
    //controls for moving the "-->"
    while (true) {
        select = wgetch(win);
        if (select == "w") {
            slotNum--;
            break;
        } else if (select == "s") {
            slotNum++;
            break;
        } else if  (select == "\n") {
            break;
        }
    }
    if (slotNum == 4) {
        slotNum = 0;
    } else if (slotNum == -1) {
        slotNum = 3;
    }
}

void printArt(WINDOW *win, string filename) {
    string line = "";
    ifstream inFile;
    inFile.open(filename.c_str());
    if (inFile.is_open()) {
        int y = 0;
        while (getline(inFile, line)) {
            int x = 1;
            for (char c : line) {
                wmove(win, y, x);
                waddch(win, c);
                x++;
            }
            y++;
        }
    }
    inFile.close();
}

//handles the movement of the fruit with user input
void fruitMovement(string inputFruit, string& prevMoveFruit, int& fruitX, int& fruitY) {
    if (inputFruit == "w") {
        fruitY--;
        prevMoveFruit = inputFruit;
    } else if (inputFruit == "a") {
        fruitX--;
        prevMoveFruit = inputFruit;
    } else if (inputFruit == "s") {
        fruitY++;
        prevMoveFruit = inputFruit;
    } else if (inputFruit == "d") {
        fruitX++;
        prevMoveFruit = inputFruit;
    } else if (prevMoveFruit == "s") {
        fruitY++;
    } else if (prevMoveFruit == "d") {
        fruitX++;
    } else if (prevMoveFruit == "a") {
        fruitX--;
    } else if (prevMoveFruit == "w") {
        fruitY--;
    }
}

//handles the movement of the snake depending on the command from snakePathFind()
void snakeMovement(string direction, string& prevMove, int& snakeX, int& snakeY, float& updateDelay, double gameSpeed) {
    if (direction == "t" && prevMove != "g") {
        snakeY--;
        prevMove = direction;
        updateDelay = 0.2 / gameSpeed;
    } else if (direction == "f" && prevMove != "h") {
        snakeX--;
        prevMove = direction;
        updateDelay = 0.1 / gameSpeed;
    } else if (direction == "g" && prevMove != "t") {
        snakeY++;
        prevMove = direction;
        updateDelay = 0.2 / gameSpeed;
    } else if (direction == "h" && prevMove != "f") {
        snakeX++;
        prevMove = direction;
        updateDelay = 0.1 / gameSpeed;
    } else if (prevMove == "g") {
        snakeY++;
    } else if (prevMove == "h") {
        snakeX++;
    } else if (prevMove == "f") {
        snakeX--;
    } else if (prevMove == "t") {
        snakeY--;
    }
    
}

//decide direction of travel depending on the position of the fruit
string snakePathFind(int startX, int startY, int headX, int headY) {
    int dx = startX - headX;
    int dy = startY- headY;
    if (abs(dx)/2 >= abs(dy)) {
        if (dx > 0) {
            return "h";
        } else {
            return "f";
        }
    } else {
        if (dy > 0) {
            return "g";
        } else {
            return "t";
        }
    }
}

//increase game speed and snake length as time progesses
void updateGame(clock_t& prevPlayTime, int& tailLength, double& gameSpeed) {
    double elapsedTime = static_cast<float>(clock() - prevPlayTime) / CLOCKS_PER_SEC;
    if (elapsedTime >= 3) {
        if (tailLength <= 10) {
            tailLength++;
        }
        gameSpeed += 0.1;
        prevPlayTime = clock();
    }
}

//allows the snake and fruit to pass through the boundary
void checkBoundary(int& Pos, int bound1, int bound2) {
    if (Pos >= bound2-1) {
        Pos = 1;
    } else if (Pos <= 0) {
        Pos = bound2-2;
    }

    
}

void snakeGame(WINDOW *win, int height, int width, bool &snakeW, bool &playerW) {
    //spawn position of snake head
        int snakeX = 1;
        int snakeY = 1;

        int LastX, LastY, fruitX, fruitY;
        //spawn position of fruit
        fruitX = 12;
        fruitY = 25;
        int tailXY[10][2];
        tailXY[0][0] = snakeX; //set x-coordinate of snake head
        tailXY[0][1] = snakeY; //set y-coordinate of snake head
        int tailLength = 1;

        nodelay(win, true); //assumes input to be "NULL" when receives no input

        string prevMove = "p";
        string direction = "h";

        string inputFruit = "h";
        string prevMoveFruit = "d";

        //check input time interval for snake
        clock_t prevTime;
        clock_t currTime;
        prevTime = clock();  //sets prevTime to current time

        //check input time interval for game
        clock_t prevPlayTime;
        clock_t currPlayTime;
        prevPlayTime = clock(); //sets prevPlayTime to current time

        //check input time interval for fruit
        clock_t currFruitInputTime;
        clock_t prevFruitInputTime;
        prevFruitInputTime = clock();

        float updateDelay = 0.1;
        double gameSpeed = 1;
        
        int LastX1, LastY1;
        bool gameOver = false;
        while (inputFruit != "x") {
            noecho();

            updateGame(prevPlayTime, tailLength, gameSpeed);

            refresh();

            currTime = clock() - prevTime; //checks the time passed
            wrefresh(win);

            //snake
            float elaspedTime1 = (float)currTime/CLOCKS_PER_SEC;
            if (elaspedTime1 >= updateDelay) { //if time passed is less than 0.1, does not receive input

                wrefresh(win);

                //direction of travel command
                direction = snakePathFind(fruitX, fruitY, snakeX, snakeY);

                LastX = tailXY[tailLength-1][0];
                LastY = tailXY[tailLength-1][1];
                prevTime = clock();

                //snake movement control
                snakeMovement(direction, prevMove, snakeX, snakeY, updateDelay, gameSpeed);

                //allow passing through the boundaries
                checkBoundary(snakeX, 0 , width-1);
                checkBoundary(snakeY, 0, height-1);
            
                //update the tail to follow the head
                for (int i=tailLength-1;i>-1;i--) {
                    if (i == 0) {
                        tailXY[i][0] = snakeX;
                        tailXY[i][1] = snakeY;
                    } else {
                        tailXY[i][0] = tailXY[i-1][0];
                        tailXY[i][1] = tailXY[i-1][1];
                    }
                }
            }
        
            currFruitInputTime = clock() - prevFruitInputTime; //checks the time passed
            wrefresh(win);

            //fruit
            float elapsedTime2 = (float)currFruitInputTime/CLOCKS_PER_SEC;
            if (elapsedTime2 >= 0.1) { //if time passed is less than 0.1, does not receive input. Basically 10 fps

                wrefresh(win);

                inputFruit = wgetch(win);

                //store the previous position of the fruit
                LastX1 = fruitX;
                LastY1 = fruitY;
                prevFruitInputTime = clock(); //resets timer

                //fruit movement control
                fruitMovement(inputFruit, prevMoveFruit, fruitX, fruitY);

                //allow passing through the boundaries
                checkBoundary(fruitX, 0, width-1);
                checkBoundary(fruitY, 0, height-1);
            }

            //prints the snake
            for (int i=0; i<tailLength;i++) {
                if (i == 0) {
                    mvwprintw(win,(tailXY[i][1]),(tailXY[i][0]),"O");
                } else {
                    mvwprintw(win,(tailXY[i][1]),(tailXY[i][0]),"o");  //prints character at cursor
                }
            }
        
            //remove the trail left by the snake
            mvwprintw(win,LastY,LastX," ");

            //remove trail left by the fruit
            mvwprintw(win,LastY1,LastX1," ");

            //print the fruit
            mvwprintw(win,fruitY,fruitX,"A");

            //game ends when snake head touches the fruit
            if (tailXY[0][0] == fruitX && tailXY[0][1] == fruitY) {
                snakeW = true;
                break;
            }

            //snake dies when the head touches its tails
            for (int i=0;i<tailLength;i++) {
                if (tailXY[i][0] == tailXY[0][0] && tailXY[i][1] == tailXY[0][1] && (i != 0)) {
                    gameOver = true;
                    playerW = true;
                    break;
                }
            }

            //game ends
            if (gameOver == true) {
                break;
            }
        }
}

int main() {
    clear();

    initscr(); //initializes window
    
    //sets attributes for window
    int height = 25;
    int width = 50;
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    mvprintw(1, (maxX-10)/2, "Apple rush");
    WINDOW *win = newwin(height, width, (maxY-height)/2, (maxX-width)/2); //sets window to centre
    refresh();

    //announce game state
    bool snakeW = false;
    bool playerW = false;
    bool fullGameOver = false;

    box(win,0,0); //sets border
    
    while (!fullGameOver) {
        
        string select;
        int slotNum = 0; //sets the position of "-->" at "New Game"
        while (true) {
            mainMenu(win, height, width, select, slotNum);
            if (select == "\n") {
                if (slotNum == 0) {
                    clearWindow(win, height, width);
                    snakeGame(win, height, width, snakeW, playerW);

                    clearWindow(win, height, width);

                    string filename;
                    if (snakeW) {
                        filename = "gameOver.txt";
                    } else if (playerW) {
                        filename = "gameWin.txt";
                    }
                    printArt(win, filename);

                    string c;
                    do {
                        c = wgetch(win);
                    } while (c != "\n");

                    clearWindow(win, height, width);

                    filename = "gameScore.txt";
                    printArt(win, filename);
                    do {
                        c = wgetch(win);
                    } while (c!= "\n");

                    clearWindow(win, height, width);
                } else if (slotNum == 3) {
                    fullGameOver = true;
                    break;
                }
            }
        }
        if (fullGameOver == true) {
            break;
        }
        clearWindow(win, height, width);
        //game ends when X-key is pressed
        
    }
    clearWindow(win, height, width);
    wrefresh(win); //refreshes window
    
    endwin();
    
    
    return 0;
}