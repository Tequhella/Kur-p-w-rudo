/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionMap.h                          */
/* Numéro de version : 0.7                                   */
/* Date              : 27/05/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _GESTIONMAP_H_INCLUDED_
#define _GESTIONMAP_H_INCLUDED_

#include "type.h"

//----------------------------Gestion Map----------------------------//

void remplirHasard (Map* m);

void creerCaverne (Map* m, unsigned int pos, int randMoins);

int testAccessibilitee (Map* m, int x, int y);

void decache (Map* m);

void remplirStock (Map* m);

void visibilitee (Map* m, int x, int y);

//---------------------------Gestion Block---------------------------//

void casserBlock
(
    Map* m,
    Coord* _bPos,
    int* _blockAcasser,
    int* _compte,
    int* _nb_besoin,
    int* _erreur
);

#endif