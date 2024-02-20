#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define LONG 1024

struct myDFA{
    int numOfstate;
    int numOfchar;
    int state[10];//state set
    char characters[10];//alphabet
    int transTable[10][10];//transit set
    int startState; //initial state
    int endState;//end state
};

typedef struct myDFA DFA;

char strinput[LONG];
char *str=strinput;

void Creat_DFA_exact_ullman(DFA *dfa);
void Creat_DFA_begin_com(DFA *dfa);
void Creat_DFA_exact_three_3(DFA *dfa);
void Creat_DFA_even1_odd0(DFA *dfa);

void DFA_prt(DFA *dfa);
void output4dfa(DFA *dfa);

bool ullman(const char *string);
bool com(const char *string);
bool three_3s(const char *string);
bool even0s_odd1s(const char *string);

void DFA_repl();

int menu();

int main()
{

    DFA *dfa;
    int op;
    dfa=(DFA*)malloc(sizeof (DFA));
    printf("\nTesting DFA that recognizes exactly \"csc173\"by  ZHEYI FU...\n");

    while(1)
    { op=menu();

        switch(op)
        {
        case 1:
            output4dfa(dfa);
            break;
        case 2:
            DFA_repl();
            break;
        case 3:
            return 0;
        default:
           break;
        }

    }

   return 0;
}


//Allocate and return a new DFA containing the given number of states.


bool DFA_execute(DFA dfa, char *input)
{
    return true;
}
bool DFA_run(DFA dfa, char *input)
{
   return true;
}
void DFA_repl()
{
   int op,op1,op2,op3,op4;
   //char* number;
   printf(" Enter an input 1 for ullman 2 for com 3 for 3s 4 for 0and1 (\"quit\" to quit):");
   getchar();
   gets(strinput);
   //int len=strlen(strinput);

    if(strcmp(strinput,"1") ==0){
        printf("this is test for ullman, please enter your string (\"quit\" to quit):  \n");
        gets(strinput);
        while(strcmp(strinput,"quit")!=0) {
            printf("Testing DFA that recognizes exactly \"ullman\"...\n");
            op1 = false;
            op1 = ullman(str);
            if (op1 == true)
                printf("    Result for input \"%s\": true", strinput);
            else {
                printf("    Result for input \"%s\": false", strinput);
            }
            printf("\n    Enter an input (\"quit\" to quit):");
            gets(strinput);
        }
    }

    else if(strcmp(strinput,"2") ==0){
        printf("this is test for com, please enter your string (\"quit\" to quit):  \n");
        gets(strinput);
        while(strcmp(strinput,"quit")!=0) {
            printf("Testing DFA that recognizes stating with \"com\"...\n");
            op2 = false;
            op2=com(str);
            if (op2 == true)
                printf("    Result for input \"%s\": true", strinput);
            else {
                printf("    Result for input \"%s\": false", strinput);
            }
            printf("\n    Enter an input (\"quit\" to quit):");
            gets(strinput);
        }
    }

    else if(strcmp(strinput,"3") ==0){
        printf("this is test for 3s, please enter your string (\"quit\" to quit):  \n");
        gets(strinput);
        while(strcmp(strinput,"quit")!=0) {
            printf("Testing DFA that recognizes exactly three \"3s\"...\n");
            op3 = false;
            op3=three_3s(str);
            if (op3 == true)
                printf("    Result for input \"%s\": true", strinput);
            else {
                printf("    Result for input \"%s\": false", strinput);
            }
            printf("\n    Enter an input (\"quit\" to quit):");
            gets(strinput);
        }

    }

    else if(strcmp(strinput,"4") ==0){
        printf("this is test for 1 and 0, please enter your string (\"quit\" to quit):  \n");
        gets(strinput);
        while(strcmp(strinput,"quit")!=0) {
            printf("Testing DFA that recognizes  even number of 0’s and and odd number of 1’s...\n");
            op4 = false;
            op4=even0s_odd1s(str);
            if (op4 == true)
                printf("    Result for input \"%s\": true", strinput);
            else {
                printf("    Result for input \"%s\": false", strinput);
            }
            printf("\n    Enter an input (\"quit\" to quit):");
            gets(strinput);
        }
    }

    else{
        printf("invalid input, please try again.\n");
    }




}
//=============================================================
 void DFA_prt(DFA *dfa)
{

    int i,j;
    //for(i=0;i<dfa->numOfstate;i++)
        //printf("%d ",dfa->state[i]);
    //printf("\n");

    puts(dfa->characters);

     printf("   |  ");
    for(i=0;i<dfa->numOfchar;i++)
        printf("  %c  ",dfa->characters[i]);
    //printf("\'\\0\'");
    printf("\n-----------------------\n");

    for(i=0;i<dfa->numOfstate;i++)
    {
        printf("%3d|",dfa->state[i]);
        for(j=0;j<dfa->numOfchar;j++)
            printf("%5d",dfa->transTable[i][j]);
        printf("\n");
    }
   // printf("\n");
    //printf("%d ",dfa->startState);
   // printf("\n");
    //printf("%d",dfa->endState);
    printf("\n");
}

void output4dfa(DFA *dfa)
{
    Creat_DFA_exact_ullman(dfa);
    printf("DFA of ullman:\n");
    DFA_prt(dfa);

    Creat_DFA_begin_com(dfa);
    printf("DFA of com:\n");
    DFA_prt(dfa);

    Creat_DFA_exact_three_3(dfa);
    printf("DFA of exact three 3:\n");
    DFA_prt(dfa);

    Creat_DFA_even1_odd0(dfa);
    printf("DFA of even 1 ,odd 0:\n");
    DFA_prt(dfa);

}

//-------------------------------------

bool ullman(const char *string)
{
    //state 0:start
    //state 1:u
    //state 2:ul
    //state 3:ull
    //state 4:ullm
    //state 5:ullma
    //state 6:ullman
    //state 7:ullman'\0'accepted state

   int state = 0;

    if(string[0]=='u')
    {
        state=1;
        if(string[1]=='l')
        {
            state=2;
            if(string[2]=='l')
            {
                state=3;
                if(string[3]=='m')
                {
                    state=4;
                    if(string[4]=='a')
                    {
                        state=5;
                        if(string[5]=='n')
                        {
                            state=6;
                            if(string[6]=='\0')
                                state=7;
                            else
                                state=0;
                        }

                        else
                        state=0;
                    }
                    else
                        state=0;
                }
                else
                    state=0;
            }
            else
                state=0;
        }
        else
            state=0;
    }
    else
        state=0;


    if(state==7)
        return true;
    else
        return false;

}
bool com(const char *string)
{
    //state 0:start
    //state 1:c
    //state 2:co
    //state 3:com* ,accepted state
    /* state 0 */
    int state = 0;
	if(string[0]=='c')
	  state=1;  /* state 1 */
    else
        return false;
    if(state==1&&string[1]=='o')
        state=2;  /* state 2 */
    else
        return false;
    if(state==2&&string[2]=='m')
        {state=3;   return true;}   /* state 3,accepted */
    else
        return false;


}

bool three_3s(const char *string)
{
    //state 0:start , string is empety
    //state 1:*3
    //state 2:*3*3
    //state 3:*3*3*,accepted state
    /* state 0 */
    int state=0;
    int str_len=strlen(string);
    int i=0;

    for(i=0;i<str_len;i++)
    {
        if(string[i]!='3')
            continue;
        else
            state++;/* state 1,2,3 */
    }
    if(state==3)
        return true;
    else
        return false;
}


bool even0s_odd1s(const char *string)
{
     /* state 0 */
    int state=0;
    int str_len=strlen(string);
    int i=0;

    //state 0:0 number of 0,0 number of 1
    //state 1:even number of 0,even number of 1,include
    //state 2:odd number of 0,even number of 1
    //state 3:odd number of 0,odd number of 1
    //state 4:even number of 0,odd number of 1,accepted state

    for(i=0;i<str_len;i++)
    {
        switch(state)
        {
        case 0:
            if(str_len==0) //if string is empty,even 0,even 1,state 1
             {
                 state=1;
                 break;
             }
            if(str_len==1) //if string only has one char
                {if(string[i]=='0')
                    {state=2;break;} //state 2:odd 0,even 1
                  if(string[i]=='1')
                  {state=4;break;}   //state 4:even 0,odd 1
                }

        case 1:
            if(string[i]=='0')
                state=2;
            else if(string[i]=='1')
                state=4;
            break;
        case 2:
            if(string[i]=='0')
                state=1;
            else if(string[i]=='1')
                state=3;
            break;
        case 3:
            if(string[i]=='0')
                state=4;
            else if(string[i]=='1')
                state=2;
            break;
        case 4:
            if(string[i]=='0')
                state=3;
            else if(string[i]=='1')
                state=1;
            break;

        }

    }
    if(state==4)   /* state 4,accepted */
        return true;
    else
        return false;

}


//------------creat DFA----------------
void Creat_DFA_exact_ullman(DFA *dfa)
{
    int i,j;
    dfa->numOfstate=7;

    for(i=0;i<dfa->numOfstate;i++)
        dfa->state[i]=i; //state[10]={0,1,2,3,4,5,6,7};

    dfa->numOfchar=6;
    strcpy(dfa->characters,"ulman*");

    /*
    transTable[10][10]=
    {
      1 0 0 0 0 0
      0 2 0 0 0 0
      0 3 0 0 0 0
      0 0 4 0 0 0
      0 0 0 5 0 0
      0 0 0 0 6 0
      0 0 0 0 0 7
      0 0 0 0 0 0
    };
    */

    for(i=0;i<dfa->numOfstate;i++)
        for(j=0;j<dfa->numOfchar;j++)
        {   dfa->transTable[i][j]=0;
        }
     dfa->transTable[0][0]=1;
     dfa->transTable[1][1]=2;
     dfa->transTable[2][1]=3;
     dfa->transTable[3][2]=4;
     dfa->transTable[4][3]=5;
     dfa->transTable[5][4]=6;
     dfa->transTable[6][5]=7;


     dfa->startState=0;
     dfa->endState=7;

}

void Creat_DFA_begin_com(DFA *dfa)
{
    int i,j;
    dfa->numOfstate=4;

    for(i=0;i<dfa->numOfstate;i++)
        dfa->state[i]=i; //state[10]={0,1,2,3};

    dfa->numOfchar=3;
    strcpy(dfa->characters,"com");

    /*
    transTable[10][10]=
    {
      1 0 0
      0 2 0
      0 0 3
    };
    */

    for(i=0;i<dfa->numOfstate;i++)
        for(j=0;j<dfa->numOfchar;j++)
        {   dfa->transTable[i][j]=0;
        }
     dfa->transTable[0][0]=1;
     dfa->transTable[1][1]=2;
     dfa->transTable[2][2]=3;


     dfa->startState=0;
     dfa->endState=3;

}
void Creat_DFA_exact_three_3(DFA *dfa)
{
    int i;
    dfa->numOfstate=4;

    for(i=0;i<dfa->numOfstate;i++)
        dfa->state[i]=i; //state[10]={0,1,2,3};

    dfa->numOfchar=2;
    strcpy(dfa->characters,"3*");

    /*
    transTable[10][10]=
       { {1,0},
         {2,0},
         {3,0}} ,
        };
    */

     dfa->transTable[0][0]=1; dfa->transTable[0][1]=0;
     dfa->transTable[1][0]=2; dfa->transTable[1][1]=2;
     dfa->transTable[2][0]=3; dfa->transTable[2][1]=3;


     dfa->startState=0;
     dfa->endState=3;
}
void Creat_DFA_even1_odd0(DFA *dfa)
{
     int i,j;
    dfa->numOfstate=5;

    for(i=0;i<dfa->numOfstate;i++)
        dfa->state[i]=i; //state[10]={0,1,2,3,4};

    dfa->numOfchar=2;
    strcpy(dfa->characters,"01");

    /*
    transTable[10][10]=
       {  {1,4},
          {2,4},
          {1,3},
          {4,2},
          {3,1}
        };
    */
     for(i=0;i<dfa->numOfstate;i++)
        for(j=0;j<dfa->numOfchar;j++)
        {   dfa->transTable[i][j]=0;
        }

     dfa->transTable[0][0]=1; dfa->transTable[0][1]=4;
     dfa->transTable[1][0]=2; dfa->transTable[1][1]=4;
     dfa->transTable[2][0]=1; dfa->transTable[2][1]=3;
     dfa->transTable[3][0]=4; dfa->transTable[3][1]=2;
     dfa->transTable[4][0]=3; dfa->transTable[4][1]=1;


     dfa->startState=0;
     dfa->endState=4;

}
int menu()
{
    int op;
    printf("--------------------------------\n");
    printf("|  1.  Print all 4 DFA.        |\n");
    printf("|  2.  test 4 strings.         |\n");
    printf("|  3.  quit.                   |\n");
    printf("--------------------------------");
    printf("\n please input 1 or 2 or 3:");
    scanf("%d",&op);
    return op;

}

