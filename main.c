#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "hex.h"


int mainMenu(){
    /*
     * The main menu demand to the players
     * if they want to start a new or
     * to load a game if it's a save
     * or to quit the game
     */
    bool savePre;
    printf("HEX Version 1.0 \n\nCommencer une partie[Taper 1]\n");
    if((savePre=savePresent("jeu.txt"))){
            printf("Charger une partie déja commencer[Taper 2]\n");
    }
    printf("Quitter le jeu[Taper 3]\n");
    int choix=4;
    if(savePre){
        while(choix<1 || choix>3)scanf("%d",&choix);
    }else{
        while(choix<1 || choix>3){
            scanf("%d",&choix);
            if(choix==2)choix=4;
        }
    }
    return choix;
}


int game(Board b, Joueur jAct, Joueur j1, Joueur j2){
    /*
     * The game call function in hex.c
     * and ask the player the move he want to do,
     * if he is sure of the move, if he want to quit,
     * if he want to save the game
     * The return to the main menu is active if the players want
     */
    char joueurG;
    int annule=3;
    int ligne,colonne;
    int termine;
    bool notValid;
    do{
        system("clear");
        //Si le c
        if(annule==0){
            printf("Coup Annulé\n");
        }
        affichageInformation(jAct);
        affichageTableau(b);
        printf("\nJoueur %d a vous jouer:",jAct->noJoueur);
        do{
            caseJoue(b->size,&ligne,&colonne);
            //The move can be no valid so he restart the move
            if((notValid=(!turnIsValid(b,ligne,colonne))))
                printf("\nCase non valide.Recommencer.");
        }while(notValid);
        //put the move on the board
        b=newTurn(b,(jAct->pionDuJoueur==WHITE),ligne,colonne);
        system("clear");
        affichageTableau(b);
        //If no winner now
        if((joueurG=checkWinner(b))==EMPTY){
            annule=3;
            //Demand if the player is sure of the move he made
            printf("\nEtes-vous sûre de votre coup? [1 pour oui,0 pour non]\n");
            while(annule<0 || annule>1)scanf("%d",&annule);
            // if not sure
            if(annule==0){
                //the move is clear from board
                b=annulerCoup(b,ligne,colonne);
            }else{
                //else the move is save for the actual player
                turn("jeu.txt",(jAct->pionDuJoueur==WHITE),ligne,colonne);
                if(jAct==j1){
                    sprintf(j1->dernierCoupJoue,"%d %d",ligne+1, colonne+1);
                    jAct=j2;
                }else{
                    sprintf(j2->dernierCoupJoue,"%d %d",ligne+1, colonne+1);
                    jAct=j1;
                }
            }
            system("clear");
            //demand the players if they want to stop
            printf("\nVoulez-vous arrêter la partie [1 pour oui, 0 pour non]\n");
            termine=3;
            while(termine<0 || termine>1)scanf("%d",&termine);
        }
    }while(joueurG==EMPTY && termine==0);
    //If a winner is designed
    if(joueurG==j1->pionDuJoueur) {
        printf("\n\nLe gagnant est le joueur 1\n");
    }
    else if (joueurG==j2->pionDuJoueur){
        printf("\n\nLe gagnant est le joueur 2\n");
    }
    //If not a finish game
    if(termine==1){
        printf("\nVoulez-vous sauvegarder la partie? [1 pour oui,0 pour non]\n");
        termine=3;
        while(termine<0 || termine>1)scanf("%d",&termine);
        if(termine==0)execlp("rm","rm","jeu.txt",NULL);
    }else{
        // else clean the save if it's finish
        execlp("rm","rm","jeu.txt",NULL);
    }
    
    //Free the mallocs
    deleteInformation(j1);
    deleteInformation(j2);
    deleteInformation(jAct);
    freeBoard(b);
    //Demand if they want to return to main menu
    system("clear");
    termine=3;
    printf("\n\nVoulez-vous retourner au menu principal? [1 pour oui,0 pour non]\n");
    while(termine<0 || termine>1)scanf("%d",&termine);
    return termine;
}


int main() {
    Joueur j1;
    Joueur j2;
    Joueur joueurAct;
    Board b;
    int retour=1;
    int choix;
    while(retour==1){
        choix=mainMenu();
        if(choix==1 || choix==2){
            j1=creerInformation(1);
            j2=creerInformation(2);
            joueurAct=creerInformation(3);
            if(choix==1){
                b=startNewGame(&j1,&j2);
                joueurAct=j1;
                newGame("jeu.txt",b->size);
            }else if(choix==2)
                b=loadGame("jeu.txt",&joueurAct,&j1,&j2);
            retour=game(b,joueurAct,j1,j2);
        }else
            retour=0;
    }
    return 0;
}