/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : main.c                                */
/* Numéro de version : 0.2                                   */
/* Date              : 17/03/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "type.h"
#include "fonction.h"

int main ()
{
    srand (time(NULL));

    Map* mapHasard = creerMap(LARGEUR, HAUTEUR, *("newMap"));

    remplirHasard (mapHasard);
    creerCaverne  (mapHasard, rand() % LARGEUR * HAUTEUR + 280, 0);
    creerCaverne  (mapHasard, rand() % LARGEUR * HAUTEUR + 280, 0);
    creerCaverne  (mapHasard, rand() % LARGEUR * HAUTEUR + 280, 0);
    creerCaverne  (mapHasard, rand() % LARGEUR * HAUTEUR + 280, 0);
    
    afficherMap (mapHasard);
    detruireMap (mapHasard);

    return 0;
}