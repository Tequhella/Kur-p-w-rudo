/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : main.c                                */
/* Numéro de version : 0.1                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 23/10/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/carte.h"

int main ()
{
    Carte mapHasard = Carte(LARGEUR, HAUTEUR, *("test")) ;

    mapHasard.remplirHasard () ;
    
    for (int i = 0; i < 4; i++)
        mapHasard.creerCaverne (rand() % LARGEUR * HAUTEUR + 280, 0) ;

    mapHasard.afficherCarte () ;

    mapHasard.~Carte () ;

    return 0;
}