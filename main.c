/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : main.c                                */
/* Numéro de version : 0.2                                   */
/* Date              : 16/03/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#include "type.h"
#include "fonction.h"

int main ()
{
    srand (time(NULL));

    unsigned int dirt;
    unsigned int stone;
    unsigned int gold;

    Map* mapHasard = creerMap(LARGEUR, HAUTEUR, *("newMap"));
    for (unsigned int i = 0; i < LARGEUR * HAUTEUR; i++)
    {
        dirt  = rand()%40+1;
        stone = rand()%40+1;
        gold  = rand()%40+1;
        
        if (i >= 5 * LARGEUR)
        {
            mapHasard->elements[i].type = BLOCK;

            if (gold < 2) /*---------->*/ mapHasard->elements[i].block = creerBlock (GOLD, 0, i % LARGEUR, i / LARGEUR);
            else if (stone < 10) /*--->*/ mapHasard->elements[i].block = creerBlock (STONE, rand()%3+1, i % LARGEUR, i / LARGEUR);
            else if (dirt <= 40) /*--->*/ mapHasard->elements[i].block = creerBlock (DIRT, 0, i % LARGEUR, i / LARGEUR);
            
        }

    }
    
    afficherMap (mapHasard);
    detruireMap (mapHasard);

    return 0;
}