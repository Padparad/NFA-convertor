//
//  conversion.c
//  
//
//  Created by Lucy Lin on 9/23/22.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//structure of NFA containing 5-tuple definition
struct NFA {
    int numOfstate;
    int typesOfInput;
    int transitionTable[10][10][10];
    int state[10];
    int acceptingState;
};

//structure of DFA containing 5-tuple definition
struct DFA{
    int numOfstate;
    int typesOfInput;
    int transitionTable[10][10];
    int state[10];
    int acceptingState;
};

//constructing NFA transition table of ending in "gs"
struct NFA* GSinitialize () {
    struct NFA* endInGS  = (struct NFA*) malloc(sizeof(struct NFA));
    endInGS->numOfstate = 3;
    endInGS->typesOfInput = 3;
    endInGS->acceptingState = 2;
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            for (int k = 0; k < 2; k++) {
                endInGS->transitionTable[i][j][k] = 0;
            }
        }
    }
    endInGS->transitionTable[0][0][1] = 1;
    endInGS->transitionTable[1][0][1] = 1;
    endInGS->transitionTable[1][1][1] = 2;
    endInGS->transitionTable[2][0][1] = 1;
    
    return endInGS;
}

//contructing NFA transition table of containing "mas"
struct NFA* MASinitialize () {
    struct NFA* table  = (struct NFA*) malloc(sizeof(struct NFA));
    table->numOfstate = 4;
    table->typesOfInput = 4;
    table->acceptingState = 3;
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

//if NFA set contains non-zero element, return it for DFA; otherwise, return 0
int validState(int input[], int length) {
    int state = 0;
    for (int i = 0; i < length; i++) {
        if(input[i] != 0) {
            state = input[i];
        }
    }
    return state;
}

//conversion of endin in "gs"
struct DFA* GSconversion(struct NFA* endInGS) {
    struct DFA* convert = (struct DFA*) malloc(sizeof(struct DFA));
    convert->numOfstate = endInGS->numOfstate;
    convert->typesOfInput = endInGS->typesOfInput;
    convert->acceptingState = endInGS->acceptingState;
    int state[2];
    for (int i = 0; i < convert->numOfstate; i++) {
        for (int j = 0; j < convert->typesOfInput; j++) {
            for (int k = 0; k < 2; k++) {
                state[k] = endInGS->transitionTable[i][j][k];
                
            }
            convert->transitionTable[i][j] = validState(state, 2);
        }
    }
    return convert;
}
 
//conversion of containing "mas"
struct DFA* MASconversion(struct NFA* containsMAS) {
    struct DFA* convert = (struct DFA*) malloc(sizeof(struct DFA));
    convert->numOfstate = containsMAS->numOfstate;
    convert->typesOfInput = containsMAS->typesOfInput;
    convert->acceptingState = containsMAS->acceptingState;
    int state[3];
    for (int i = 0; i < convert->numOfstate; i++) {
        for (int j = 0; j < convert->typesOfInput; j++) {
            for (int k = 0; k < 3; k++) {
                state[k] = containsMAS->transitionTable[i][j][k];
                
            }
            convert->transitionTable[i][j] = validState(state, 3);
        }
        
    }
    return convert;
}

int main(int argc, const char * argv[]) {
    
    printf("Printing the transition table of NFA- end in 'gs'...\n");
    struct NFA* GStable = GSinitialize();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 2; k++) {
                printf("%d ", GStable->transitionTable[i][j][k]);
            }
            printf("\t");
        }
        printf("\n");
    }
    
    printf("Printing the transition table of DFA- end in 'gs'...\n");
    struct DFA* endInGS = GSconversion(GStable);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", endInGS->transitionTable[i][j]);
        }
        printf("\n");
    }
    
    printf("Printing the transition table of NFA- end containing 'mas'...\n");
    struct NFA* MAStable = MASinitialize();
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 3; k++) {
                printf("%d ", MAStable->transitionTable[i][j][k]);
            }
            printf("\t");
        }
        printf("\n");
    }
    
    printf("Printing the transition table of DFA- end containing 'mas'...\n");
    struct DFA* containsMAS = MASconversion(MAStable);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", containsMAS->transitionTable[i][j]);
        }
        printf("\n");
    }

     
}
