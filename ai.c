#include <stdbool.h>
#include "hex.h"
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
    /*player: 1 = white; 0 = black*/
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
