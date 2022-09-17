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
int currentState[4][4];
int headIndex[2];
//todo: add move history variable here

// // BECAUSE WINDOWS F**KING SUCKS!
// #ifdef _WIN32
//     system("CHCP 65001");
// #endif

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

    game();
}

void newGame(){
    // Creates a new game
    headIndex[0] = 3;
    headIndex[1] = 3;
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++){
            currentState[i][j] = 4 * j + i + 1;
        }
    }
    currentState[3][3] = 0;
    int seed = time(NULL);
    for(int i = 0; i < 100; i++){
        //todo: pattern randomiser here
    }
    game();
}

void makeMove(char dir){
    // Moves the headIndex
    switch (dir){
    case 'u':
        currentState[headIndex[1]][headIndex[0]] = currentState[headIndex[1]][headIndex[0] + 1];
        currentState[headIndex[1]][headIndex[0] + 1] = 0;
        headIndex[0]++;
        break;
    case 'r':
        currentState[headIndex[1]][headIndex[0]] = currentState[headIndex[1] - 1][headIndex[0]];
        currentState[headIndex[1] - 1][headIndex[0]] = 0;
        headIndex[1]--;
        break;
    case 'd':
        currentState[headIndex[1]][headIndex[0]] = currentState[headIndex[1]][headIndex[0] - 1];
        currentState[headIndex[1]][headIndex[0] - 1] = 0;
        headIndex[0]--;
        break;
    case 'l':
        currentState[headIndex[1]][headIndex[0]] = currentState[headIndex[1] + 1][headIndex[0]];
        currentState[headIndex[1] + 1][headIndex[0]] = 0;
        headIndex[1]++;
        break;
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
    // main game output
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 203, 205, 205, 205, 187);
    for(int j = 0; j < 4; j++){
        if(j != 0){
            // Borders
            if(headIndex[0] == j - 1){
                switch(headIndex[1]){
                    case 0:
                        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 24, 205, 206, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185);
                        break;
                    case 1:
                        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 24, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185);
                        break;
                    case 2:
                        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 24, 205, 206, 205, 205, 205, 185);
                        break;
                    case 3:
                        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 206, 205, 24, 205, 185);
                        break;
                }
            }
            else if(headIndex[0] == j){
                switch(headIndex[1]){
                    case 0:
                        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 25, 205, 206, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185);
                        break;
                    case 1:
                        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 25, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185);
                        break;
                    case 2:
                        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 25, 205, 206, 205, 205, 205, 185);
                        break;
                    case 3:
                        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 206, 205, 25, 205, 185);
                        break;
                }
            }
            else{
                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205, 185);
            }
        }
        // Numbers
        printf("%c   %c   %c   %c   %c\n", 186, 186, 186, 186, 186);
        for(int i = 0; i < 4; i++){
            if(currentState[i][j] == 0 && i != 0){
                printf(">   ");
            }
            else if(currentState[i - 1][j] == 0 && i != 0){
                printf("< %2d", currentState[i][j]);
            }
            else if(currentState[i][j] == 0){
                printf("%c   ", 186);
            }
            else{
                printf("%c %2d", 186, currentState[i][j]);
            }
        }
        printf("%c\n", 186);
        printf("%c   %c   %c   %c   %c\n", 186, 186, 186, 186, 186);
    }
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 202, 205, 205, 205, 188);

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
                    makeMove('u');
                }
                break;
            case 'd':
                if(headIndex[1] != 0){
                    // RIGHT
                    makeMove('r');
                }
                break;
            case 's':
                if(headIndex[0] != 0){
                    // DOWN
                    makeMove('d');
                }
                break;
            case 'a':
                if(headIndex[1] != 3){
                    // LEFT
                    makeMove('l');
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