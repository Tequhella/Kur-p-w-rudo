/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : main.c                                */
/* Numéro de version : 0.3                                   */
/* Branche           : Branch-CPP                            */
/* Date              : 11/01/2022                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "../headers/carte.h"
#include "../headers/type.h"

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