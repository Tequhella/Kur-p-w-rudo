/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionMap.h                          */
/* Numéro de version : 0.5                                   */
/* Date              : 21/03/2021                            */
/* Auteurs           : Lilian CHARDON                        */
/*************************************************************/

#ifndef _GESTIONMAP_H_INCLUDED_
#define _GESTIONMAP_H_INCLUDED_

#include "../headers/type.h"

//----------------------------Gestion Map----------------------------//

void remplirHasard (Map* m);

void creerCaverne (Map* m, unsigned int pos, int randMoins);

int testAccessibilitee (Map* m, int x, int y);

void decache (Map* m);

void remplirStock (Map* m);

//---------------------------Gestion Block---------------------------//

void casserBlock
(
    Map* m,
    Coord* _bPos,
    int* _blockAcasser,
    int* _compte,
    int* _nb_besoin
);

//--------------------------Gestion Entitee--------------------------//

void ajouterEntitee (Case* c, int x, int y, unsigned int type, unsigned int* erreur);

void constructionEntitee
(
    Map* m,
    Coord* _ePos,
    Coord* _tabEntitee,
    int* _entiteeAcreer,
    int* _compteE,
    int* _nb_Entitee,
    int* _nb_besoin,
    int* _sortie
);

void remplirEnergieEntitee (Map* m, Coord* _tabEntitee, int* _nb_Entitee, int* _nb_besoin);

void viderEnergieEntitee (Map* m, Coord* _tabEntitee, int* _nb_Entitee);

void ajouterSpawnerHasard (Case* c, unsigned int nb_Spawner);

#endif
