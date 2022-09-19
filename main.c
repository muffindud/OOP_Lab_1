#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#ifdef _WIN32
    #pragma execution_character_set( "utf-8" )
    #include <conio.h>
#elif __linux__
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

FILE *saveState;
int initialState[4][4];
int currentState[4][4];
int headIndex[2];
int moves, length;
char ch;
char *moveHistory;

void clrscr(){
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}

void delSave(){
    #ifdef _WIN32
        system("del \"save-state.txt\"");
    #elif __linux__
        system("rm save-state.txt");
    #endif
}

// Game functionalities
void check(){
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
    moveHistory = (char*)malloc(0 * sizeof(char));
    moves = 0;
    length = 0;
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

    clrscr();
    printf("Generating game...\n");

    long int seed = time(NULL);
    for(int i = 0; i < 1000; i++){
        srand(seed);
        seed = rand();
            switch(seed % 4){
                case 0:
                    if(headIndex[0] != 3){
                        randomiser('d');
                    }
                    break;
                case 1:
                    if(headIndex[1] != 0){
                        randomiser('l');
                    }
                    break;
                case 2:
                    if(headIndex[0] != 0){
                        randomiser('u');
                    }
                    break;
                case 3:
                    if(headIndex[1] != 3){
                        randomiser('r');
                    }
                    break;
            }
        }
    game();
}

void randomiser(char dir){
    // Move tiles without checking
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

void undo(){
    // Undoes the move
    moves--;
    switch (moveHistory[moves]){
        case 'd':
            randomiser('u');
            break;
        case 'l':
            randomiser('r');
            break;
        case 'u':
            randomiser('d');
            break;
        case 'r':
            randomiser('l');
            break;
        }
    game();
}

void redo(){
    // Redoes the move
    randomiser(moveHistory[moves]);
    moves++;
    game();
}

void makeMove(char dir){
    // Moves the headIndex with check on 3, 3
    moves++;
    length = moves;
    moveHistory = (char*)realloc(moveHistory, moves * sizeof(char));
    moveHistory[moves - 1] = dir;
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
    if(fopen("save-state.txt", "r") != NULL){
        printf("[c]: Continue\n");
    }
    printf("[n]: New game\n");
    printf("[q]: Quit the game\n");
    while(true){
        char command = tolower((char)getch());
        switch(command){
            case 'c':
                if(fopen("save-state.txt", "r") != NULL){
                    saveState = fopen("save-state.txt", "r");
                    for(int j = 0; j < 4; j++){
                        for(int i = 0; i < 4; i++){
                            fscanf(saveState, "%d%c", &currentState[i][j], ch);
                        }
                    }
                    fscanf(saveState, "%d%c%d", &headIndex[0], ch, &headIndex[1]);
                    fclose(saveState);
                    game();
                }
                break;
            case 'n':
                newGame();
                break;
            case 'q':
                exit(0);
                break;
            default:
                break;
        }
    }
}

void finish(){
    // The finish screen
    clrscr();
    free(moveHistory);
    delSave();
    printf("Congrats! You solved the puzzle\n");
    printf("--Press any button to return to the main menu--\n");
    getch();
    mainMenu();
}

// The main game
void game(){
    // The game takes place here
    clrscr();

    // handle the output
    // main game output
    printf("\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n");
    for(int j = 0; j < 4; j++){
        if(j != 0){
            // Borders
            if(headIndex[0] == j - 1){
                switch(headIndex[1]){
                    case 0:
                        printf("\u2560\u2550\u2550\u21E9\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
                        break;
                    case 1:
                        printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u21E9\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
                        break;
                    case 2:
                        printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u21E9\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
                        break;
                    case 3:
                        printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u21E9\u2550\u2550\u2550\u2563\n");
                        break;
                }
            }
            else if(headIndex[0] == j){
                switch(headIndex[1]){
                    case 0:
                        printf("\u2560\u2550\u2550\u21E7\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
                        break;
                    case 1:
                        printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u21E7\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
                        break;
                    case 2:
                        printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u21E7\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
                        break;
                    case 3:
                        printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u21E7\u2550\u2550\u2550\u2563\n");
                        break;
                }
            }
            else{
                printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
            }
        }
        // Numbers
        printf("\u2551      \u2551      \u2551      \u2551      \u2551\n");
        for(int i = 0; i < 4; i++){
            if(currentState[i][j] == 0 && i != 0){
                printf("\u21E6      ");
            }
            else if(currentState[i - 1][j] == 0 && i != 0){
                printf("\u21E8  %2d  ", currentState[i][j]);
            }
            else if(currentState[i][j] == 0){
                printf("\u2551      ");
            }
            else{
                printf("\u2551  %2d  ", currentState[i][j]);
            }
        }
        printf("\u2551\n");
        printf("\u2551      \u2551      \u2551      \u2551      \u2551\n");
    }
    printf("\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n");

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
    if(moves != 0){
        printf("[b]: Undo\n");
    }
    if(moves < length){
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
                free(moveHistory);
                saveState = fopen("save-state.txt", "w+");
                for(int j = 0; j < 4; j++){
                    for(int i = 0; i < 4; i++){
                        fprintf(saveState, "%d ", currentState[i][j]);
                    }
                }
                fprintf(saveState, "%d %d", headIndex[0], headIndex[1]);
                fclose(saveState);
                mainMenu();
                break;
            case 'r':
                // Restart game
                free(moveHistory);
                newGame();
            case 'b':
                // Undo move
                if(moves != 0){
                    undo();
                }
                break;
            case 'n':
                // Redo move
                if(moves < length){
                    redo();
                }
                break;
        }
        game();
    }
}

int main(){
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 4; i++){
            initialState[i][j] = 4 * j + i + 1;
        }
    }
    initialState[3][3] = 0;
    mainMenu();
}