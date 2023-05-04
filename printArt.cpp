#include <iostream>
#include <string>
#include <fstream>
#include <ncurses.h>
using namespace std;

//sample printArt function
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


//the main() only serves as a sample for the overall logic
//the validity of the file was not checked
int main() {
    clear();
    initscr();

    int height = 25;
    int width = 50;
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    mvprintw(1, (maxX-10)/2, "Apple rush");
    WINDOW *win = newwin(height, width, (maxY-height)/2, (maxX-width)/2); //sets window to centre
    refresh();

    box(win,0,0); //sets border

    string filename = "gameOver.txt";
    printArt(win,filename);
    wrefresh(win);

    endwin();
}