#include <stdio.h> 
#include <time.h>

FILE *saveFile, *saveState;
const int initialState[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
int currentState[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};

void randomise(){
    //Creates a random move-set for the game

}

void check(){
    //Check if the puzzle is solved

}

void move(char direction){
    //Checks for walls and moves the head in the specified direction

}

void game(){

}

void menu(){
    //Main menu
    
}

void saves(){
    //Save menu

}

int main(){
    menu();
}