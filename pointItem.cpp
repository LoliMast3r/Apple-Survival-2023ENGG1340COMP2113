#include <iostream>
#include <string>
#include <fstream>
#include <ncurses.h>
#include <ctime>
#include <cstdlib>
using namespace std;

//get the real time in sec as a unit

int currentSec(){
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    return elapsed_seconds
}

int locationGenerator(){
      for(int i = 25; i < 50; i++){
        int x = rand() % N;
        int y = rand() % N;

        std::cout << "x:" << x << " y:" << y << "\n\n";
    }
}



void printItem(){
  srand(time(0));
  while (currentSec()/10)==0{
  
  
  }
  
  }
