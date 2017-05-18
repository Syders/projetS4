#ifndef hex_h
#define hex_h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EMPTY '.'
#define BLACK '*'
#define WHITE 'o'


typedef struct board *Board;
typedef struct _joueur *Joueur;

Joueur creerInformation(int noJoueur);
void deleteInformation(Joueur j);
void affichageInformation(Joueur jActuelle);
void freeBoard(Board b);
Board startNewGame(Joueur j1, Joueur j2);
bool savePresent(char * name);
void affichageTableau(Board b);
Board newBoard(int size);
bool turnIsValid(Board b, int l, int c) ;
Board newTurn(Board b, bool player, int l, int c);
char checkWinner(Board b);
void newGame(char * name, int size);
bool turn(char* name, bool player, int l, int c);
Board loadGame(char* name,Joueur  joueurAct,Joueur  j1, Joueur  J2);
void caseJoue(int size,int * l, int * c);
Board annulerCoup(Board b, int l, int c);

#endif