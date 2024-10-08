#include <ncurses.h>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <array>
#include "obtainItem.h"
#include "PortalGen.h"
#include "clearwindow.h"
using namespace std;

void fruitMovement(string inputFruit, string& prevMoveFruit, int& fruitX, int& fruitY, float &updateDelay1, double gameSpeed1, double& adjust) {
    //handles the movement of the fruit with user input
    if (inputFruit == "w") {
        fruitY--;
        prevMoveFruit = inputFruit;
        updateDelay1 = 0.14 / gameSpeed1 - adjust; 
        //update delay refers to time waited before moving one unit everytime, basically how fast the snake moves
        //as we want to speed up the snake over time, gamespeed serves as a factor that we can increase/decrease snake speed
        //since 1 height unit = 2 width units, vertical has to be 0.5 times horizontal speed
    } else if (inputFruit == "a") {
        fruitX--;
        updateDelay1 = 0.07 / gameSpeed1 - adjust/2;
        prevMoveFruit = inputFruit; 
        //prevMove stores the previous move so that if no key is pressed, the object continues in same direction
    } else if (inputFruit == "s") {
        fruitY++;
        prevMoveFruit = inputFruit;
        updateDelay1 = 0.14 / gameSpeed1 - adjust;
    } else if (inputFruit == "d") {
        fruitX++;
        prevMoveFruit = inputFruit;
        updateDelay1 = 0.07 / gameSpeed1 - adjust/2;
    } else if (prevMoveFruit == "s") {
        fruitY++;
        updateDelay1 = 0.14 / gameSpeed1 - adjust;
    } else if (prevMoveFruit == "d") {
        fruitX++;
        updateDelay1 = 0.07 / gameSpeed1 - adjust/2;
    } else if (prevMoveFruit == "a") {
        fruitX--;
        updateDelay1 = 0.07 / gameSpeed1 - adjust/2;
    } else if (prevMoveFruit == "w") {
        fruitY--;
        updateDelay1 = 0.14 / gameSpeed1 - adjust;
    }
}

void snakeMovement(string direction, string& prevMove, int& snakeX, int& snakeY, float& updateDelay, double gameSpeed, double& snakeadjust) {
    //handles the movement of the snake depending on the command from snakePathFind()
    //same logic as fruit movement
    if (direction == "t" && prevMove != "g") {
        snakeY--;
        prevMove = direction;
        updateDelay = 0.2 / gameSpeed + snakeadjust;
    } else if (direction == "f" && prevMove != "h") {
        snakeX--;
        prevMove = direction;
        updateDelay = 0.1 / gameSpeed + snakeadjust/2;
    } else if (direction == "g" && prevMove != "t") {
        snakeY++;
        prevMove = direction;
        updateDelay = 0.2 / gameSpeed + snakeadjust;
    } else if (direction == "h" && prevMove != "f") {
        snakeX++;
        prevMove = direction;
        updateDelay = 0.1 / gameSpeed + snakeadjust/2;
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

void mainMenu(WINDOW *win, int height, int width, string &select, int &slotNum) {
     //select is passed by reference since we need to save the button pressed to detect whether "Enter" is pressed, outside function
    noecho();
    refresh();
    string Options[4] = {"New Game", "Story", "Highscore", "Quit"};  //main menu options
    
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

void Highscores(WINDOW *win,int height, int width, string &select, int page){ //browse highscores
    clearWindow(win, height, width); 
    noecho();
    refresh();

    string name;int score;
    vector <pair<string,int>> scores; // make a paired vector for easy sorting

    ifstream File;

    File.open("highscore.txt"); // append highscore names and values into a vector for iteration
    while(File >> name >> score){
        scores.push_back(make_pair(name,score));
    }
    File.close(); 
    if(scores.size()==0){  //print msg if no scores yet.
        string noscores = "No Scores yet!";
        mvwprintw(win,11,19,"%s",noscores.c_str());
    } 
    else{
        sort(scores.begin(),scores.end(), [](const pair<string,int> &left, const pair<string,int> &right) {
        return left.second > right.second;}); //sort pairs according to scores

        string tempname,tempscore;int vecsize;
        if(8*page > scores.size()) vecsize = scores.size() - 8*(page-1); //8 scores per page
        else vecsize = 8;

        for(int i=0; i<vecsize; i++){
            if(scores[8*(page-1)+i].first.length() > 10) tempname = scores[8*(page-1)+i].first.substr(0,10); // formatting width to 10 in case name is too long
            else tempname = scores[8*(page-1)+i].first;
            tempscore = "        "; // align to right
            tempscore.replace(8-(to_string(scores[8*(page-1)+i].second).length()),to_string(scores[8*(page-1)+i].second).length(),to_string(scores[8*(page-1)+i].second));

            mvwprintw(win,((height-4)/2)+i-2,11,"%s",tempname.c_str());
            mvwprintw(win,((height-4)/2)+i-2,29,"%s",tempscore.c_str());
        }  
    }      

    int b = floor(scores.size()/8)+1; // Layout for Highscores
    string title = "Highscores";
    string title2 = "-----------------------------";
    string pagestr = "<Page "+to_string(page)+" of "+to_string(b)+">";
    string instructions = "Press a and d to change page number.";
    string instructions2 = "Or press s to go back.";
    mvwprintw(win,5,20,"%s",title.c_str());
    mvwprintw(win,6,10,"%s",title2.c_str());
    mvwprintw(win,17,19,"%s",pagestr.c_str());
    mvwprintw(win,18,7,"%s",instructions.c_str());
    mvwprintw(win,19,14,"%s",instructions2.c_str());
    string userInput;
    while (true) {
        userInput = wgetch(win);     //page scrolling and back to main        
        if(userInput == "a"){ 
            if(page != 1)page -= 1;  
            clearWindow(win, height, width); 
            Highscores(win, height, width, select,page); 
        }

        if(userInput == "d"){
            if(page != b)page += 1; 
            clearWindow(win, height, width);  
            Highscores(win, height, width, select,page);
        }

        if(userInput == "s"){
            break;
        }
    }
    clearWindow(win, height, width);  
}
void importscore(string name,int score){
    ofstream Write;
    Write.open("highscore.txt",ios::app);
    if(name=="") name = "Anonymous";
    Write << name << " " << score;
    Write.close();
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

void scorescreen(WINDOW *win,int height,int timeS,int PortalS,int ItemS){
    echo();
    refresh();
    nodelay(win, false);
    int total;string name;
    PortalS = PortalS*3;
    total = timeS+PortalS+ItemS;
    array<string,3> cat = {"Playing Time:","Portals Used:","Items Obtained:"};
    array<int,3> ss = {timeS,PortalS,ItemS};
    string title = "Metric             Scores";
    string title2 = "_____________________________";
    string entername = "Enter your name: ";
    mvwprintw(win,5,12,"%s",title.c_str());
    mvwprintw(win,6,10,"%s",title2.c_str());
    for(int i=0;i<cat.size();i++){
        mvwprintw(win,((height-4)/2)+i-2,10,"%s",cat[i].c_str()); // print categories

        string tempscore = "        "; // align to right
        tempscore.replace(8-to_string(ss[i]).length(),to_string(ss[i]).length(),to_string(ss[i]));
        mvwprintw(win,((height-4)/2)+i-2,30,"%s",tempscore.c_str());
    }
    mvwprintw(win,14,10,"%s",title2.c_str());
    string temptotal = "        ";
    temptotal.replace(8-to_string(total).length(),to_string(total).length(),to_string(total));
    string totalsss = "Total:              "+temptotal;
    mvwprintw(win,15,10,"%s",totalsss.c_str());
    mvwprintw(win,18,11,"%s",entername.c_str()); // get name for import highscore
    name = "";
    string getchar = "s";
    while (getchar!="\n") {
        getchar = wgetch(win);
        if (getchar != "\n") {
            name += getchar;
        }
    }
    importscore(name,total);
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

void story(WINDOW *win, int height, int width) { //prints background story, Press 's' to quit              
    string line1 = "In the Garden of Eden, God once created the ";
    string line2 = " first ever human beings to exist -- Adam and";
    string line3 = "Eve. It was a perfect place, free from sin and";
    string line4 = "evil. However, God warned about a forbidden";
    string line5 = "apple they should not eat and Satan, in the form";
    string line6 = "of a snake, is planning to lure them into eating";
    string line7 = " it. You are the apple, run from the devil";
    string line8 = "himself to avoid the corruption of mankind!";
    string line9 = "Satan MUST NOT PREVAIL!!!";
    string line15 = "Press S to quit";
    mvwprintw(win, 1, 1, "%s", line1.c_str());
    mvwprintw(win, 2, 1, "%s", line2.c_str());
    mvwprintw(win, 3, 1, "%s", line3.c_str());
    mvwprintw(win, 4, 1, "%s",line4.c_str());
    mvwprintw(win, 5, 1, "%s",line5.c_str());
    mvwprintw(win, 6, 1, "%s",line6.c_str());
    mvwprintw(win, 7, 1, "%s",line7.c_str());
    mvwprintw(win, 8, 1, "%s",line8.c_str());
    mvwprintw(win, 9, 1,"%s", line9.c_str());
    mvwprintw(win, 15, (50-15)/2, "%s",line15.c_str()); //print line 11 in the middle of the screen
    string inputOut = "p";
    while (inputOut != "s") {
        inputOut = wgetch(win);
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

int snakeGame(WINDOW *win, int height, int width, bool &snakeW, bool &playerW, int &timescore, int &portalscore) {
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

        //check Gametime
        clock_t Gametime;
        clock_t ElapsedGametime;
        clock_t GameEndtime;
        Gametime = clock();

        //check item spawn time
        clock_t ItemSpawntime;
        ItemSpawntime = clock();
        bool itemSpawn = false;
        int chooseItem = rand()%2;
        bool itemObtained = false;
        int prevItem;
        clock_t effectDuration;
        effectDuration = clock();


        //some scoring para
        
        float updateDelay = 0.1; //snake Update Delay
        double gameSpeed = 1; //factor that affects snake speed

        float updateDelay1 = 0.07; //fruit update delay
        double gameSpeed1 = 1; //factor that affects snake speed 
        
        int LastX1, LastY1;
        bool gameOver = false;

        bool obtainedItem1 = false;
        bool obtainedItem2 = false;

        // item spd adjustments
        double adjust,snakeadjust = 0;
        int itemscores = 0;

        int Portal[3][2]; //Store coordinates of Portals
        unsigned int srand(time(NULL)); //set random seed
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
        int items[2][2]; //generates coordinates of items for the first time
        for (int i=0; i<2; i++) {
            items[i][0] = (rand() % (width-3))+1;
            items[i][1] = (rand() % (height-3))+1;
        }
        while (true) { 
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
                snakeMovement(direction, prevMove, snakeX, snakeY, updateDelay, gameSpeed, snakeadjust); //moves snake

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
                int obtained = obtainItem(fruitX, fruitY, win, itemSpawn, ItemSpawntime, items, chooseItem, width ,height);
                double elapsedTime4 = static_cast<float>(clock() - effectDuration) / CLOCKS_PER_SEC;
                if (obtained == 0) {
                    prevItem = obtained; //stores what item is picked up to reverse the effects accordingly afterwards
                    effectDuration = clock();//reset timer for next item spawn time
                    adjust = 0.06; //speeds up player
                    itemscores += 3; //increases points
                } else if (obtained == 1) {
                    prevItem = obtained;
                    effectDuration = clock();
                    snakeadjust = 1; //stuns snake
                    itemscores += 3;
                } else if (prevItem==0 && elapsedTime4 >= 3 ) {
                    prevItem = -1;
                    adjust = 0; //reverses effect
                } else if (prevItem == 1 && elapsedTime4 >= 1.5) {
                    prevItem = -1;
                    snakeadjust = 0; //reverses effect
                }
                inputFruit = wgetch(win); //get user input

                //store the previous position of the fruit to remove after, like snake
                LastX1 = fruitX;
                LastY1 = fruitY;
                prevFruitInputTime = clock(); //resets timer

                //fruit movement control
                fruitMovement(inputFruit, prevMoveFruit, fruitX, fruitY, updateDelay1, gameSpeed1, adjust);

                //allow passing through the boundaries
                checkBoundary(fruitX, 0, width-1);
                checkBoundary(fruitY, 0, height-1);
                PortalGen(fruitX, fruitY, Portal, win, height,width,portalscore);
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
                gameOver = true;
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
            if (gameOver == true) {;
                GameEndtime = clock();
                timescore = ((double)(GameEndtime - Gametime))/CLOCKS_PER_SEC;
                return itemscores;
            }
        }
    return 0;
}

int main() {
    clear();

    initscr(); //initializes window
    
    //sets attributes for window
    int height = 25;
    int width = 50;
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    mvprintw(1, (maxX-14)/2, "Apple Survival");  //prints game name 
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
                    int timescore,portalscore,itemscores;
                    portalscore = 0;
                    clearWindow(win, height, width); 
                    itemscores = snakeGame(win, height, width, snakeW, playerW,timescore, portalscore); //start snake game

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

                    scorescreen(win,height,timescore,portalscore,itemscores);
                    do {
                        c = wgetch(win);
                    } while (c != "\n");
                    clearWindow(win, height, width);

                } else if (slotNum == 3) {//and quit is selected
                    fullGameOver = true;
                    break; //quits game
                } else if (slotNum == 2) { //and Highscore is selected
                    clearWindow(win, height, width);
                    Highscores(win, height, width, select,1); //Display Highscores
                } else if (slotNum == 1) {
                    clearWindow(win, height, width);
                    story(win, height, width);
                    clearWindow(win, height, width);
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
