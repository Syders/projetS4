#include <stdio.h>
#include <stdbool.h>
#define MAX_SIZE 20
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
bool isValid(char* name, int c, int l) {
    /*Checks whether the turn is valid
        name is the name of the game (the game has already been created)
        c is the column of the desired location
        l is the line of the desired location
        Returns 1 if it's valid, 0 if it's not
    */
    int size;
    FILE *f = fopen(name,"rt");
    char str[MAX_SIZE]; /*it's a dump to store unnecessary lines*/
    int ch; /*the value of the desired location*/
    fgets(str, MAX_SIZE, f); /*reading of the line "\hex"*/
    fscanf(f,"\\dim %d\n",&size);
    if((c >= size) || (l>=size)) {
        fclose(f);
        return 0;
    }
    fgets(str, MAX_SIZE, f); /*reading of the line "\board"*/
    for (int i = 0; i < l; i++)
        fgets(str, MAX_SIZE, f); /*reading of the ith line of the board*/
    for (int i = 0; i < c; i++)
        fgetc(f); /*reading of the ith character of the lth line of the board*/
    ch = fgetc(f);
    fclose(f);
    /*printf("%c\n",ch);*/ /*used for tests*/
    if (ch != '.')
        return 0;
    return 1;
}
bool turn(char* name, bool player, int c, int l) {
    /*Allows to play a turn
        name is the name of the game (the game has already been created)
        player is 0 if black, 1 if white
        c is the column of the desired location
        l is the line of the desired location
        Returns 1 if the turn is valid, 0 if it's not
    */
    if (! isValid(name, c, l))
        return 0;
    char str[MAX_SIZE]; /*it's a dump to store unnecessary lines*/
    FILE *f = fopen(name,"r+t");
    char ch; /*the character to be printed*/
    rewind(f);
    for (int i = 0; i < 3; i++)
        fgets(str, MAX_SIZE, f); /*reading of the first three lines*/
    for (int i = 0; i < l; i++)
        fgets(str, MAX_SIZE, f); /*reading of the ith line of the board*/
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
int main() {
    /*It's a test program*/
    newGame("jeu",6);
    turn("jeu",0,3,4);
    turn("jeu",1,0,5);
    /*printf("%d\n",isValid("jeu",3,4));*/
    return 0;
}
