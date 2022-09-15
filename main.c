#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <conio.h>
#elif __linux__
    #include <curses.h> // requires libncursesw5-dev
#endif

FILE *saveFile, *saveState;
const int initialState[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
int headIndex[2] = {3, 3};

void clrscr(){
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}

// Game functionalities
void undo(){
    // Undoes the move
    clrscr();

}

void newGame(){
    // Creates a new game
    clrscr();   
    int currentState[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
    int seed = time(NULL);
    for(int i = 0; i < 100; i++){

    }
}

void check(){
    // Check if the puzzle is solved

}

void moveIndex(char direction){
    // Checks for walls and moves the head in the specified direction
    clrscr();

}

// Game menus
void mainMenu(){
    // Main menu
    clrscr();
    printf("Pick yout option:\n");
    if(/*check for game progress in saveState*/){
        printf("c: Continue\n");
    }
    printf("n: New game\n");
    if(/*check for save file(s)*/){
        printf("s: Pick a save file\n");
    }
}

void savesMenu(){
    // Save menu
    clrscr();

}

// The main game
void game(){
    // The game takes place here
    clrscr();

    // handle the output

    // handle the input
    if(getch() == (109 || 77)){
        // Return to main menu
        main();
    }
    else if(getch() == ( || )){

    }
    else if(getch() == ( || )){

    }
    else if(getch() == ( || )){

    }
    else if(getch() == ( || )){

    }

    if(headIndex[0] == 3 && headIndex[1] == 3){
        check();
    }
}

int main(){
    menu();
    if(getch() == (99 || 67) && /*saveState exists*/){
        //continue game
    }
    else if (getch() == (110 || 78)){
        newGame();
    }
    else if (getch() == (115 || 85) && /*save file(s) exist(s)*/){
        savesMenu();
    }
}