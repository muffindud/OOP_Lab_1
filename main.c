#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <conio.h>
#elif __linux__
    #include <stdio.h>
    #include <termios.h>
    #include <unistd.h>

    int getch(void) { 
        struct termios oldattr, newattr; 
        int ch; 
        tcgetattr(STDIN_FILENO, &oldattr); 
        newattr = oldattr; 
        newattr.c_lflag &= ~(ICANON | ECHO); 
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr); 
        ch = getchar(); 
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); 
        return ch; 
    }
#endif

FILE *saveFile, *saveState;
int initialState[4][4];
int currentState[4][4];
int headIndex[2];
int result;

//todo: add move history variable here

//DONE
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

//DONE
bool check(){
    // Check if the game is solved
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++){
            if(currentState[i][j] != initialState[i][j]){
                game();
            }
        }
    }
    finish();
}

void newGame(){
    // Creates a new game
    headIndex[0] = 3;
    headIndex[1] = 3;
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++){
            currentState[i][j] = 4 * j + i + 1;
            initialState[i][j] = currentState[i][j];
        }
    }
    currentState[3][3] = 0;
    initialState[3][3] = 0;
    for(int i = 0; i < 100; i++){
        
    }
    game();
}

void randomiser(char dir){
    switch (dir){
    case 'd':
        currentState[headIndex[1]][headIndex[0]] = currentState[headIndex[1]][headIndex[0] + 1];
        currentState[headIndex[1]][headIndex[0] + 1] = 0;
        headIndex[0]++;
        break;
    case 'l':
        currentState[headIndex[1]][headIndex[0]] = currentState[headIndex[1] - 1][headIndex[0]];
        currentState[headIndex[1] - 1][headIndex[0]] = 0;
        headIndex[1]--;
        break;
    case 'u':
        currentState[headIndex[1]][headIndex[0]] = currentState[headIndex[1]][headIndex[0] - 1];
        currentState[headIndex[1]][headIndex[0] - 1] = 0;
        headIndex[0]--;
        break;
    case 'r':
        currentState[headIndex[1]][headIndex[0]] = currentState[headIndex[1] + 1][headIndex[0]];
        currentState[headIndex[1] + 1][headIndex[0]] = 0;
        headIndex[1]++;
        break;
    }
}

//DONE
void makeMove(char dir){
    // Moves the headIndex
    switch (dir){
    case 'd':
        currentState[headIndex[1]][headIndex[0]] = currentState[headIndex[1]][headIndex[0] + 1];
        currentState[headIndex[1]][headIndex[0] + 1] = 0;
        headIndex[0]++;
        break;
    case 'l':
        currentState[headIndex[1]][headIndex[0]] = currentState[headIndex[1] - 1][headIndex[0]];
        currentState[headIndex[1] - 1][headIndex[0]] = 0;
        headIndex[1]--;
        break;
    case 'u':
        currentState[headIndex[1]][headIndex[0]] = currentState[headIndex[1]][headIndex[0] - 1];
        currentState[headIndex[1]][headIndex[0] - 1] = 0;
        headIndex[0]--;
        break;
    case 'r':
        currentState[headIndex[1]][headIndex[0]] = currentState[headIndex[1] + 1][headIndex[0]];
        currentState[headIndex[1] + 1][headIndex[0]] = 0;
        headIndex[1]++;
        break;
    }
    if(headIndex[0] == 3 && headIndex[1] == 3){
        check();
    }
    else{
        game();
    }
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


//todo: implement finish screen
void finish(){
    // The finish screen
    clrscr();
    printf("Congrats! You solved the puzzle\n");
    printf("--Press any button to return to the main menu--\n");
    getch();
    mainMenu();
}

//DONE
// The main game
void game(){
    // The game takes place here
    clrscr();

    printf("%d %d\n", headIndex[0], headIndex[1]);
    printf("%d\n", result);

    // handle the output
    // main game output
    printf("\u2554\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2557\n");
    for(int j = 0; j < 4; j++){
        if(j != 0){
            // Borders
            if(headIndex[0] == j - 1){
                switch(headIndex[1]){
                    case 0:
                        printf("\u2560\u2550\u21E9\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2563\n");
                        break;
                    case 1:
                        printf("\u2560\u2550\u2550\u2550\u256C\u2550\u21E9\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2563\n");
                        break;
                    case 2:
                        printf("\u2560\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u21E9\u2550\u256C\u2550\u2550\u2550\u2563\n");
                        break;
                    case 3:
                        printf("\u2560\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u21E9\u2550\u2563\n");
                        break;
                }
            }
            else if(headIndex[0] == j){
                switch(headIndex[1]){
                    case 0:
                        printf("\u2560\u2550\u21E7\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2563\n");
                        break;
                    case 1:
                        printf("\u2560\u2550\u2550\u2550\u256C\u2550\u21E7\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2563\n");
                        break;
                    case 2:
                        printf("\u2560\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u21E7\u2550\u256C\u2550\u2550\u2550\u2563\n");
                        break;
                    case 3:
                        printf("\u2560\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u21E7\u2550\u2563\n");
                        break;
                }
            }
            else{
                printf("\u2560\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2563\n");
            }
        }
        // Numbers
        printf("\u2551   \u2551   \u2551   \u2551   \u2551\n");
        for(int i = 0; i < 4; i++){
            if(currentState[i][j] == 0 && i != 0){
                printf("\u21E6   ");
            }
            else if(currentState[i - 1][j] == 0 && i != 0){
                printf("\u21E8 %2d", currentState[i][j]);
            }
            else if(currentState[i][j] == 0){
                printf("\u2551   ");
            }
            else{
                printf("\u2551 %2d", currentState[i][j]);
            }
        }
        printf("\u2551\n");
        printf("\u2551   \u2551   \u2551   \u2551   \u2551\n");
    }
    printf("\u255A\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u255D\n");

    //menu
    if(headIndex[0] != 0){
        printf("[w]: Up ");
    }
    if(headIndex[1] != 3){
       printf("[d]: Right "); 
    }
    if(headIndex[0] != 3){
        printf("[s]: Down ");
    }
    if(headIndex[1] != 0){
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
                if(headIndex[0] != 0){
                    // UP
                    makeMove('u');
                }
                break;
            case 'd':
                if(headIndex[1] != 3){
                    // RIGHT
                    makeMove('r');
                }
                break;
            case 's':
                if(headIndex[0] != 3){
                    // DOWN
                    makeMove('d');
                }
                break;
            case 'a':
                if(headIndex[1] != 0){
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
        game();
    }
}

int main(){
    mainMenu();
}