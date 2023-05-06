#include <ncurses.h>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <array>
#include "PortalGen.h"
using namespace std;

void PortalGen(int &fruitX, int &fruitY, int Portal[3][2], WINDOW  *win, int height, int width, int &portalscore) {
    int PortalChosen; bool touched = false; 
    for (int i=0; i<3;i++) {
        if (fruitX == Portal[i][0] && fruitY == Portal[i][1]) { //if apple touches portal....
            touched = true;
            portalscore+=1;
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
