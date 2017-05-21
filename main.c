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
    printf("HEX Version 1.0 \n\nCommencer une partie[Taper 1]\nCommencer une partie avec l'ia[Taper 2]\n");
    if((savePre=savePresent("jeu.txt"))){
            printf("Charger une partie déja commencer(sans ia)[Taper 3]\n");
    }
    printf("Quitter le jeu[Taper 4]\n");
    int choix=5;
    if(savePre){
        while(choix<1 || choix>4)scanf("%d",&choix);
    }else{
        while(choix<1 || choix>4){
            scanf("%d",&choix);
            if(choix==3)choix=5;
        }
    }
    return choix;
}


int game(Board b, Joueur jAct, Joueur j1, Joueur j2, bool iaActive){
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
        //Si le coup est annulé
        if(annule==0){
            printf("Coup Annulé\n");
        }
        if((iaActive && jAct->pionDuJoueur==j1->pionDuJoueur) || (!iaActive)){
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
                    if(!iaActive)turn("jeu.txt",(jAct->pionDuJoueur==WHITE),ligne,colonne);
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
        }else{
            b=AITurn(b,j2->pionDuJoueur==WHITE);
            joueurG=checkWinner(b);
            jAct=j1;
        }
        
    }while(joueurG==EMPTY && termine==0);
    //If a winner is designed
    system("clear");
    if(iaActive)affichageTableau(b);
    if(joueurG==j1->pionDuJoueur) {
        printf("\n\n\nLe gagnant est le joueur 1\n");
    }
    else if (joueurG==j2->pionDuJoueur){
        printf("\n\n\nLe gagnant est le joueur 2\n");
    }
    //If not a finish game
    if(termine==1){
        printf("\nVoulez-vous sauvegarder la partie? [1 pour oui,0 pour non]\n");
        termine=3;
        while(termine<0 || termine>1)scanf("%d",&termine);
        if(termine==0)execlp("rm","rm","jeu.txt",NULL);
    }else if(termine==0 && !iaActive){
        // else clean the save if it's finish
        execlp("rm","rm","jeu.txt",NULL);
    }
    
    //Free the mallocs
    deleteInformation(j1);
    deleteInformation(j2);
    deleteInformation(jAct);
    freeBoard(b);
    //Demand if they want to return to main menu
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
    bool iaActive=false;
    int retour=1;
    int choix;
    while(retour==1){
        choix=mainMenu();
        if(choix>=1 && choix<=3){
            j1=creerInformation(1);
            j2=creerInformation(2);
            joueurAct=creerInformation(3);
            if(choix==1 || choix==2){
                b=startNewGame(&j1,&j2);
                if(choix==1){
                    joueurAct=j1;
                    newGame("jeu.txt",b->size);
                }else{
                    system("clear");
                    iaActive=true;
                    printf("\nVoulez-vous que l'ia commence?[1 pour oui, 0 pour non]\n");
                    while(choix<0 || choix>1)scanf("%d",&choix);
                    joueurAct=(choix==1)?j2:j1;
                }
            }else if(choix==3){
                b=loadGame("jeu.txt",&joueurAct,&j1,&j2);
            }
                
            retour=game(b,joueurAct,j1,j2,iaActive);
        }else
            retour=0;
    }
    return 0;
}