#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hex.h"
#define COLOR_WHITE "\x1b[37m"
#define COLOR_BLACK "\x1b[30;1m"
#define RESET_COLOR "\x1b[0m"
#define CHECKEDBLACK 'B'
#define CHECKEDWHITE 'W'
#define MAXSIZE 20

//AI section

int minimax (Board b, bool player) {
    /*player: 1 = white; 0 = black*/
    if (checkWinner(b) == BLACK)
        return 1;
    if (checkWinner(b) == WHITE)
        return -1;
    int current, score;
    if (player) //white
        score = 1;
    else //black
        score = -1;
    for (int i = 0; i < b->size; i++)
        for (int j = 0; j < b->size; j++)
            if (turnIsValid(b,i,j)) {
                b = newTurn(b,player,i,j);
                current = minimax(b,!player);
                if ((player && (current < score)) || (!player && (current > score)))
                    score = current;
                b = annulerCoup(b,i,j);
            }
    return score;
}

Board AITurn (Board b, bool player) {
    /*AI player: 1 = white; 0 = black*/
    int current, score, l, c;
    l = c = -1;
    if (player) //white
        score = 1;
    else //black
        score = -1;
    for (int i = 0; i < b->size; i++)
        for (int j = 0; j < b->size; j++)
            if (turnIsValid(b,i,j)) {
                if (l == -1) { //initialisation at a valid value
                    l = i;
                    c = j;
                }
                b = newTurn(b,player,i,j);
                current = minimax(b,!player);
                if ((player && (current < score)) || (!player && (current > score))) {
                    score = current;
                    l = i;
                    c = j;
                }
                b = annulerCoup(b,i,j);
            }
    return newTurn(b,player,l,c);
}

//End section

Joueur creerInformation(int noJoueur){
    /*
     * Create the information for the player
     */
    Joueur j=(Joueur)malloc(sizeof(struct _joueur));
    j->noJoueur=noJoueur;
    j->dernierCoupJoue=(char *)malloc(sizeof(char)*10);
    sprintf(j->dernierCoupJoue," ");
    j->noTour=1;
    j->pionDuJoueur='.';
    return j;
}

void deleteInformation(Joueur j){
    //Free the player malloc
    free(j);
}

void affichageInformation(Joueur jActuelle){
    /*
     * Print the information from the player
     */
    printf("\n\nJoueur n°%d avec le pion",jActuelle->noJoueur); 
    if(jActuelle->pionDuJoueur==BLACK){
        printf(COLOR_BLACK " X" RESET_COLOR "\n");
    }else{
        printf(COLOR_WHITE " O" RESET_COLOR "\n");
    }
    
    printf("Tour n°%d\nDernier Coup joué:%s\n",jActuelle->noTour,jActuelle->dernierCoupJoue);
}

void affichageTableau(Board b){
    /*
     * Print the board 
     * whith the player color
     */
                printf("\n\n");
		for(int i=0;i<b->size;i++){
			printf(COLOR_WHITE "W " RESET_COLOR);
		}
		printf(COLOR_WHITE "W" RESET_COLOR "/" COLOR_BLACK "B" RESET_COLOR "\n");
		for(int i=0;i<b->size;i++){
            for(int k=0;k<=i;k++)printf(" ");
			for(int j=0;j<b->size;j++){
				if(j==0)printf(COLOR_BLACK "B " RESET_COLOR);
				//printf(" * ");
				//printf("%c ",b->board[i*b->size+j]);
                                //Les couleurs sont affichés à l'écran
                                if(b->board[i*b->size+j]!=EMPTY){
                                    if(b->board[i*b->size+j]==WHITE){
                                        printf(COLOR_WHITE "O " RESET_COLOR,WHITE);
                                    }else{
                                        printf(COLOR_BLACK "X " RESET_COLOR,BLACK);
                                    }
                                }else
                                    printf("  ");
			}
			printf(COLOR_BLACK "B" RESET_COLOR "\n");
			if(i==b->size-1){
                for(int k=0;k<=i+1;k++)printf(" ");
			}
		}
		printf(COLOR_BLACK "B" RESET_COLOR "/" COLOR_WHITE "W " RESET_COLOR);
		for(int i=0;i<b->size-1;i++){
			printf(COLOR_WHITE "W " RESET_COLOR);
		}
		printf(COLOR_WHITE "W" RESET_COLOR "\n" COLOR_BLACK " X" RESET_COLOR " pour les noirs (B) et " COLOR_WHITE "O" RESET_COLOR " pour les blancs (W) \n");
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

void freeBoard(Board b){
    //Free the malloc from the board
    free(b->board);
    free(b);
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


Board startNewGame(Joueur * j1, Joueur * j2){
/*                                      
 * Demarre une nouvelle partie         
 * et demande au joueur 1 de choisir   
 * son pion                            
 */
    system("clear");
    printf("\f\nChoisissez la taille du plateau [superieur à 2]");
    int taille=1;
    while(taille<=2)scanf("%d",&taille);
    Board b=newBoard(taille);
    printf("\nJoueur 1 vous voulez quel pion? [soit *='"COLOR_BLACK "X" RESET_COLOR "' ou o='" COLOR_WHITE "O" RESET_COLOR "'] (Joueur 2 aura l'autre pion)\n");
    char pion='.';
    while(pion!=BLACK && pion!=WHITE)scanf("%c",&pion);
    (*j1)->pionDuJoueur=pion;
    (*j2)->pionDuJoueur=(pion==BLACK) ? WHITE: BLACK;
    return b;
}

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
    fprintf(f,"\\play %c %d %d\n\\endgame\n\\endhex",ch,l+1,c+1);
    fclose(f);
    return 1;
}

bool savePresent(char * name){
    /*
     * Return if the save is present
     */
    return (fopen(name,"rt")!=NULL);
}


Board loadGame(char* name,Joueur * joueurAct,Joueur * j1, Joueur * j2) {
    /* 
     * Creates a board based on the savefile
     *   name is the name of the game (the game has already been created)
     *   Returns the board  corresponding to the game 
     *   the last player who have played,
     *   
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
    }
    //Who have played last? && what are the information
    char saveline[MAXSIZE];//Knowing the line where is the information
    char endgame[MAXSIZE]="\\endgame\n";//The last line of the game
    for(int i=0;i<3;i++)fgets(str, MAXSIZE, f);//endboard/endhexS
    bool first=true,jOne=true;//jOne pour compter le nombre de coup joué
    while(strcmp(str,endgame)){
        fgets(str, MAXSIZE, f);
        //The first player is always J1
        if(first){
            if(str[6]==WHITE){
                (*j1)->pionDuJoueur=WHITE;
                (*j2)->pionDuJoueur=BLACK;
            }else{
                (*j1)->pionDuJoueur=BLACK;
                (*j2)->pionDuJoueur=WHITE; 
            }
            first=false;
        }

        //Know the last move from the player
        if(strcmp(str,endgame)){
            strcpy(saveline,str);
            if(jOne){
                (*j1)->noTour++;
                sprintf((*j1)->dernierCoupJoue,"%s",strpbrk(str,"1234567890"));
            }else{
                (*j2)->noTour++;
                sprintf((*j2)->dernierCoupJoue,"%s",strpbrk(str,"1234567890"));
        
        }
        }
        jOne=!jOne;
    }
    (*joueurAct)=saveline[6]==(*j1)->pionDuJoueur?(*j2):(*j1);//the color of the last player who have to played
    fclose(f);
    return b;
}

void caseJoue(int size,int * l, int * c){
    /*
     * Demand the player the move he want to do
     */
    printf("\nLigne:[compris entre 1 et %d]", size);
    int ligne,colonne;
    do{
        scanf("%d",&ligne);
    }while(ligne<1 || ligne>size);
    printf("\nColonne:[compris entre 1 et %d]", size);
    do{
        scanf("%d",&colonne);
    }while(colonne<1 || colonne>size);
    *l=ligne-1;
    *c=colonne-1;
}

Board annulerCoup(Board b, int l, int c){
    //The move become EMPTY to clean it
    b->board[l*b->size+c]=EMPTY;
    return b;
}




