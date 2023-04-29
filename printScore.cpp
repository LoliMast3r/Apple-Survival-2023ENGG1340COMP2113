#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

void printArt(string filename, int highScore, int score, int width) {
    int i = 0;
    int numHighScore = width - to_string(highScore).length();
    int numScore = width - to_string(score).length();
    string line = "";
    ifstream inFile;
    inFile.open(filename.c_str());
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            i++;
            if (i == 6) {
                cout << setw(numHighScore / 2 + to_string(highScore).length()) << highScore << endl;
            }
            else if (i == 12) {
                cout << setw(numScore / 2 + to_string(score).length()) << score << endl;
            }
            else {
                cout << line << endl;
            }
        }
    }
    inFile.close();
}

//This only prints the txt file specified by me
//In this case, "gameOver.txt"
//When implementing this code, I suggest using if conditions
int main() {
    string filename = "score.txt";
    printArt(filename, 10000, 10, 50);
    return 0;
}