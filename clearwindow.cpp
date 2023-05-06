#include <ncurses.h>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <array>
#include "clearwindow.h"
using namespace std;

void clearWindow(WINDOW *win, int height, int width) {
    //fills window with space (" ")
    for (int i=1; i<height-1; i++) {
        for (int j=1; j<width-1;j++) {
            mvwprintw(win, i, j, " ");
        }
    }
}