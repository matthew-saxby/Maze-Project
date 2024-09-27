//matthew saxby
//maze lab 7
//3 14 2024

// standard include files
#include <iostream>
#include <fstream>
#include <unistd.h>

// read this file to figure out how to set background color and unset background color  
#include "conio.cpp"

using namespace std;
using namespace conio;

//function prototypes
void loadMaze(char maze[10][10]);
void printMaze(char maze[10][10]);
bool canEscape(char maze[10][10], int row, int col);

//global variables
const int SLEEP_TIME  = 250000;
const char BEEN_HERE  = '!';
const char PATH       = '@';
const char WALL       = '#';
const char EXIT       = 'E';


int main (){
    //variables
    char maze[10][10];
    int inputRow = -1;
    int inputCol = -1;

    //load maze
    loadMaze(maze);

    cout << clrscr() << flush;

    //print maze
    printMaze(maze);

    //read inputs
    cout << "input row and col: ";
    cin >> inputRow
        >> inputCol;
    

    //can i escape?
    if(canEscape(maze, inputRow, inputCol)){
        cout << gotoRowCol(15,1) << "congratulations, you escaped!" << endl;
    }else{
        cout <<gotoRowCol(15,1) << "I'm sorry for your loss." << endl;
    }
    return 0;
}

void loadMaze(char maze[10][10]){

    //variables
    string fileName;
    ifstream mazeStream;

    //get filename
    cout << "enter file name: ";
    cin >> fileName;

    //open file
    mazeStream.open(fileName.c_str());

    while (cin && !mazeStream){

        cout << "Bad input" << endl;
        cout << "enter file name: ";
        cin >> fileName;

        mazeStream.open(fileName.c_str());
    }

    //read maze from file inot 2d array
    for (int row=0; row<10; row++){
        for(int col=0; col<10; col++){
            maze[row][col] = mazeStream.get();

        }
        (void)mazeStream.get();
    }
}

void printMaze(char maze[10][10]){
    cout << gotoRowCol(1,1)
    << " 0123456789" << endl;
    for (int row=0; row<10; row++){
        cout << row;
        for(int col=0; col<10; col++){
            cout << maze[row][col];
        }
        cout << endl;
    }
}

int erow;
int ecol;
bool canEscape(char maze[10][10], int row, int col){

    //base case
    if(row<0 || row>=10 || col<0 || col>=10){
        return false;
    }else if (maze[row][col] == BEEN_HERE){
        return false;
    }else if (maze[row][col] == WALL){
        return false;
    }else if (maze[row][col] == EXIT){
        erow = row;
        ecol = col;
        return true;
    }
    

    //precheck stuff
    
    maze[row][col] = BEEN_HERE;
    
    cout << gotoRowCol(row+2, col+2) << PATH << conio::bgColor(conio::YELLOW) << '\b' << flush;
    usleep(SLEEP_TIME);
    

    //recursive case
    bool escapePossible = canEscape(maze, row-1, col) ||
                          canEscape(maze, row, col-1) ||
                          canEscape(maze, row+1, col) ||
                          canEscape(maze, row, col+1);



    
                          
    if(escapePossible){
        cout << gotoRowCol(row+2, col+2) << PATH << conio::bgColor(conio::GREEN) << '\b' << flush;
        cout << gotoRowCol(erow+2, ecol+2) << EXIT << conio::bgColor(conio::GREEN) << '\b' << flush;
        return true;
    }else{
        cout << gotoRowCol(row+2, col+2) << PATH << conio::bgColor(conio::RED) << '\b' << flush;

        return false;
    }
}