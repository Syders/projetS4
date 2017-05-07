#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hex.h"
#define EMPTY 'e'
#define BLACK 'b'
#define WHITE 'w'
#define CHECKEDBLACK 'B'
#define CHECKEDWHITE 'W'
#define MAXSIZE 20
struct board {
    int size; /*the size of the board*/
    char * board; /*the board itself*/
};

//Yes
Board newBoard(int size) {
    /*Initializes a board
        size is the size of the board
        Returns the created board
    */
    Board b = malloc(sizeof(struct board));
	b->board = (char*)malloc(sizeof(char));
    b->size = size;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
			b->board =(char*) realloc(b->board,sizeof(char));
			b->board[i*size+j] = EMPTY;
		}
	}
    return b;
}
//YES
bool turnIsValid(Board b, int l, int c) {
    /*Checks whether the turn is valid
        b is the board of the game
        l is the line of the desired location
        c is the column of the desired location
        Returns 1 if it's valid, 0 if it's not
    */
    return b->board[l*b->size+c] == EMPTY;
}
//YES
Board newTurn(Board b, bool player, int l, int c) {
    /*Allows to play a turn (ASSUMES THE TURN IS VALID)
        b is the board of the game
        player is 0 if black, 1 if white
        l is the line of the location
        c is the column of the location
        Returns the board with the turn played
    */
    if (player)
        b->board[l*b->size+c] = WHITE;
    else
        b->board[l*b->size+c] = BLACK;
    return b;
}
//X
bool checkBlackWinner(Board b, int l, int c) {
    /*Recursive function that checks whether a plot is a black one that hasn't
    been checked previously and calls iself with the coordinates of the
    neighbouring plots
        b is the board of the game
        l is the line of the plot being checked
        c is the column of the plot being checked
    */
    if ((l == -1) || (c == -1) || (l == b->size))
        return 0;
    if (c == b->size)
        return 1;
    if (b->board[l*b->size+c] == BLACK)
        b->board[l*b->size+c] = CHECKEDBLACK;
    else
        return 0;
    if (checkBlackWinner(b,l+1,c))
        return 1;
    if (checkBlackWinner(b,l-1,c))
        return 1;
    if (checkBlackWinner(b,l,c+1))
        return 1;
    if (checkBlackWinner(b,l,c-1))
        return 1;
    if (checkBlackWinner(b,l+1,c-1))
        return 1;
    if (checkBlackWinner(b,l-1,c+1))
        return 1;
    return 0;
}
//X
bool checkWhiteWinner(Board b, int l, int c) {
    /*Recursive function that checks whether a plot is a white one that hasn't
    been checked previously and calls iself with the coordinates of the
    neighbouring plots
        b is the board of the game
        l is the line of the plot being checked
        c is the column of the plot being checked
    */
    if ((l == -1) || (c == -1) || (c == b->size))
        return 0;
    if (l == b->size)
        return 1;
    if (b->board[l*b->size+c] == WHITE)
        b->board[l*b->size+c] = CHECKEDWHITE;
    else
        return 0;
    if (checkWhiteWinner(b,l+1,c))
        return 1;
    if (checkWhiteWinner(b,l-1,c))
        return 1;
    if (checkWhiteWinner(b,l,c+1))
        return 1;
    if (checkWhiteWinner(b,l,c-1))
        return 1;
    if (checkWhiteWinner(b,l+1,c-1))
        return 1;
    if (checkWhiteWinner(b,l-1,c+1))
        return 1;
    return 0;
}
//X
Board cleanBoard(Board b) {
    /*Returns to a normal state all the "checked" plots
        b is the board to clean
        Returns the cleaned board
    */
    for (int i = 0; i < b->size; i++){
        for (int j = 0; j < b->size; j++) {
            if (b->board[i*b->size+j] == CHECKEDBLACK)
                b->board[i*b->size+j] = BLACK;
            if (b->board[i*b->size+j] == CHECKEDWHITE)
                b->board[i*b->size+j] = WHITE;
        }
	}
    return b;
}
//Yes,checkBlackWinner,checkWhiteWinner,cleanBoard
char checkWinner(Board b) {
    /*Checks who is the winner (if there is one)
        b is the board of the game
        Returns EMPTY if no winner, BLACK or WHITE if there is one
    */
    for (int i = 0; i < b->size; i++){
        if (checkBlackWinner(b,i,0)) {
            b = cleanBoard(b);
            return BLACK;
        }
	}
    for (int i = 0; i < b->size; i++){
        if (checkWhiteWinner(b,0,i)) {
            b = cleanBoard(b);
            return WHITE;
        }
	}
    b = cleanBoard(b);
    return EMPTY;
}
//Yes
void newGame(char* name, int size) {
    /*Creates a new game
        name is the name of the file
        size is the size of the board
    */
    FILE *f = fopen(name,"wt");
    fprintf(f,"\\hex\n\\dim %d\n\\board\n",size);
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++)
            fputc('.',f);
        fputc('\n',f);
    }
    fputs("\\endboard\n\\game\n\\endgame\n\\endhex",f);
    fclose(f);
}
//X
bool isValid(char* name, int l, int c) {
    /*Checks whether the turn is valid
        name is the name of the game (the game has already been created)
        l is the line of the desired location
        c is the column of the desired location
        Returns 1 if it's valid, 0 if it's not
    */
	int size;
    FILE *f = fopen(name,"rt");
    char str[MAXSIZE]; /*it's a dump to store unnecessary lines*/
    int ch; /*the value of the desired location*/
    fgets(str, MAXSIZE, f); /*reading of the line "\hex"*/
    fscanf(f,"\\dim %d\n",&size);
    if((l >= size) || (c >= size)) {
        fclose(f);
        return 0;
    }
    fgets(str, MAXSIZE, f); /*reading of the line "\board"*/
    for (int i = 0; i < l; i++)
        fgets(str, MAXSIZE, f); /*reading of the ith line of the board*/
    for (int i = 0; i < c; i++)
        fgetc(f); /*reading of the ith character of the lth line of the board*/
    ch = fgetc(f);
    fclose(f);
    /*printf("%c\n",ch);*/ /*used for tests*/
    if (ch != '.')
        return 0;
    return 1;
}
// Yes,is Valid
bool turn(char* name, bool player, int l, int c) {
    /*Allows to play a turn
        name is the name of the game (the game has already been created)
        player is 0 if black, 1 if white
        l is the line of the desired location
        c is the column of the desired location
        Returns 1 if the turn is valid, 0 if it's not
    */
    if (! isValid(name, l, c))
        return 0;
    char str[MAXSIZE]; /*it's a dump to store unnecessary line*/
    FILE *f = fopen(name,"r+t");
    char ch; /*the character to be printed*/
    rewind(f);
    for (int i = 0; i < 3; i++)
        fgets(str, MAXSIZE, f); /*reading of the first three lines*/
    for (int i = 0; i < l; i++)
        fgets(str, MAXSIZE, f); /*reading of the ith line of the board*/
    for (int i = 0; i < c; i++)
        fgetc(f); /*reading of the ith character of the lth line of the board*/
    if (player) /*white*/
        ch = 'o';
    else /*black*/
        ch = '*';
    fputc(ch,f);
    fseek(f,-16,SEEK_END); /*the cursor is placed at the beginning of the last but one line*/
    fprintf(f,"\\play %c %d %d\n\\endgame\n\\endhex",ch,c,l);
    fclose(f);
    return 1;
}
//Test
int main() {
    /*It's a test program*/
    Board b = newBoard(4);
    printf("%d\n",turnIsValid(b,0,3));
    b = newTurn(b,0,3,0);
    printf("%d\n",turnIsValid(b,3,0));
    b = newTurn(b,0,3,1);
    b = newTurn(b,0,3,2);
    b = newTurn(b,0,3,3);
    printf("%c\n",checkWinner(b));
    printf("%d\n",isValid("jeu",3,4,b->size));
    return 0;
}
