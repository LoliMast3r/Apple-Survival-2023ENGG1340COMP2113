#include <ncurses.h>
#include <string>
#include <ctime>
#include <iostream>
using namespace std;

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


void snakeMovement(string c, string& prevMove, int& snakeX, int& snakeY, float& updateDelay, double gameSpeed) {
    if (c == "t" && prevMove != "g") {
        snakeY--;
        prevMove = c;
        updateDelay = 0.2 / gameSpeed;
    } else if (c == "f" && prevMove != "h") {
        snakeX--;
        prevMove = c;
        updateDelay = 0.1 / gameSpeed;
    } else if (c == "g" && prevMove != "t") {
        snakeY++;
        prevMove = c;
        updateDelay = 0.2 / gameSpeed;
    } else if (c == "h" && prevMove != "f") {
        snakeX++;
        prevMove = c;
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

string snakePathFind(int startX, int startY, int headX, int headY) {
    int dx = startX - headX;
    int dy = startY- headY;
    if (abs(dx)/2>=abs(dy)) {
        if (dx>0) {
            return "h";
        } else {
            return "f";
    

        }
    } else {
        if (dy>0) {
            return "g";
        } else {
            return "t";
        }
    }
}

void updateGame(clock_t& prevPlayTime, int& tailLength, double& gameSpeed) {
    double elapsedTime = static_cast<float>(clock() - prevPlayTime) / CLOCKS_PER_SEC;
    if (elapsedTime >= 3) {
        if (tailLength <= 10) {
            tailLength++;
        }
        gameSpeed += 0;
        prevPlayTime = clock();
    }
}

void checkBoundary(int& Pos, int bound1, int bound2) {
    if (Pos >= bound2-1) {
        Pos = 1;
    } else if (Pos <= 0) {
        Pos = bound2-2;
    }

    
}

int main() {
    clear();
    bool gameOver = false;
    initscr(); //initializes window
    int height = 25;
    int width = 50;
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    WINDOW *win = newwin(height, width, (maxY-height)/2, (maxX-width)/2); //sets window to middle of terminal
    refresh();

    box(win,0,0); //sets border

    int snakeX = 1;
    int snakeY = 1;

    int LastX, LastY, fruitX, fruitY;
    fruitX = 12;
    fruitY = 25;
    int tailXY[10][2];
    tailXY[0][0] = snakeX;
    tailXY[0][1] = snakeY;
    int tailLength = 1;

    nodelay(win, true); //assumes input to be "NULL" when receives no input
    string prevMove = "p";
    string c = "h";

    string inputFruit = "h";
    string prevMoveFruit = "d";

    clock_t prevTime;
    clock_t currTime;
    prevTime = clock();  //sets prevTime to current time

    clock_t prevPlayTime;
    clock_t currPlayTime;
    prevPlayTime = clock();  //sets prevPlayTime to current time

    clock_t currFruitInputTime;
    clock_t prevFruitInputTime;
    prevFruitInputTime = clock();

    float updateDelay = 0.1;
    double gameSpeed = 1;

    int LastX1, LastY1;

    while (inputFruit != "x") {
        noecho();

        updateGame(prevPlayTime, tailLength, gameSpeed);

        refresh();

        currTime = clock() - prevTime; //checks the time passed
        wrefresh(win);

        float elaspedTime1 = (float)currTime/CLOCKS_PER_SEC;
        if (elaspedTime1 >= updateDelay) { //if time passed is less than 0.1, does not receive input. Basically 10 fps.

            wrefresh(win);

            c = snakePathFind(fruitX, fruitY, snakeX, snakeY);
            

            LastX = tailXY[tailLength-1][0];
            LastY = tailXY[tailLength-1][1];
            prevTime = clock();

            snakeMovement(c, prevMove, snakeX, snakeY, updateDelay, gameSpeed);

            checkBoundary(snakeX, 0 , width-1);
            checkBoundary(snakeY, 0, height-1);
            
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

        float elapsedTime2 = (float)currFruitInputTime/CLOCKS_PER_SEC;
        if (elapsedTime2 >= 0.1) { //if time passed is less than 0.1, does not receive input. Basically 10 fps

            wrefresh(win);

            inputFruit = wgetch(win);

            LastX1 = fruitX;
            LastY1 = fruitY;
            prevFruitInputTime = clock(); //resets timer

            fruitMovement(inputFruit, prevMoveFruit, fruitX, fruitY);

            checkBoundary(fruitX, 0, width-1);
            checkBoundary(fruitY, 0, height-1);
        }
        
        

        for (int i=0; i<tailLength;i++) {
            if (i == 0) {
                mvwprintw(win,(tailXY[i][1]),(tailXY[i][0]),"O");
            } else {
                mvwprintw(win,(tailXY[i][1]),(tailXY[i][0]),"o");  //prints character at cursor
            }
        }
        
        mvwprintw(win,LastY,LastX," ");
        mvwprintw(win,LastY1,LastX1," ");
        mvwprintw(win,fruitY,fruitX,"A");
        if (tailXY[0][0] == fruitX && tailXY[0][1] == fruitY) {
            break;
        } 
        for (int i=0;i<tailLength;i++) {
            if (tailXY[i][0] == tailXY[0][0] && tailXY[i][1] == tailXY[0][1] && (i != 0)) {
                gameOver = true;
                break;
            }
        }
        if (gameOver == true) {
            break;
        }
    }
    wrefresh(win); //refreshes window
    
    endwin(); 
    return 0;
}