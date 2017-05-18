#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "hex.h"


//Le premier menu
int principalMenu(){
    bool savePre;
    printf("HEX Version 1.0 \n\n Commencer une partie[Taper 1]\n");
    if((savePre=savePresent("jeu.txt"))){
            printf("Charger une partie déja commencer[Taper 2]\n");
    }
    printf("Quitter le jeu[Taper 3]\n");
    int choix=4;
    if(savePre){
        while(choix<1 && choix>3)scanf("%d",&choix);
    }else{
        while(choix!=1 && choix!=3)scanf("%d",&choix);
    }
    return choix;
}

//Le fonctionnement du jeu
void game(Board b, Joueur jAct, Joueur j1, Joueur j2){
    char joueurG;
    int annule;
    int ligne,colonne;
    int termine;
    do{
        printf("\nJoueur %d a vous jouer:",jAct->noJoueur);
        do{
            caseJoue(b->size,&ligne,&colonne);
        }while(!turnIsValid(b,ligne,colonne));
        b=newTurn(b,(jAct->pionDuJoueur==WHITE),ligne,colonne);
        affichageTableau(b);
        if(checkWinner(b)==EMPTY){
            printf("\nEtes-vous sûre de votre coup?[0 pour non, autre pour oui]");
            scanf("%d",&annule);
            if(annule==0){
            b=annulerCoup(b,ligne,colonne);
            printf("\n Coup annulé");
            }else{
                turn("jeu.txt",(jAct->pionDuJoueur==WHITE),ligne,colonne);
                if(jAct==j1){
                    sprintf(j1->dernierCoupJoue,"%d %d",ligne, colonne);
                    jAct=j2;
                }else{
                    sprintf(j2->dernierCoupJoue,"%d %d",ligne, colonne);
                    jAct=j1;
                }
            }
            printf("\nVoulez-vous arrêter la partie [1 pour oui, 0 pour non]");
            termine=3;
            while(termine<0 && termine>1)scanf("%d",&termine);
        }
    }while((annule==0 || (joueurG=checkWinner(b)==EMPTY)) && !termine);
    //If a winner is designed
    if(joueurG==j1->pionDuJoueur)
        printf("\n\nLe gagnant est le joueur 1");
    else if (joueurG==j2->pionDuJoueur)
        printf("\n\nLe gagnant est le joueur 2");
    //If not a finish game
    if(termine){
        printf("\n\nVoulez-vous sauvegarder la partie? [0 pour non,1 pour non]");
        termine=3;
        while(termine<0 && termine>1)scanf("%d",&termine);
        if(!termine)execlp("rm","rm","jeu.txt",NULL);
    }else{
        execlp("rm","rm","jeu.txt",NULL);
    }
    
    //Free the mallocs
    deleteInformation(j1);
    deleteInformation(j2);
    freeBoard(b);
}


int main() {
    Joueur j1;
    Joueur j2;
    Joueur joueurAct;
    Board b;
    j1=creerInformation(1);
    j2=creerInformation(2);
    int choix=principalMenu();
    if(choix==1){
        b=startNewGame(j1,j2);
        newGame("jeu.txt",b->size);
    }else if(choix==2)
        b=loadGame("jeu.txt",joueurAct,j1,j2);
    else
        return 0;
    game(b,joueurAct,j1,j2);
    
    return 0;
}