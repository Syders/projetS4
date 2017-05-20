#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "hex.h"


//Le premier menu
int principalMenu(){
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

//Le fonctionnement du jeu
void game(Board b, Joueur jAct, Joueur j1, Joueur j2){
    char joueurG;
    int annule;
    int ligne,colonne;
    int termine;
    //printf("\nPion J1= %c,dernierCoupJoue= %s",j1->pionDuJoueur,j1->dernierCoupJoue);
    //printf("\nPion J2= %c,dernierCoupJoue= %s",j2->pionDuJoueur,j2->dernierCoupJoue);
    
    do{
        system("clear");
        if(annule==0){
            printf("Coup Annulé\n\n");
        }
        affichageInformation(jAct);
        affichageTableau(b);
        printf("\nJoueur %d a vous jouer:",jAct->noJoueur);
        do{
            caseJoue(b->size,&ligne,&colonne);
            if(!turnIsValid(b,ligne,colonne))
                printf("\nCase non valide.Recommencer.");
        }while(!turnIsValid(b,ligne,colonne));
        b=newTurn(b,(jAct->pionDuJoueur==WHITE),ligne,colonne);
        system("clear");
        affichageTableau(b);
        if((joueurG=checkWinner(b))==EMPTY){
            annule=3;
            printf("\nEtes-vous sûre de votre coup? [1 pour oui,0 pour non]");
            while(annule<0 || annule>1)scanf("%d",&annule);
            if(annule==0){
                b=annulerCoup(b,ligne,colonne);
            }else{
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
            printf("\nVoulez-vous arrêter la partie [1 pour oui, 0 pour non]");
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
        printf("\f\nVoulez-vous sauvegarder la partie? [1 pour oui,0 pour non]");
        termine=3;
        while(termine<0 || termine>1)scanf("%d",&termine);
        if(termine==0)execlp("rm","rm","jeu.txt",NULL);
    }else{
        execlp("rm","rm","jeu.txt",NULL);
    }
    
    //Free the mallocs
    deleteInformation(j1);
    deleteInformation(j2);
    deleteInformation(jAct);
    freeBoard(b);
}


int main() {
    Joueur j1;
    Joueur j2;
    Joueur joueurAct;
    Board b;
    j1=creerInformation(1);
    j2=creerInformation(2);
    joueurAct=creerInformation(3);
    int choix=principalMenu();
    if(choix==1){
        b=startNewGame(&j1,&j2);
        joueurAct=j1;
        newGame("jeu.txt",b->size);
    }else if(choix==2)
        b=loadGame("jeu.txt",&joueurAct,&j1,&j2);
    else
        return 0;
    game(b,joueurAct,j1,j2);
    
    return 0;
}