#include <iostream>
#include <string>
#include <fstream>
#include <ncurses.h>
#include <ctime>
#include <cstdlib>

//get the real time in sec as a unit

int currentSec(){
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
}

//x== width, y=height

int locationGenerator(){
      for(int i = 0; i < 50; i++){
        int x = rand() % N;
      }
      for(int i = 0; i < 50; i++){
        int y = rand() % N;
      }
}

void printItem(int playerx, int playery, int snakex, int snakey, int item_picked){
  while{gameOver!==True){
      int item_number=0;
      int sec = currentSec().elapsed_seconds;
      if (sec/10)==0 and (item_number==0){
          item_number+=1;
          int location_x=locationGenerator().x;
          int location_y=locationGenerator().y;
          mvwprintw(win,location_y,location_x,3);
          if(playerx==location_x) and (playery==location_y){
              item_number-=1;
              item_picked+=1;
              mvwprintw(win,location_y,location_x," ");
          }
          elif(snakex==location_x) and (snakey==location_y){
              item_number-=1;
              mvwprintw(win,location_y,location_x," ");
          }
      }
      if gameOver==True{
        return item_picked;
      break
      }
  }
          
          
       
