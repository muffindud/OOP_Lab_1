#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <conio.h>
#elif __linux__
    #include <curses.h> // requires libncursesw5-dev
#endif

FILE *saveFile, *saveState;
const int initialState[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
int headIndex[2];
//todo: add move history variable here

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
    // (need move history)
    clrscr();

}

void newGame(){
    // Creates a new game
    clrscr();
    headIndex[0] = 3;
    headIndex[1] = 3;
    int currentState[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
    int seed = time(NULL);
    for(int i = 0; i < 100; i++){
        //todo: pattern randomiser here
    }
    game();
}

bool check(){
    // Check if the puzzle is solved
    printf("Check happened");
    //todo: check currentState to initialState
    return false;
}

// Game menus
void mainMenu(){
    // Main menu
    clrscr();
    printf("Pick yout option:\n");
    if(true/*check for game progress in saveState*/){ //todo: check for last save file
        printf("[c]: Continue\n");
    }
    printf("[n]: New game\n");
    printf("[s]: Pick a save file\n");
    while(true){
        char command = tolower((char)getch());
        switch(command){
            case 'c':
                //todo: pick last save file
                break;
            case 'n':
                newGame();
                break;
            case 's':
                savesMenu();
                break;
            default:
                break;
        }
    }
}

void savesMenu(){
    // Save menu
    clrscr();
    printf("Saves menu:\n");
    //todo: list all save instances here
}

// The main game
void game(){
    // The game takes place here
    clrscr();

    //debug head coords.
    printf("%d %d\n", headIndex[0], headIndex[1]);

    // handle the output
    //todo: display the game array: currentState

    //menu
    if(headIndex[0] != 3){
        printf("[w]: Up ");
    }
    if(headIndex[1] != 0){
       printf("[d]: Right "); 
    }
    if(headIndex[0] != 0){
        printf("[s]: Down ");
    }
    if(headIndex[1] != 3){
        printf("[a]: Left");
    }
    printf("\n");
    printf("[m]: Main menu\n");
    printf("[r]: Restart the game\n");
    if(true/*exists prev. move*/){ //todo: check history (need move history)
        printf("[b]: Undo\n");
    }
    if(true/*exists redo move*/){ //todo: chech history (need move history)
        printf("[n]: Redo\n");
    }

    // handle the input
    while(true){
        char command = tolower((char)getch());
        switch(command){
            case 'w':
                if(headIndex[0] != 3){
                    // UP
                    headIndex[0]++;
                }
                break;
            case 'd':
                if(headIndex[1] != 0){
                    // RIGHT
                    headIndex[1]--;
                }
                break;
            case 's':
                if(headIndex[0] != 0){
                    // DOWN
                    headIndex[0]--;
                }
                break;
            case 'a':
                if(headIndex[1] != 3){
                    // LEFT
                    headIndex[1]++;
                }
                break;
            case 'm':
                // Main menu
                mainMenu();
                break;
            case 'r':
                // Restart game
                newGame();
            case 'b':
                // Undo move
                if(true/*exsits prev. move*/){ //todo: check history (need history variable)
                    // Undo
                }
                break;
            case 'n':
                // Redo move
                if(true/*exists next move*/){ //todo: check history (need history variable)
                    // Redo
                }
                break;
        }
        if(headIndex[0] == 3 && headIndex[1] == 3){
            if(check()){
                // Finish screen
                //todo: implement finish screen
            }
        }
        game();
    }
}

int main(){
    mainMenu();
}