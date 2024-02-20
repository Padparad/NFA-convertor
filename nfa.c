//
//  main.c
//  test_project1
//
//  Created by Lucy Lin on 9/21/22.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>



struct NFA {
    int transitionTable[100][100][100];
    int state[100];
};

//function 1: ending in GS
//generate the transition table
struct NFA* GStransition () {
    struct NFA* table  = (struct NFA*) malloc(sizeof(struct NFA));
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            for (int k = 0; k < 2; k++) {
                table->transitionTable[i][j][k] = 0;
            }
        }
    }
    table->transitionTable[0][0][1] = 1;
    table->transitionTable[1][0][1] = 1;
    table->transitionTable[1][1][1] = 2;
    table->transitionTable[2][0][1] = 1;
    
    return table;
}

//according to the input character, return the column index on the transition table
int GSgetJ (char input) {
    switch(input) {
        case 'G':
            return 0;
            break;
        case 'g':
            return 0;
            break;
        case 'S':
            return 1;
            break;
        case 's':
            return 1;
            break;
        default:
            return 2;
    }
}

//according to the current state, return the row index on the transition table
int GSgetI (int* state) {
    int b = state[1];
    if (b == 0)
        return 0;
    else if (b == 1)
        return 1;
    else
        return 2;
}

//check if the accepting state 2 is contains in the final state set
bool GSaccept (int finalState[]) {
    bool accept = false;
    for (int i = 0; i < 2; i++) {
        if (finalState[i] == 2)
            accept = true;
    }
    return accept;
}

//run function for end_in_gs
bool endInGS (struct NFA* gs, char input[]) {
    //initialize state to {0,0}
    gs->state[0] = gs->state[1] = 0;
    int i;
    int j;
    int index = 0;
    while (input[index] != NULL) {
        //get row and column index then get the state set of this position
        i = GSgetI(gs->state);
        j = GSgetJ(input[index]);
        for (int n = 0; n < 2; n++) {
            gs->state[n] = gs->transitionTable[i][j][n];
        }
        index++;
    }
    //check if final state is accepted or rejected
    bool accept = GSaccept(gs->state);
    return accept;
}

//function 2: containing MAS
//generate the transition table
struct NFA* MAStransition () {
    struct NFA* table  = (struct NFA*) malloc(sizeof(struct NFA));
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 3; k++) {
                table->transitionTable[i][j][k] = 0;
            }
        }
    }
    table->transitionTable[0][0][1] = table->transitionTable[1][0][1] = table->transitionTable[2][0][1] = table->transitionTable[3][0][1] = table->transitionTable[4][0][1] = table->transitionTable[5][0][1] = 1;
    table->transitionTable[1][1][1] = table->transitionTable[4][1][1] = 2;
    table->transitionTable[2][2][1] = table->transitionTable[3][0][2] = table->transitionTable[3][1][1] = table->transitionTable[3][2][1] = table->transitionTable[3][3][1] = table->transitionTable[4][0][2] = table->transitionTable[4][1][2] = table->transitionTable[4][2][1] = table->transitionTable[4][3][1] = table->transitionTable[5][0][2] = table->transitionTable[5][1][1] = table->transitionTable[5][2][1] = table->transitionTable[5][3][1] = 3;
    
    return table;
}

//according to current state, get row index of the transition table
int MASgetI (int* state) {
    int b = state[1];
    int c = state[2];
    if (b == 0)
        //{0,0,0}
        return 0;
    else if (b == 1) {
        if (c == 0)
            //{0,1,0}
            return 1;
        else
            //{0,1,4}
            return 4;
    }
    else if (b == 2) {
        if (c == 0)
            //{0,2,0}
            return 2;
        else
            //{0,2,3}
            return 5;
    }
    else {
        //{0,3,0}
        return 3;
    }
}

//according to the input, get column index of the transition table
int MASgetJ (char input) {
    switch(input) {
        case 'M':
            return 0;
            break;
        case 'm':
            return 0;
            break;
        case 'A':
            return 1;
            break;
        case 'a':
            return 1;
            break;
        case 'S':
            return 2;
            break;
        case 's':
            return 2;
            break;
        default:
            return 3;
    }
}

//check if accepting state 3 is included in the final state set
bool MASaccept (int finalState[]) {
    bool accept = false;
    for (int i = 0; i < 3; i++) {
        if (finalState[i] == 3)
            accept = true;
    }
    return accept;
}

//run function for contain_mas
bool containsMAS (struct NFA* mas, char input[]) {
    mas->state[0] = mas->state[1] = mas->state[2] = 0;
    int i;
    int j;
    int index = 0;
    bool accept = false;
    while (input[index] != NULL) {
        i = MASgetI(mas->state);
        j = MASgetJ(input[index]);
        for (int n = 0; n < 2; n++) {
            mas->state[n] = mas->transitionTable[i][j][n];
        }
        accept = MASaccept(mas->state);
        if(accept) {
            return accept;
        }
        index++;
    }
    return accept;
}

//function 3: not an anagram of "codebreaker"
//generate the transition table
struct NFA* CodebreakerTransition () {
    struct NFA* table  = (struct NFA*) malloc(sizeof(struct NFA));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 5; k++) {
                table->transitionTable[i][j][k] = 0;
            }
        }
    }
    
    for (int i = 0; i < 10; i++) {
        table->transitionTable[i][0][1] = 3;
        table->transitionTable[i][1][1] = 6;
        table->transitionTable[i][2][1] = 1;
    }
    
    table->transitionTable[2][0][2] = table->transitionTable[3][0][2] = table->transitionTable[4][0][2] = table->transitionTable[7][0][2] = 4;
    table->transitionTable[4][0][3] = table->transitionTable[7][0][3] = 5;
    
    table->transitionTable[3][1][2] = table->transitionTable[6][1][2] = table->transitionTable[8][1][2] = table->transitionTable[9][1][2] = 7;
    table->transitionTable[6][1][3] = table->transitionTable[8][1][3] = table->transitionTable[9][1][3] = 8;
    table->transitionTable[8][1][4] = table->transitionTable[9][1][4] = 9;
    
    table->transitionTable[1][2][2] = table->transitionTable[5][2][2] = 2;
    
    return table;
}

//according to current state, return row index on the transition table
int CodebreakerGetI (int* state) {
    int a = state[1];
    int b = state[2];
    int c = state[3];
    int d = state[4];
    if (a == 0)
        return 0;
    else if (a == 1) {
        if (b == 0)
            return 1;
        else
            return 5;
    } else if (a == 3) {
        if (b == 0)
            return 2;
        else
            if (c == 0)
                return 4;
            else
                return 7;
    } else {
        //a == 6
        if (b == 0)
            return 3;
        else {//b == 7
            if (c == 0)
                return 6;
            else {
                if (d == 0)
                    return 8;
                else
                    return 9;
            }
        }
    }
}

//according to the input, return the column index of the transition table
int CodebreakerGetJ (char input) {
    switch(input) {
        case 'R':
            return 0;
            break;
        case 'r':
            return 0;
            break;
        case 'E':
            return 1;
            break;
        case 'e':
            return 1;
            break;
        case 'A':
            return 2;
            break;
        case 'a':
            return 2;
            break;
        case 'B':
            return 2;
            break;
        case 'b':
            return 2;
            break;
        case 'C':
            return 2;
            break;
        case 'c':
            return 2;
            break;
        case 'D':
            return 2;
            break;
        case 'd':
            return 2;
            break;
        case 'K':
            return 2;
            break;
        case 'k':
            return 2;
            break;
        case 'O':
            return 2;
            break;
        case 'o':
            return 2;
            break;
        default:
            return 100;
            break;
    }
}

//check if the accecting states 2 and 5 and 9 is included in the final state set
bool CodebreakerAccept (int finalState[]) {
    bool accept = false;
    for (int i = 0; i < 5; i++) {
        if ((finalState[i] == 2) || (finalState[i] == 5) || (finalState[i] == 9))
            accept = true;
    }
    return accept;
}

//check if the input is a letter contained in "codebreaker"
bool CodebreakerValid (char input) {
    switch(input) {
        case 'R':
            return true;
            break;
        case 'r':
            return true;
            break;
        case 'E':
            return true;
            break;
        case 'e':
            return true;
            break;
        case 'A':
            return true;
            break;
        case 'a':
            return true;
            break;
        case 'B':
            return true;
            break;
        case 'b':
            return true;
            break;
        case 'C':
            return true;
            break;
        case 'c':
            return true;
            break;
        case 'D':
            return true;
            break;
        case 'd':
            return true;
            break;
        case 'K':
            return true;
            break;
        case 'k':
            return true;
            break;
        case 'O':
            return true;
            break;
        case 'o':
            return true;
            break;
        default:
            return false;
            break;
    }
}

//run function for codebreaker
bool CodebreakerAnagram (struct NFA* cb, char input[]) {
    cb->state[0] = cb->state[1] = cb->state[2] = cb->state[3] = cb->state[4] = 0;
    int i;
    int j;
    int index = 0;
    bool accept = false;
    while (input[index] != NULL) {
        //if input is not a letter contained in "codebreaker", it can be accepted since it connot be an
        //anagram of "codebreaker"
        if (CodebreakerValid(input[index])) {
            i = CodebreakerGetI(cb->state);
            j = CodebreakerGetJ(input[index]);
            for (int n = 0; n < 5; n++) {
                cb->state[n] = cb->transitionTable[i][j][n];
            }
            index++;
        } else {
            return accept = true;
        }
    }
    accept = CodebreakerAccept(cb->state);
    return accept;
}

//functions for main class performance
//check if the input is "quit"
bool quit(char input[]) {
    int index = 0;
    char* quit = "quit";
    if (strcmp(input, quit) == 0)
        return true;
    else
        return false;
}

//return "true" or "false" as string according to the boolean value
char* TF(bool input) {
    if (input) {
        return "true";
    } else {
        return "false";
    }
}

int main(int argc, const char * argv[]) {

    
    printf("CSC173 Project 1 by George Ferguson\n");
    
    
    printf("\nTesting NFA that ends with \"gs\"...\n");
    char userInput[100];
    struct NFA* GStable = GStransition();
    bool accept;
    while(true) {
        printf("\tEnter an input (\"quit\" to quit): ");
        scanf("%s", userInput);
        if(quit(userInput)) {
            break;
        }
        accept = endInGS(GStable, userInput);
        printf("\tResult for input \"%s\": %s\n", userInput, TF(accept));
        
    }
    
    
    printf("\nTesting NFA that contains with \"mas\"...\n");
    char userInput2[100];
    struct NFA* MAStable = MAStransition();
    bool accept2;
    while(true) {
        printf("\tEnter an input (\"quit\" to quit): ");
        scanf("%s", userInput2);
        if(quit(userInput2)) {
            break;
        }
        accept2 = containsMAS(MAStable, userInput2);
        printf("\tResult for input \"%s\": %s\n", userInput2, TF(accept2));
        
    }
    
    printf("\nTesting NFA that is not an anagram of \"codebreaker\"...\n");
    char userInput3[100];
    struct NFA* CBtable = CodebreakerTransition();
    bool accept3;
    while(true) {
        printf("\tEnter an input (\"quit\" to quit): ");
        scanf("%s", userInput3);
        if(quit(userInput3)) {
            break;
        }
        accept3 = CodebreakerAnagram(CBtable, userInput3);
        printf("\tResult for input \"%s\": %s\n", userInput3, TF(accept3));
        
    }
    
    return 0;
}
