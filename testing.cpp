#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
using namespace std;
int main(void) {
    initscr();
    char c = getch();
    addch(c);
    getch();
    endwin();
    return 0;
}