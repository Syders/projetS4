#include <jni.h>
#include "hex.h"
#include "HEX_src_jeu_InterfaceAvecC.h"

JNIEXPORT jint JNICALL Java_HEX_src_jeu_InterfaceAvecC_choix_1mode
  (JNIEnv *env, jobject obj){
    int choix=-1;
    while(choix<1 && choix>3){
        scanf("%d",&choix);
        if(choix==2 && !savePresent("jeu"))choix=4;
    }
    return choix;
  }
JNIEXPORT jobject JNICALL Java_HEX_src_jeu_InterfaceAvecC_saveDisponible
  (JNIEnv *env, jobject obj){
        return savePresent("jeu");
  }
JNIEXPORT jchar JNICALL Java_HEX_src_jeu_InterfaceAvecC_creer_1information_1joueur_11
  (JNIEnv *env, jobject obj){
    char pion='.';
    while(pion!='*' && pion!='o'){
        scanf("%c",&pion);
    }
    return pion;
  }
JNIEXPORT jint JNICALL Java_HEX_src_jeu_InterfaceAvecC_choixTaille
  (JNIEnv *env, jobject obj){
    int taille=2;
    while(taille<=2)scanf("%d",&taille);
    return taille;
  }
JNIEXPORT jcharArray JNICALL Java_HEX_src_jeu_InterfaceAvecC_initialisationTab
  (JNIEnv *env, jobject obj, jint size){
    Board board= newBoard(size);
    return board_take(board);
  }
JNIEXPORT jint JNICALL Java_HEX_src_jeu_InterfaceAvecC_loadSaveSize
  (JNIEnv *env, jobject obj){
    int size=loadGameSize("jeu");
    return size;
  }
JNIEXPORT jcharArray JNICALL Java_HEX_src_jeu_InterfaceAvecC_loadSaveTab
  (JNIEnv * env, jobject obj){
    char * tab=loadGameTab("jeu");
    return tab;
  }
JNIEXPORT jint JNICALL Java_HEX_src_jeu_InterfaceAvecC_action_1joueur
  (JNIEnv * env, jobject obj, jcharArray tab, jobject joueur, jint size){
    printf("\nLigne[Entre 1 et %d]: ",size);
    int ligne=-1;
    while(ligne<1 && ligne>size)scanf("%d",&ligne);
    ligne--;
    printf("\nColonne[Entre 1 et %d)]: ",size");
    int colonne=-1;
    while(colonne<1 && colonne>size)scanf("%d",&colonne);
    colonne--;
    return ligne*size+colonne;
  }
JNIEXPORT jobject JNICALL Java_HEX_src_jeu_InterfaceAvecC_question_1quitter
  (JNIEnv * env, jobject obj){
    printf("\nAppuyer sur 1 pour quitter le jeu, 0 pour continuer ");
    int quitter=-1;
    while(quitter<0 && quitter>1)scanf("%d",&quitter);
  }
JNIEXPORT jchar JNICALL Java_HEX_src_jeu_InterfaceAvecC_gagnant
  (JNIEnv * env, jobject obj, jcharArray tab, jint size){
    return checkWinner(tab,size);
  }
JNIEXPORT void JNICALL Java_HEX_src_jeu_InterfaceAvecC_saveQuestion
  (JNIEnv * env, jobject obj, jcharArray tab, jint size){
    printf("\nVoulez-vous sauvegarder votre partie?[1 pour oui, 0 pour non] ");
    int save=-1;
    while(save<0 && save>1)scanf("%d",&save);
    if(save)saveGame("jeu",tab,size);
  }
