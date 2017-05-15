#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct board *Board;


Board newBoard(int size);
char * board_take(Board b);
bool turnIsValid(char * b,int size, int l, int c) ;
char * newTurn(char * b,int size, bool player, int l, int c);
char checkWinner(char * b,int size);
void newGame(char * name,int size);
bool turn(char* name, bool player, int l, int c);
int loadGameSize(char* name);
char * loadGameTab(char* name);
void saveGame(char * name,char * b, int size);
