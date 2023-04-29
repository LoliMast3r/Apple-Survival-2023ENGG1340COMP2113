#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void printArt(string filename) {
    string line = "";
    ifstream inFile;
    inFile.open(filename.c_str());
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            cout << line << endl;
        }
    }
    inFile.close();
}

//This only prints the text file specified by me
//In this case, "gameOver.txt"
//Hence this is only an example to print the text file
int main() {
    string filename = "gameOver.txt";
    printArt(filename);
    return 0;
}