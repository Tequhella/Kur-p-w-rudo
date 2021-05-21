/*************************************************************/
/* Kurīpāwārudo (inspiré du jeu Creeper World 2)             */
/*-----------------------------------------------------------*/
/* Module            : gestionMap.h                          */
/* Numéro de version : 0.6                                   */
/* Date              : 18/05/2021                            */
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

void visibilitee (Map* m, int x, int y);

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

void ajouterStructure (Map* m, int x, int y, unsigned int type, int* erreur);

Coord* constructionStructure
(
    Map* m,
    Coord* _ePos,
    Coord* _tabEntitee,
    int* _entiteeAcreer,
    int* _compteE,
    int* _nb_Entitee,
    int* _nb_besoin
);

Coord* remplirEnergieStructure
(
    Map* m,
    Coord* _tabEntitee,
    int* _nb_Entitee,
    int* _nb_besoin,
    int* _sortie
);

void viderEnergieStructure (Map* m, Coord* _tabEntitee, int _nb_Entitee);

void ajouterSpawnerHasard (Case* c, unsigned int nb_Spawner);

void effetDegats (Case* c, Entity* attaquant, Entity* victime);

#endif