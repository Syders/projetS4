#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hex.h"
#define EMPTY '.'
#define BLACK '*'
#define WHITE 'o'
#define CHECKEDBLACK 'B'
#define CHECKEDWHITE 'W'
#define MAXSIZE 20
struct board {
    int size; /*the size of the board*/
    char * board; /*the board itself*/
};
//Fonction test

void affichageTableau(Board b){
		for(int i=0;i<b->size;i++){
			printf("W ");
		}
		printf("W/B\n");
		for(int i=0;i<b->size;i++){
            for(int k=0;k<=i;k++)printf(" ");
			for(int j=0;j<b->size;j++){
				if(j==0)printf("B ");
				//printf(" * ");
				printf("%c ",b->board[i*b->size+j]);
			}
			printf("B\n");
			if(i==b->size-1){
                for(int k=0;k<=i+1;k++)printf(" ");
			}
		}
		printf("B/W ");
		for(int i=0;i<b->size-1;i++){
			printf("W ");
		}
		printf("W\n * pour les noirs (B) et o pour les blancs (W) \n");
	}
//Yes
Board newBoard(int size) {
    /*Initializes a board
        size is the size of the board
        Returns the created board
    */
    Board b = malloc(sizeof(struct board));
	b->board = (char*)malloc(sizeof(char) * size * size);
    b->size = size;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
			//b->board =(char*) realloc(b->board,sizeof(char));
			b->board[i*size+j] = EMPTY;
		}
	}
    return b;
}
//YES
bool turnIsValid(char * b,int size, int l, int c) {
    /*Checks whether the turn is valid
        b is the board of the game
        l is the line of the desired location
        c is the column of the desired location
        Returns 1 if it's valid, 0 if it's not
    */
    return b[l*size+c] == EMPTY;
}
//YES
char * newTurn(char * b,int size, bool player, int l, int c) {
    /*Allows to play a turn (ASSUMES THE TURN IS VALID)
        b is the board of the game
        player is 0 if black, 1 if white
        l is the line of the location
        c is the column of the location
        Returns the board with the turn played
    */
    if (player)
        b[l*size+c] = WHITE;
    else
        b[l*size+c] = BLACK;
    return b;
}
//X
bool checkBlackWinner(char * b,int size, int l, int c) {
    /*Recursive function that checks whether a plot is a black one that hasn't
    been checked previously and calls iself with the coordinates of the
    neighbouring plots
        b is the board of the game
        l is the line of the plot being checked
        c is the column of the plot being checked
    */
    if ((l == -1) || (c == -1) || (l == size))
        return 0;
    if (c == size)
        return 1;
    if (b[l*size+c] == BLACK)
        b[l*size+c] = CHECKEDBLACK;
    else
        return 0;
    if (checkBlackWinner(b,size,l+1,c))
        return 1;
    if (checkBlackWinner(b,size,l-1,c))
        return 1;
    if (checkBlackWinner(b,size,l,c+1))
        return 1;
    if (checkBlackWinner(b,size,l,c-1))
        return 1;
    if (checkBlackWinner(b,size,l+1,c-1))
        return 1;
    if (checkBlackWinner(b,size,l-1,c+1))
        return 1;
    return 0;
}
//X
bool checkWhiteWinner(char * b,int size, int l, int c) {
    /*Recursive function that checks whether a plot is a white one that hasn't
    been checked previously and calls iself with the coordinates of the
    neighbouring plots
        b is the board of the game
        l is the line of the plot being checked
        c is the column of the plot being checked
    */
    if ((l == -1) || (c == -1) || (c == size))
        return 0;
    if (l == size)
        return 1;
    if (b[l*size+c] == WHITE)
        b[l*size+c] = CHECKEDWHITE;
    else
        return 0;
    if (checkWhiteWinner(b,size,l+1,c))
        return 1;
    if (checkWhiteWinner(b,size,l-1,c))
        return 1;
    if (checkWhiteWinner(b,size,l,c+1))
        return 1;
    if (checkWhiteWinner(b,size,l,c-1))
        return 1;
    if (checkWhiteWinner(b,size,l+1,c-1))
        return 1;
    if (checkWhiteWinner(b,size,l-1,c+1))
        return 1;
    return 0;
}
//X
char * cleanBoard(char * b,int size) {
    /*Returns to a normal state all the "checked" plots
        b is the board to clean
        Returns the cleaned board
    */
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++) {
            if (b[i*size+j] == CHECKEDBLACK)
                b[i*size+j] = BLACK;
            if (b[i*size+j] == CHECKEDWHITE)
                b[i*size+j] = WHITE;
        }
	}
    return b;
}
//Yes,checkBlackWinner,checkWhiteWinner,cleanBoard
char checkWinner(char * b,int size) {
    /*Checks who is the winner (if there is one)
        b is the board of the game
        Returns EMPTY if no winner, BLACK or WHITE if there is one
    */
    for (int i = 0; i < size; i++){
        if (checkBlackWinner(b,size,i,0)) {
            b = cleanBoard(b,size);
            return BLACK;
        }
	}
    for (int i = 0; i < size; i++){
        if (checkWhiteWinner(b,size,0,i)) {
            b = cleanBoard(b,size);
            return WHITE;
        }
	}
    b = cleanBoard(b,size);
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
    FILE *f = fopen(name,"rt");
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
void saveGame(char * name,char * b, int size){

    FILE *f = fopen(name,"wt");
    fprintf(f,"\\hex\n\\dim %d\n\\board\n",size);
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++)
            fprintf(f,"%c ",b[i*size+j]);
        fputc('\n',f);
    }
    fputs("\\endboard\n\\game\n\\endgame\n\\endhex",f);
    fclose(f);
}

bool savePresent(char * name){
    return (fopen(name,"wt")!=EOF);
}

int loadGameSize(char * name){
	int size;
    FILE *f = fopen(name,"rt");
    char str[MAXSIZE]; /*it's a dump to store unnecessary lines*/
    fgets(str, MAXSIZE, f); /*reading of the line "\hex"*/
    fscanf(f,"\\dim %d\n",&size);
	return size;
}

char * loadGameTab(char* name) {
    /* Creates a board based on the savefile
        name is the name of the game (the game has already been created)
        Returns the board corresponding to the game
    */
    int size;
    int ch; /*the character to store the value of a tile*/
    FILE *f = fopen(name,"rt");
    char str[MAXSIZE]; /*it's a dump to store unnecessary lines*/
    fgets(str, MAXSIZE, f); /*reading of the line "\hex"*/
    fscanf(f,"\\dim %d\n",&size);
    Board b = newBoard(size);
    fgets(str, MAXSIZE, f); /*reading of the line "\board"*/
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            ch = fgetc(f);
            while(ch==' ' || ch=='\n')ch = fgetc(f);
            if (ch == '*')
                b->board[i*b->size+j] = BLACK;
            else if (ch == 'o')
                b->board[i*b->size+j] = WHITE;
            else if (ch== '.')
                b->board[i*b->size+j] = EMPTY;
        }
        printf("\n");
    }
    fclose(f);
    return b->board;
}


/*test
int main() {
    It's a test program
    Board b = newBoard(4);
    affichageTableau(b);
    printf("%d\n",turnIsValid(b,0,3));
    b = newTurn(b,1,0,3);
    printf("%d\n",turnIsValid(b,3,0));
    b = newTurn(b,1,1,3);
    b = newTurn(b,1,2,3);
    b = newTurn(b,1,3,3);
    printf("%c\n",checkWinner(b));
     affichageTableau(b);
     printf("\n");
    saveGame("jeu",b->board,b->size);
    //newGame("jeu",10);
    b = loadGame("jeu");
    affichageTableau(b);
    //printf("%s\n",b->board);
    //printf("%d\n",isValid("jeu",3,4));
    return 0;
}*/
