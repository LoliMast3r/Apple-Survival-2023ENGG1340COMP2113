#include <ncurses.h>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void PortalGen(int &fruitX, int &fruitY, int Portal[3][2], WINDOW  *win, int height, int width) {
    int PortalChosen; 
    for (int i=0; i<3;i++) {
        if (fruitX == Portal[i][0] && fruitY == Portal[i][1]) { //if apple touches portal....
            while (true) {
                PortalChosen = rand()%3; //randomly select another portal to teleport to
                if (PortalChosen != i) { //make sure it isn't the same portal
                    break;
                }
            }
            fruitX = Portal[PortalChosen][0]; //teleports fruit to chosen portal
            fruitY = Portal[PortalChosen][1];
            mvwprintw(win, Portal[i][1], Portal[i][0], " " ); //removes the previous portals
            mvwprintw(win, Portal[PortalChosen][1], Portal[PortalChosen][0], " " );
            int *k1,*k2;
            bool portalduplicate=true;
            while (portalduplicate==true) { //check portals are not duplicate
                portalduplicate=false;
                k1=new int; //create dynamic memory of k1,k2
                k2=new int;
                *k1=(rand() % (width-3))+1;
                *k2=(rand() % (height-3))+1;
                for (int j=0; j<3; j++) {    
                    if (*k1==Portal[j][0] || *k2==Portal[j][1]) {
                        portalduplicate=true;
                        break;
                    }
                }
            }
            Portal[i][0] = *k1; //create new portals
            Portal[i][1] = *k2;
            portalduplicate=true;
            while (portalduplicate==true) { //check portals are not duplicate
                portalduplicate=false;
                *k1=(rand() % (width-3))+1;
                *k2=(rand() % (height-3))+1;
                for (int j=0; j<3; j++) {    
                    if (*k1==Portal[j][0] || *k2==Portal[j][1]) {
                        portalduplicate=true;
                        break;
                    }
                }
            }
            Portal[PortalChosen][0] = *k1; //create new portals
            Portal[PortalChosen][1] = *k2;
            delete k1; //release dynamic memory
            delete k2;
            break;
        }
    }
    for (int i=0; i<3; i++) {
        mvwprintw(win, Portal[i][1], Portal[i][0], "@" ); //Prints the Portal 
    }
    
}
void clearWindow(WINDOW *win, int height, int width) {
    //fills window with space (" ")
    for (int i=1; i<height-2; i++) {
        for (int j=1; j<width-2;j++) {
            mvwprintw(win, i, j, " ");
        }
    }
}

void mainMenu(WINDOW *win, int height, int width, string &select, int &slotNum) {
     //select is passed by reference since we need to save the button pressed to detect whether "Enter" is pressed, outside function
    noecho();
    refresh();
    string Options[4] = {"New Game", "Help", "Highscore", "Quit"};  //main menu options
    
    for (int i=0; i<4; i++) { //prints all four options
        if (i == slotNum) {
            //prints "-->" beside the option selected 
            string printSlot = "-->"+Options[i];
            mvwprintw(win, ((height-4)/2)+i-2, ((width-Options[i].size())/2)-3, "%s", printSlot.c_str());
        } else {
            //removes the "-->" before unselected options
            string printSlot = "   "+Options[i];
            mvwprintw(win, ((height-4)/2)+i-2, ((width-Options[i].size())/2)-3, "%s", printSlot.c_str());
        }
        //prints options in the centre
        mvwprintw(win, ((height-4)/2)+i-2, (width-Options[i].size())/2, "%s", Options[i].c_str());
    }
    
    while (true) {
        select = wgetch(win);
        if (select == "w") { //move selector up
            slotNum--;
            break;
        } else if (select == "s") { // move selector down
            slotNum++;
            break;
        } else if  (select == "\n") { //does nothing within the function
            break;
        }
    }
    if (slotNum == 4) {
        slotNum = 0; //so that selector doesn't go out of bounds
    } else if (slotNum == -1) {
        slotNum = 3;
    }
}

void Highscores(WINDOW *win,int height, int width, string &select){ //browse highscores(testing)
    noecho();
    refresh();

    string name; int score;
    vector <string> names; vector <int> scores;
    ifstream File;

    File.open("highscore.txt"); // append highscore names and values into a vector for iteration
    while(File >> name >> score){
        names.push_back(name);
        scores.push_back(score);
    }
  File.close();

    for(int i=0; i<names.size(); i++){
        cout << names[i] << " " << scores[i] << endl;
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


void fruitMovement(string inputFruit, string& prevMoveFruit, int& fruitX, int& fruitY, float &updateDelay1, double gameSpeed1) {
    //handles the movement of the fruit with user input
    if (inputFruit == "w") {
        fruitY--;
        prevMoveFruit = inputFruit;
        updateDelay1 = 0.14 / gameSpeed1; 
        //update delay refers to time waited before moving one unit everytime, basically how fast the snake moves
        //as we want to speed up the snake over time, gamespeed serves as a factor that we can increase/decrease snake speed
        //since 1 height unit = 2 width units, vertical has to be 0.5 times horizontal speed
    } else if (inputFruit == "a") {
        fruitX--;
        updateDelay1 = 0.07 / gameSpeed1;
        prevMoveFruit = inputFruit; 
        //prevMove stores the previous move so that if no key is pressed, the object continues in same direction
    } else if (inputFruit == "s") {
        fruitY++;
        prevMoveFruit = inputFruit;
        updateDelay1 = 0.14 / gameSpeed1;
    } else if (inputFruit == "d") {
        fruitX++;
        prevMoveFruit = inputFruit;
        updateDelay1 = 0.07 / gameSpeed1;
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


void snakeMovement(string direction, string& prevMove, int& snakeX, int& snakeY, float& updateDelay, double gameSpeed) {
    //handles the movement of the snake depending on the command from snakePathFind()
    //same logic as fruit movement
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


string snakePathFind(int startX, int startY, int headX, int headY) {
    //decide direction of travel depending on the position of the fruit
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


void updateGame(clock_t& prevPlayTime, int& tailLength, double& gameSpeed) {
    //increase game speed and snake length as time progesses
    double elapsedTime = static_cast<float>(clock() - prevPlayTime) / CLOCKS_PER_SEC; //time passed before previous increase in tail and speed
    if (elapsedTime >= 5) { //if 5 seconds passed
        if (tailLength <= 10) { //max tail length = 10
            tailLength++; //increase tail
        }
        gameSpeed += 0.1; //speed up snakespeed 
        prevPlayTime = clock(); //resets timer
    }
}


void checkBoundary(int& Pos, int bound1, int bound2) {
    //allows the snake and fruit to pass through the boundary
    if (Pos >= bound2-1) {
        Pos = 1;
    } else if (Pos <= 0) {
        Pos = bound2-2;
    }

    
}

void snakeGame(WINDOW *win, int height, int width, bool &snakeW, bool &playerW) {
    //spawn position of snake head (X, Y coord)
        int snakeX = 1;
        int snakeY = 1;

        int LastX, LastY, fruitX, fruitY;
        //spawn position of fruit
        fruitX = 12;
        fruitY = 25;
        int tailXY[10][2]; //array to store the head and tail of snake
        tailXY[0][0] = snakeX; 
        tailXY[0][1] = snakeY; 
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

        float updateDelay = 0.1; //snake Update Delay
        double gameSpeed = 1; //factor that affects snake speed

        float updateDelay1 = 0.07; //fruit update delay
        double gameSpeed1 = 1; //factor that affects snake speed 
        
        int LastX1, LastY1;
        bool gameOver = false;

        int Portal[3][2]; //Store coordinates of Portals
        srand(time(NULL)); //set random seed
        Portal[0][0] = (rand() % (width-3))+1; //Sets up initial position for the 3 portals
        Portal[0][1] = (rand() % (height-4))+1;
        for (int i=1; i<3; i++) {
            int *k1,*k2;   
            bool portalduplicate=true;
            while (portalduplicate==true) {
                portalduplicate=false;
                k1=new int; //create dynamic memory of k1,k2
                k2=new int;
                *k1=(rand() % (width-3))+1;
                *k2=(rand() % (height-3))+1;
                for (int j=0; j<3; j++) {    
                    if (*k1==Portal[j][0] || *k2==Portal[j][1]) {
                        portalduplicate=true;
                        break;
                    }
                }
            }
            Portal[i][0] = *k1;
            Portal[i][1] = *k2;
            delete k1; //free dynamic memory
            delete k2;
        }
        
        while (inputFruit != "x") { //quits when "x" is pressed 
            noecho();

            updateGame(prevPlayTime, tailLength, gameSpeed); //check if speed up snake and increase tail

            refresh();

            currTime = clock() - prevTime; //checks the time passed
            wrefresh(win);
            
            //snake
            float elaspedTime1 = (float)currTime/CLOCKS_PER_SEC;
            if (elaspedTime1 >= updateDelay) { //if time passed is less than threshold, does not receive input

                wrefresh(win);

                //get direction for snake
                direction = snakePathFind(fruitX, fruitY, snakeX, snakeY);

                LastX = tailXY[tailLength-1][0]; //gets previous position of the last tail unit to remove trail later
                LastY = tailXY[tailLength-1][1];
                prevTime = clock();

                //snake movement control
                snakeMovement(direction, prevMove, snakeX, snakeY, updateDelay, gameSpeed); //moves snake

                //allow passing through the boundaries
                checkBoundary(snakeX, 0 , width-1); //check if snake pass border
                checkBoundary(snakeY, 0, height-1);
            
                //update the tail to follow the head
                for (int i=tailLength-1;i>-1;i--) {
                    if (i == 0) {
                        tailXY[i][0] = snakeX; //first tail follows previous position of head
                        tailXY[i][1] = snakeY;
                    } else {
                        tailXY[i][0] = tailXY[i-1][0]; //tails follows previous position of previous tail
                        tailXY[i][1] = tailXY[i-1][1];
                    }
                }
            }
        
            currFruitInputTime = clock() - prevFruitInputTime; //checks the time passed
            wrefresh(win);

            //fruit
            float elapsedTime2 = (float)currFruitInputTime/CLOCKS_PER_SEC;
            if (elapsedTime2 >= updateDelay1) { //if time passed is less than threshold, does not receive input

                wrefresh(win);

                inputFruit = wgetch(win); //get user input

                //store the previous position of the fruit to remove after, like snake
                LastX1 = fruitX;
                LastY1 = fruitY;
                prevFruitInputTime = clock(); //resets timer

                //fruit movement control
                fruitMovement(inputFruit, prevMoveFruit, fruitX, fruitY, updateDelay1, gameSpeed1);

                //allow passing through the boundaries
                checkBoundary(fruitX, 0, width-1);
                checkBoundary(fruitY, 0, height-1);
                PortalGen(fruitX, fruitY, Portal, win, height,width); //checks if fruit reaches portal
            }

            //prints the snake
            for (int i=0; i<tailLength;i++) {
                if (i == 0) {
                    mvwprintw(win,(tailXY[i][1]),(tailXY[i][0]),"O"); //print head
                } else {
                    mvwprintw(win,(tailXY[i][1]),(tailXY[i][0]),"o");  //print tail
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
    mvprintw(1, (maxX-10)/2, "Apple rush");  //prints game name 
    WINDOW *win = newwin(height, width, (maxY-height)/2, (maxX-width)/2); //sets window to centre
    refresh();

    //announce game state
    bool snakeW = false;
    bool playerW = false;
    bool fullGameOver = false;

    box(win,0,0); //sets border for window
    
    while (!fullGameOver) {
        
        string select;
        int slotNum = 0; //default select New Game
        while (true) {
            mainMenu(win, height, width, select, slotNum); //generates main menu
            if (select == "\n") { //if enter is pressed 
                if (slotNum == 0) { //and new game is selected
                    clearWindow(win, height, width); 
                    snakeGame(win, height, width, snakeW, playerW); //start snake game

                    clearWindow(win, height, width);

                    string filename;
                    if (snakeW) {
                        filename = "gameOver.txt"; //prints lose screen
                    } else if (playerW) {
                        filename = "gameWin.txt"; //prints win screen
                    }
                    printArt(win, filename); 

                    string c;
                    do {
                        c = wgetch(win);
                    } while (c != "\n"); //waits for any input

                    clearWindow(win, height, width);

                    filename = "gameScore.txt";
                    printArt(win, filename);
                    do {
                        c = wgetch(win);
                    } while (c!= "\n");

                    clearWindow(win, height, width);
                } else if (slotNum == 3) {//and quit is selected
                    fullGameOver = true;
                    break; //quits game
                }
                if (slotNum == 2) { //and Highscore is selected
                clearWindow(win, height, width); 
                Highscores(win, height, width, select); //Display Highscores
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