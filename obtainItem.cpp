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
using namespace std;

int obtainItem(int fruitX, int fruitY, WINDOW *win, bool &itemSpawn, clock_t& ItemSpawntime, int items[2][2], int &chooseItem, int width, int height ) {
    //generates item and allows players to collect it
    double elapsedTime3 = static_cast<float>(clock() - ItemSpawntime) / CLOCKS_PER_SEC;
    if (elapsedTime3 >= 5 && itemSpawn == false ) {
        //prints item if only 5 seconds have passed after user last picked up an item
        itemSpawn = true; 
        return -1;
    } else if (itemSpawn == true) {
        
        if (chooseItem == 0) { //prints either one of "+" or "S"
            mvwprintw(win, items[chooseItem][1], items[chooseItem][0], "+");
        } else if (chooseItem == 1) {
            mvwprintw(win, items[chooseItem][1], items[chooseItem][0], "S");
        }
        
        if (fruitX == items[chooseItem][0] && fruitY == items[chooseItem][1]) {
            //if picked up, waits an extra 5 seconds before showing another item
            itemSpawn = false;
            ItemSpawntime = clock();
            mvwprintw(win, items[chooseItem][1], items[chooseItem][0], " ");
            items[chooseItem][0] = (rand() % (width-3))+1; //assign new location for item
            items[chooseItem][1] = (rand() % (height-3))+1;
            int prevItem = chooseItem;
            chooseItem = rand()%2;
            return prevItem;

        } else {
            return -1;
        }
        
    } else {
        return -1;
    }
    

}